/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 13:27:41 by aubertra          #+#    #+#             */
/*   Updated: 2025/01/02 15:10:44 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Parsing and execution functions for all the built ins*/

#include "minishell.h"
#include "libft.h"

/*From manager->word that is of a type CMD, this function will identify
if it is a builtin cmd, else it will do nothing*/
int    check_builtin(t_manager *manager, char *to_test)
{
    (void)manager; //supp ca plus tard si pas besoin
    if (!strcmp(to_test, "echo"))
       return (ECHO);
    else if (!strcmp(to_test, "cd"))
       return (CD);
    else if (!strcmp(to_test, "pwd"))
       return (PWD);
    else if (!strcmp(to_test, "export"))
       return (EXPORT);
    else if (!strcmp(to_test, "unset"))
       return (UNSET);
    else if (!strcmp(to_test, "env"))
       return (ENV);
    else if (!strcmp(to_test, "exit"))
       return (EXIT);
    return (CMD_ARG);
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
    (void)previous_fd; //voir si necessaire pour la gestion d erreur !, je pense que je peux le virer mais a voir
    printf("cmd args is %s\n", cmd->args[0]);
    manager->type = check_builtin(manager, cmd->args[0]);
    printf("type is %d\n", manager->type);
    if (manager->type == ECHO)
        printf("built in a coder\n");
    else if (manager->type == CD)
        printf("built in a coder\n");
    else if (manager->type == PWD)
        printf("built in a coder\n");
    else if (manager->type == EXPORT)
        return (handle_builtin_export(manager, cmd));
    else if (manager->type == UNSET)
        printf("built in a coder\n");
    else if (manager->type == ENV)
        return (handle_builtin_env(manager, cmd));
    else if (manager->type == EXIT)
        printf("built in a coder\n");
    return (0); // a changer en -1 quand toutes les fonctions seront en place et retournerons 0 si ok et -1 si pb
}
