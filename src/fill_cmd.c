/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 10:27:13 by aubertra          #+#    #+#             */
/*   Updated: 2024/12/13 13:05:44 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Transforming the token list into the cmd list

#include "minishell.h"
#include "libft.h"

t_token	*fill_args(t_token *current, t_cmd *cmd, t_manager *manager)
{
	t_token	*save_first;
	int		cmd_count;
	int		i;

	(void)manager; //voir si utile pour gestion d erreur
	cmd_count = 0;
	save_first = current;
	while (current && (current->type == CMD_ARG
				|| current->type == DOUBLE_QUOTE
				|| current->type == SIMPLE_QUOTE))
	{
		cmd_count++;
		current = current->next;
	}
	cmd->args=(char **)malloc(sizeof(char *) * (cmd_count + 1));
	if (!cmd->args)
		return (NULL);
	i = 0;
	while (save_first && i < cmd_count)
	{
		cmd->args[i] = ft_strdup(save_first->value);
		save_first = save_first->next;
		i++;
	}
	cmd->args[i] = NULL;
	return (current);
}

int	expand_loop(t_token *current_token, t_env *s_env, t_manager *manager)
{
	while (current_token && current_token->type != PIPE)
	{
		if (current_token->type == ENV_VAR)
		{
			expand(current_token, s_env);
			current_token->type = is_operators(manager, current_token->value, 0);
			if (current_token->type == DIR)
				return (handle_dir(manager, NULL, 0, &(current_token->value)));
		}
		else if (current_token->type == DOUBLE_QUOTE)
		{
			expand_dquote(current_token, s_env);
		}
		current_token = current_token->next;
	}
	return (0);
}


int	redir_loop(t_token *current_token, t_cmd *cmd, t_manager *manager)
{
	while (current_token && current_token->type != PIPE)
	{
		if (current_token->type == REDIR_APPEND)
		{
			cmd->append = 1;
			if (check_outfile(current_token->value, manager) == -1)
				return (-1);
			cmd->outfile = ft_strdup(current_token->value);
		}
		else if (current_token->type == REDIR_OUT)
		{
			cmd->append = 0;
			if (check_outfile(current_token->value, manager) == -1)
				return (-1);
			cmd->outfile = ft_strdup(current_token->value);
		}
		else if (current_token->type == REDIR_IN)
		{
			cmd->heredoc_priority = 0;
			if (check_infile(current_token->value, manager) == -1)
				return (-1);
			cmd->infile = ft_strdup(current_token->value);
		}
		else if (current_token->type == REDIR_HEREDOC)
		{
			cmd->heredoc_priority = 1;
			if (check_heredoc(manager) == - 1)
				return (-1);
			cmd->lim = ft_strdup(current_token->value);
		}
		current_token = current_token->next;
	}
	return (0);
}

t_token	*cmd_loop(t_token *current_token, t_cmd *cmd, t_manager *manager)
{
	while (current_token)
	{
		if (current_token->type == CMD_ARG
			|| current_token->type == DOUBLE_QUOTE
			|| current_token->type == SIMPLE_QUOTE)
				current_token = fill_args(current_token, cmd, manager);
		if (!current_token || current_token->type == PIPE)
			break;
		current_token = current_token->next;
	}
	return (current_token);
}


int	fill_cmd(t_manager *manager, t_env *s_env)
{
	t_token	*current_token;
	t_cmd	*cmd;
	int		cmd_node_count;

	current_token = manager->token_first;
	cmd_node_count = 0;
	while (current_token)
	{
		if (expand_loop(current_token, s_env, manager) == -1)
			return (-1);
		cmd = cmd_new();
		if (redir_loop(current_token, cmd, manager) == -1)
			return (-1);
		current_token = cmd_loop(current_token, cmd, manager);
		create_cmd_list(cmd, cmd_node_count, manager);
		if (current_token && current_token->type == PIPE)
		{
			current_token = current_token->next;
			cmd_node_count++;
		}
	}
	return (0);
}
