/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_test_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 16:12:46 by smolines          #+#    #+#             */
/*   Updated: 2024/12/23 12:58:06 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

/*Test the access of the paths found*/

/* test_path : créer et tester un path*/
char *create_and_check_path(char *path, char *cmd, t_manager *manager, char **paths)
{
    char *to_test;

    to_test = join_path(path, cmd, manager, paths);
    if (to_test == NULL)
        return (NULL);
    if (access(to_test, F_OK) == 0)
    {
        if (access(to_test, X_OK) == 0)
            return (to_test);
    }
    free(to_test);
    return (NULL);
}

/*test_path : gère le path trouvé*/
void update_right_path(char **right_path, char *new_path)
{
    if (*right_path)
        free(*right_path);
    *right_path = ft_strdup(new_path);
}

/*tester le path*/
char *test_path(char **paths, char *cmd, t_manager *manager)
{
    int   i;
    char *to_test;
    char *right_path;

    i = 0;
    right_path = NULL;
    while (paths[i])
    {
        to_test = create_and_check_path(paths[i], cmd, manager, paths);
        if (to_test)
        {
            update_right_path(&right_path, to_test);
            free(to_test);
        }
        i++;
    }
    return (right_path);
}
