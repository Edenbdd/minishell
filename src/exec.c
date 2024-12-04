/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 10:27:13 by aubertra          #+#    #+#             */
/*   Updated: 2024/12/04 17:44:23 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Everything related to the execution

#include "minishell.h"
#include "libft.h"

t_token	*fill_args(t_token *current, char **args)
{
	t_token	*save_first;
	int		cmd_count;
	int		i;

	cmd_count = 0;
	save_first = current;
	while (current && (current->type == CMD_ARG
				|| current->type == DOUBLE_QUOTE
				|| current->type == SIMPLE_QUOTE))
	{
		cmd_count++;
		current = current->next;
	}
	args=(char **)malloc(sizeof(char *) * (cmd_count + 1));
	if (!args)
		return (NULL);
	i = 0;
	while (save_first && (save_first->type == CMD_ARG
				|| save_first->type == DOUBLE_QUOTE
				|| save_first->type == SIMPLE_QUOTE))
	{
		args[i] = save_first->value;
		save_first = save_first->next;
	}
	args[i] = "\0";
	return (current);
}
void	expand_loop(t_token *current_token, t_env *s_env)
{
	while (current_token && current_token->type != PIPE)
	{
		printf("start first loop current_token value is [%s]\n", current_token->value);
		//gere les expand en dehors et dans les dquote
		if (current_token->type == ENV_VAR)
		{
			printf("I go in first expand\n");
			expand(current_token, s_env);
		}
		else if (current_token->type == DOUBLE_QUOTE)
		{
			printf("I go in dquote\n");
			expand_dquote(current_token, s_env);
		}
		current_token = current_token->next;
	}
}

void	redir_loop(t_token *current_token, t_cmd *cmd)
{
	while (current_token && current_token->type != PIPE)
	{
		if (current_token->type == REDIR_APPEND 
					|| current_token->type == REDIR_OUT)
		{
			cmd->outfile = current_token->value;
			printf("i go intro redir out ?\n");
			printf("cmd outfile [%s]\n", cmd->outfile);
		}
		else if (current_token->type == REDIR_IN
			|| current_token->type == REDIR_HEREDOC)
		{
			cmd->infile = current_token->value;
			printf("i go intro redir in ?\n");
			printf("cmd outfile [%s]\n", cmd->outfile);
		}
		current_token = current_token->next;
	}
}
void	cmd_loop(current_token, cmd)
{
	if (current_token->type == CMD_ARG
			|| current_token->type == DOUBLE_QUOTE
			|| current_token->type == SIMPLE_QUOTE)
				current_token = fill_args(current_token, cmd->args);
		printf("after arg current_token value is [%s]\n", current_token->value);

}
void	fill_cmd(t_manager *manager, t_env *s_env)
{
	t_token	*current_token;
	t_token	*save_start;
	t_cmd	*cmd;
	int		cmd_node_count;

	current_token = manager->token_first;
	cmd_node_count = 0;
	while (current_token)
	{
		save_start = current_token;
		expand_loop(current_token, s_env); //faire les expand jusqu au pipe
		//init du node cmd
		cmd = cmd_new();
		//le while va remplir le node cmd
		current_token = save_start; //je rep[ars au debut de ma sequence
		redir_loop(current_token, cmd);
		//ici je dois check si cmd c est bien update	
		cmd_loop(current_token, cmd);
		if (current_token && current_token->type == PIPE)
			break;
		current_token = current_token->next;
	}
	//ajouter cmd a la liste
	if (cmd_node_count == 0) //save the first node in the manager
		manager->cmd_first = cmd;
	if (cmd_node_count > 0)
		cmd_add_back(manager->cmd_first, cmd); //ajouter a la suite des cmd
	free(cmd);
	//reloop a la cmd suivant
}
