/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmd_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 16:12:46 by smolines          #+#    #+#             */
/*   Updated: 2024/12/29 18:25:51 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

// Compte le nombre d'arguments d'une commande
int count_args(t_token *current) 
{
    int cmd_count;

    cmd_count = 0;
    while (current && (current->type == CMD_ARG
                || current->type == DOUBLE_QUOTE
                || current->type == SIMPLE_QUOTE
                || current->type == DIREC)) 
    {
        cmd_count++;
        current = current->next;
        //skip redir et son file           
        while (current && (current->type == REDIR_IN
			|| current->type == REDIR_OUT
			|| current->type == REDIR_HEREDOC
			|| current->type == REDIR_APPEND))
            current = current->next;
    }
    return (cmd_count);
}

// malloc le tableau d'arguments de la commande
char    **allocate_args(int cmd_count) 
{
    char **args;
    
    args = (char **)malloc(sizeof(char *) * (cmd_count + 1));
    if (!args)
        return NULL;
    return args;
}

// Remplit le tableau d'arguments de la commande
t_token *fill_args_values(t_token *current, char **args, int cmd_count, t_manager *manager) 
{
    int i;
    
    i = 0;
    while (current && i < cmd_count) 
    {
        args[i] = ft_strdup(current->value);
        current = current->next;
        while (current && (current->type == REDIR_IN
			|| current->type == REDIR_OUT
		    || (current->type == REDIR_HEREDOC 
            && manager->heredoc_line == 0)
			|| current->type == REDIR_APPEND))
            current = current->next;
        i++;
    }
    args[i] = NULL;
    return (current);
}

// Fonction principale pour remplir les arguments d'une commande
t_token *fill_args(t_token *current, t_cmd *cmd, t_manager *manager) 
{
    int cmd_count;

    (void)manager;
    cmd_count = count_args(current); //missleading name ! maybe args_count ?
    cmd->args = allocate_args(cmd_count);
    if (!cmd->args)
        return (NULL);
    return (fill_args_values(current, cmd->args, cmd_count, manager));
}
