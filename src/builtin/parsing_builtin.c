/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 13:27:41 by aubertra          #+#    #+#             */
/*   Updated: 2024/12/30 14:26:18 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Parsing and execution functions for all the built ins*/

#include "minishell.h"
#include "libft.h"

/*From manager->word that is of a type CMD, this function will identify
if it is a builtin cmd, else it will do nothing*/
void    check_builtin(t_manager *manager, char *to_test)
{
    if (!strcmp(to_test, "echo"))
        manager->type = ECHO;
    else if (!strcmp(to_test, "cd"))
        manager->type = CD;
    else if (!strcmp(to_test, "pwd"))
        manager->type = PWD;
    else if (!strcmp(to_test, "export"))
        manager->type = EXPORT;
    else if (!strcmp(to_test, "unset"))
        manager->type = UNSET;
    else if (!strcmp(to_test, "env"))
        manager->type = ENV;
    else if (!strcmp(to_test, "exit"))
        manager->type = EXIT;
    return;
}
/*Function to check if the type is one of the builtin to avoid repetitive
long conditions in parsing and exec functions*/
int is_builtin(int type)
{
    if (type >= ECHO && type <= EXIT)
        return (1);
    return (0);
}

int		builtin_exec_path(t_manager *manager, t_cmd *cmd, int *previous_fd)
{
    (void)previous_fd; //voir si necessaire pour la gestion d erreur !
    check_builtin(manager, cmd->args[0]);
    printf("type is %d\n", manager->type);
    if (manager->type == ECHO)
        printf("built in a coder\n");
    else if (manager->type == CD)
        printf("built in a coder\n");
    else if (manager->type == PWD)
        printf("built in a coder\n");
    else if (manager->type == EXPORT)
        printf("built in a coder\n");
    else if (manager->type == UNSET)
        printf("built in a coder\n");
    else if (manager->type == ENV)
        printf("built in a coder\n");
    else if (manager->type == EXIT)
        printf("built in a coder\n");
    return (0);    
}

