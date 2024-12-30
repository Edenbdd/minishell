/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 10:27:13 by aubertra          #+#    #+#             */
/*   Updated: 2024/12/29 18:32:20 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Transforming the token list into the cmd list

#include "minishell.h"
#include "libft.h"

int	redir_in_out(t_token *current_token, t_cmd *cmd, t_manager *manager)
{
	if (current_token->type == REDIR_OUT)
	{
		cmd->append = 0;
		if (cmd->outfile)
				free(cmd->outfile);
		cmd->outfile = ft_strdup(current_token->value);
		if (check_outfile(current_token->value, manager, cmd, 0) == -1)
			return (-1);
	}
	else if (current_token->type == REDIR_IN)
	{
		cmd->heredoc_count = 0;
		if (check_infile(current_token->value, manager) == -1)
			return (-1);
		cmd->infile = ft_strdup(current_token->value);
	}
	return (0);
}
//a recouper
int	redir_loop(t_token *current_token, t_cmd *cmd, t_manager *manager)
{
	while (current_token && current_token->type != PIPE
			&& !(cmd->heredoc_count > 0 && current_token->type == REDIR_HEREDOC))
	{
		if (current_token->type == REDIR_APPEND)
		{
			cmd->append = 1; 
			if (cmd->outfile)
				free(cmd->outfile);
			cmd->outfile = ft_strdup(current_token->value);
			if (check_outfile(current_token->value, manager, cmd, 0) == -1)
				return (-1);
		}
		else if ((current_token->type == REDIR_IN 
				|| current_token->type == REDIR_OUT)
				&& redir_in_out(current_token, cmd, manager) == -1)
			return (-1);
		else if (current_token->type == REDIR_HEREDOC)
		{
			if (cmd->heredoc_count > 1)
				break;
			if (parse_lim(current_token, cmd, manager) == -1)
				return (-1);	
			cmd->heredoc_count++; //maybe this should be commented ??
			if (cmd->heredoc_count > 1 && manager->heredoc_line 
				&& current_token->type == REDIR_HEREDOC)
				break;
		}
		current_token = current_token->next;
	}
	return (0);
}


t_token	*cmd_loop(t_token *current_token, t_cmd *cmd, t_manager *manager)
{
	current_token->cmd_done = 1;
	
	while (current_token)
	{
		if (current_token->type == CMD_ARG
			|| current_token->type == DOUBLE_QUOTE
			|| current_token->type == SIMPLE_QUOTE)
				current_token = fill_args(current_token, cmd, manager);
		if (!current_token || current_token->type == PIPE
			|| (cmd->heredoc_count > 1 && manager->heredoc_line == 0))
			break;
		if (current_token->type == REDIR_HEREDOC && current_token->next &&
				current_token->next->type == REDIR_HEREDOC)
		{
			current_token = current_token->next;
			break;
		}
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
		printf("start of the loop current is %s\n", current_token->value);
		if (expand_loop(current_token, s_env, manager) == -1)
			return (-1);
		cmd = cmd_new();
		if (redir_loop(current_token, cmd, manager) == -1)
			return (-1);
		printf("after redir loop current is %s\n", current_token->value);
		current_token = cmd_loop(current_token, cmd, manager);
		create_cmd_list(cmd, cmd_node_count, manager);
		cmd_node_count++; //moved here
		if (current_token && (current_token->type == PIPE 
			|| (current_token->type == REDIR_HEREDOC
			&& current_token->cmd_done == 1)))
			current_token = current_token->next;
	}
	return (0);
}

/*Original redir loop (a ete coupee)*/
// int	redir_loop(t_token *current_token, t_cmd *cmd, t_manager *manager)
// {
// 	while (current_token && current_token->type != PIPE
// 			&& !(cmd->heredoc_count > 0 && current_token->type == REDIR_HEREDOC))
// 	{
// 		if (current_token->type == REDIR_APPEND)
// 		{
// 			cmd->append = 1;
// 			if (check_outfile(current_token->value, manager) == -1)
// 				return (-1);
// 			cmd->outfile = ft_strdup(current_token->value);
// 		}
// 		else if (current_token->type == REDIR_OUT)
// 		{
// 			cmd->append = 0;
// 			if (check_outfile(current_token->value, manager) == -1)
// 				return (-1);
// 			cmd->outfile = ft_strdup(current_token->value);
// 		}
// 		else if (current_token->type == REDIR_IN)
// 		{
// 			cmd->heredoc_count = 0;
// 			if (check_infile(current_token->value, manager) == -1)
// 				return (-1);
// 			cmd->infile = ft_strdup(current_token->value);
// 		}
// 		else if (current_token->type == REDIR_HEREDOC)
// 		{
// 			if (cmd->heredoc_count > 1)
// 				break;
// 			if (parse_lim(current_token, cmd, manager) == -1)
// 				return (-1);	
// 			cmd->heredoc_count++;
// 		}
// 		current_token = current_token->next;
// 	}
// 	return (0);
// }