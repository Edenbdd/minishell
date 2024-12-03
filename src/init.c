/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smolines <smolines@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 18:13:00 by smolines          #+#    #+#             */
/*   Updated: 2024/12/03 14:36:05 by smolines         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

t_manager	*init_manager(t_manager *manager)
{
	manager->token_first = NULL;
	manager->token_last = NULL;
	manager->size_token = -1;
	manager->cmd_first = NULL;
	manager->cmd_last = NULL;
	manager->size_cmd = -1;
	manager->env_first = NULL;
	manager->env_last = NULL;
	manager->size_env = -1;
	manager->export_first = NULL;
	manager->export_last = NULL;
	manager->size_export = -1;
	return (manager);
}
//t_token		*init_token(t_token *token)
//{
//	token->value = NULL;
//	token->type = -1;
//	token->flag = -1;
//	token->next = NULL;
//	token->prev = NULL;
//}

//t_cmd		*init_cmd(t_cmd *cmd)
//{
//	cmd->path = NULL;
//	cmd->args = NULL;
//	cmd->pid = -1;
//	cmd->redir = NULL;
//	cmd->next = NULL;
//	cmd->prev = NULL;
//}

//t_redirs	*init_redirs(t_redirs *redirs)
//{
//	redirs->infile = NULL;
//	redirs->in_fd = -1;
//	redirs->outfile = NULL;
//	redirs->out_fd = -1;
//	redirs->pfd[0] = -1;
//	redirs->pfd[1] = -1;
//}
