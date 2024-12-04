/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oplist_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 22:30:11 by smolines          #+#    #+#             */
/*   Updated: 2024/12/04 17:04:05 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

// //ajouter le nouveau cmd a la liste cmd
// void	*cmd_add_new(t_cmd *new_cmd, t_cmd **cmd)
// {
// 	if (!new_cmd)
// 		return (NULL);
// 	cmd_add_back((*cmd), new_cmd);
// 	return (new_cmd);
// }

//creer un nouveau cmd avec tout set a NULL
t_cmd	*cmd_new(void)
{
	t_cmd	*new_cmd;

	new_cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (new_cmd == NULL)
		return (NULL);
	new_cmd->path = NULL;
	new_cmd->args = NULL;
	new_cmd->pid = -1;
	//new_cmd->redirs = NULL;
	new_cmd->infile = NULL;
	new_cmd->in_fd = -1;
	new_cmd->outfile = NULL;
	new_cmd->out_fd = -1;	
	new_cmd->pfd[0]	= -1;
	new_cmd->pfd[1]	= -1;
	new_cmd->next = NULL;
	new_cmd->prev = NULL;
	return (new_cmd);
}

// ajouter un nouveau cmd a la fin de la liste cmd
void	cmd_add_back(t_cmd *first_cmd, t_cmd *new_cmd)
{
	t_cmd	*lastposition;

	if (!new_cmd || !first_cmd)
		return ;
	lastposition = cmd_last(first_cmd);
	lastposition->next = new_cmd;
	new_cmd->prev = lastposition;
}

// trouver le dernier element de la liste cmd
t_cmd	*cmd_last(t_cmd *cmd)
{
	if (!cmd)
		return (NULL);
	while (cmd->next != NULL)
		cmd = cmd->next;
	return (cmd);
}

void	cmd_display(t_cmd *cmd)
{
	if (!cmd)
	{
		printf("there is no cmd ?\n");
		return ;
	}
	while (cmd)
	{
		printf("-- infile: [%s] -- outfile:[%s]\n", cmd->infile, cmd->outfile);
		cmd = cmd->next;
	}
}
