/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oplist_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 22:30:11 by smolines          #+#    #+#             */
/*   Updated: 2024/12/19 17:30:17 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

//handle the creation and fills the cmd list
void	create_cmd_list(t_cmd *new_cmd, int cmd_node_count, t_manager *manager)
{
	printf("creating a new cmd !\n");
	new_cmd->index = cmd_node_count;
	manager->size_cmd = cmd_node_count + 1;
	if (!new_cmd->args && new_cmd->heredoc_count > 0)
	{
		new_cmd->args = allocate_args(0); 
        new_cmd->args[0] = ft_strdup("\n");
        new_cmd->args[1] = NULL;
    }
	if (cmd_node_count == 0) //save the first node in the manager
		manager->cmd_first = new_cmd;
	else
		cmd_add_back(manager->cmd_first, new_cmd); //ajouter a la suite des cmd
}

//creer un nouveau cmd avec tout set a NULL
t_cmd	*cmd_new(void)
{
	t_cmd	*new_cmd;

	new_cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (new_cmd == NULL)
		return (NULL);
	new_cmd->index = 0;
	new_cmd->path = NULL;
	new_cmd->args = NULL;
	//new_cmd->redirs = NULL;
	new_cmd->infile = NULL;
	new_cmd->lim = NULL;
	new_cmd->heredoc_count = -1;
	new_cmd->heredoc_quotes = 0;
	new_cmd->outfile = NULL;
	new_cmd->append = -1;	
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

