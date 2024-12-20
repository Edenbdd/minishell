/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 10:27:13 by aubertra          #+#    #+#             */
/*   Updated: 2024/12/20 19:49:12 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Transforming the token list into the cmd list

#include "minishell.h"
#include "libft.h"

//Fonction redir loop avant d etre scinder en 2 (a garder pour reference)
// int	redir_loop(t_token *current_token, t_cmd *cmd, t_manager *manager)
// {
// 	while (current_token && current_token->type != PIPE)
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
// 			cmd->heredoc_priority = 0;
// 			if (check_infile(current_token->value, manager) == -1)
// 				return (-1);
// 			cmd->infile = ft_strdup(current_token->value);
// 		}
// 		else if (current_token->type == REDIR_HEREDOC)
// 		{
// 			cmd->heredoc_priority = 1;
// 			if (check_heredoc(manager) == - 1)
// 				return (-1);
// 			cmd->lim = ft_strdup(current_token->value);
// 		}
// 		current_token = current_token->next;
// 	}
// 	return (0);
// }

int	redir_loop(t_token *current_token, t_cmd *cmd, t_manager *manager)
{
	while (current_token && current_token->type != PIPE
			&& !(cmd->heredoc_count > 0 && current_token->type == REDIR_HEREDOC))
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
			cmd->heredoc_count = 0;
			if (check_infile(current_token->value, manager) == -1)
				return (-1);
			cmd->infile = ft_strdup(current_token->value);
		}
		else if (current_token->type == REDIR_HEREDOC)
		{
			printf("I come in the redir heredoc\n");
			if (cmd->heredoc_count > 1)
				break;
			if (parse_lim(current_token, cmd, manager) == -1)
				return (-1);	
			cmd->heredoc_count++;
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
		// printf("in cmd loop herecount %d\n", cmd->heredoc_count);
		if (current_token->type == CMD_ARG
			|| current_token->type == DOUBLE_QUOTE
			|| current_token->type == SIMPLE_QUOTE)
				current_token = fill_args(current_token, cmd, manager);
		if (current_token)
			printf("after fill args current value is [%s]\n", current_token->value);
		else
			printf("after fill args current token is at the end\n");
		if (!current_token || current_token->type == PIPE
			|| cmd->heredoc_count > 1) //j avais mis >1, voir si ca pose pb 
			break;
		else if (current_token->type == REDIR_HEREDOC && current_token->next &&
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
		printf("\033[0;34mTOKEN TO CMD LOOP\033[0m\n");
		if (expand_loop(current_token, s_env, manager) == -1)
			return (-1);
		cmd = cmd_new();
		printf("before redir token is [%s]\n", current_token->value);
		if (redir_loop(current_token, cmd, manager) == -1)
			return (-1);
		printf("after redir loop token is [%s] and herecount is %d\n", current_token->value, cmd->heredoc_count);
		current_token = cmd_loop(current_token, cmd, manager);
		if (current_token)
			printf("after cmd loop token is [%s]\n", current_token->value);
		else
			printf("end of current token\n");
		create_cmd_list(cmd, cmd_node_count, manager);
		cmd_node_count++; //moved here
		if (current_token && (current_token->type == PIPE 
			|| (current_token->type == REDIR_HEREDOC
			&& current_token->cmd_done == 1)))
		{
			printf("I come here to skip to the next token\n");
			current_token = current_token->next;
			//cmd_node_count++; was here before but moved on top, may create bug
		}
		printf("cmd created: arg[0] [%s], lim [%s]\n", cmd->args[0], cmd->lim);
	}
	return (0);
}
