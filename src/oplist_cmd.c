/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oplist_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 22:30:11 by smolines          #+#    #+#             */
/*   Updated: 2024/12/03 11:17:37 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

//ajouter le nouveau cmd a la liste cmd
void	*cmd_add_new(t_cmd *new_cmd, t_cmd **cmd)
{
	if (!new_cmd)
		return (NULL);
	cmd_add_back(&(*cmd), new_cmd);
	return (new_cmd);
}

//creer un nouveau cmd
t_cmd	*cmd_new(char *word, int type)
{
	t_cmd	*new_cmd;

	new_cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (new_cmd == NULL)
		return (NULL);
	cmd->path = find_path(current_token);
	cmd->args = get_args(current_token);
	new_cmd->pid = -1;
	new_cmd->redirs = NULL;
	new_cmd->next = NULL;
	new_cmd->prev = NULL;
	return (new_cmd);
}

// ajouter un nouveau cmd a la fin de la liste cmd
void	cmd_add_back(t_cmd **cmd, t_cmd *new_cmd)
{
	t_cmd	*lastposition;

	if (!new_cmd)
		return ;
	if (*cmd)
	{
		lastposition = cmd_last(*cmd);
		lastposition->next = new_cmd;
	}
	if (!(*cmd))
		*cmd = new_cmd;	
}

// trouver le dernier element de la liste cmd
t_cmd	*cmd_last(t_cmd *cmd)
{
	if (cmd == NULL)
		return (0);
	while (cmd->next != NULL)
		cmd = cmd->next;
	return (cmd);
}

void	cmd_display(t_cmd *cmd)
{
	if (cmd == NULL)
		return ;
	while (cmd)
	{
		printf("cmd value :[%s] -- type : [%d]\n", cmd->value, cmd->type);
		cmd = cmd->next;
	}
}