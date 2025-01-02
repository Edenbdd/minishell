/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 10:27:13 by aubertra          #+#    #+#             */
/*   Updated: 2024/12/20 13:08:59 by aubertra         ###   ########.fr       */
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
			cmd->heredoc_count = 0;
			if (check_infile(current_token->value, manager) == -1)
				return (-1);
			cmd->infile = ft_strdup(current_token->value);
		}
		else if (current_token->type == REDIR_HEREDOC)
		{
//			printf("I come in the redir heredoc\n");
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
	printf("je suis dans cmd loop\n");
	while (current_token)
	{
//		printf("in cmd loop herecount %d\n", cmd->heredoc_count);
		if (current_token->type == CMD_ARG
			|| current_token->type == DOUBLE_QUOTE
			|| current_token->type == SIMPLE_QUOTE)
				current_token = fill_args(current_token, cmd, manager);
//		if (current_token)
//			printf("after fill args current value is [%s]\n", current_token->value);
//		else
//			printf("after fill args current token is at the end\n");
		if (!current_token || current_token->type == PIPE
			|| cmd->heredoc_count > 1)
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
//		printf("TOKEN TO CMD LOOP\n");
		if (expand_loop(current_token, s_env, manager) == -1)
			return (-1);
printf("je suis dans fill_cmd apres expand loop\n");
printf("apres expand loop value is / [%s]\n", current_token->value);
printf("\033[31m a ce moment display de la liste token\033[0m\n");
token_display(manager->token_first);

		cmd = cmd_new();
//		printf("before redir token is [%s]\n", current_token->value);
		if (redir_loop(current_token, cmd, manager) == -1)
			return (-1);
//		printf("after redir loop token is [%s] and herecount is %d\n", current_token->value, cmd->heredoc_count);
		current_token = cmd_loop(current_token, cmd, manager);
//		if (current_token)
//			printf("after cmd loop token is [%s]\n", current_token->value);
//		else
//			printf("end of current token\n");
		create_cmd_list(cmd, cmd_node_count, manager);
		if (current_token && (current_token->type == PIPE 
			|| current_token->type == REDIR_HEREDOC))
		{
//			printf("I come here\n");
			current_token = current_token->next;
			cmd_node_count++;
		}
	}
	return (0);
}
