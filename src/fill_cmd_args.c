/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 16:12:46 by smolines          #+#    #+#             */
/*   Updated: 2024/12/13 14:18:41 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

/*
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
				|| current->type == SIMPLE_QUOTE
				|| current->type == DIR))
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
*/


// Compte le nombre d'arguments d'une commande
int count_args(t_token *current) 
{
    int cmd_count = 0;

    while (current && (current->type == CMD_ARG
                || current->type == DOUBLE_QUOTE
                || current->type == SIMPLE_QUOTE
                || current->type == DIR)) {
        cmd_count++;
        current = current->next;
    }
    return cmd_count;
}

// malloc le tableau d'arguments de la commande
char **allocate_args(int cmd_count) 
{
    char **args = (char **)malloc(sizeof(char *) * (cmd_count + 1));
    if (!args)
        return NULL;
    return args;
}

// Remplit le tableau d'arguments de la commande
t_token *fill_args_values(t_token *current, char **args, int cmd_count) 
{
    int i = 0;
    while (current && i < cmd_count) {
        args[i] = ft_strdup(current->value);
        current = current->next;
        i++;
    }
    args[i] = NULL;
    return current;
}

// Fonction principale pour remplir les arguments d'une commande
t_token *fill_args(t_token *current, t_cmd *cmd, t_manager *manager) 
{
    int cmd_count;

    (void)manager; // Voir si utile pour gestion d'erreur
    cmd_count = count_args(current);
    cmd->args = allocate_args(cmd_count);
    if (!cmd->args)
        return NULL;
    return fill_args_values(current, cmd->args, cmd_count);
}