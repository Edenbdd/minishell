/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin_args.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 14:40:26 by aubertra          #+#    #+#             */
/*   Updated: 2025/01/02 10:37:35 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

//mettre les fonctions static dans le .h + trier les fonctions dans des fichiers

int count_args_env(char **old_args, int i)
{
    int count;

    count = 0;
    while (old_args[i])
    {
        count++;
        i++;
    }
    return (count);
}
char **fill_new_args(char **old_args, int i, int count)
{
    char    **new_args;
    int     j;

    new_args = (char **)malloc(sizeof(char *) * (count + 1));
    if (!new_args)
        return (NULL);
    j = 0;
    while (old_args[i])
    {
        new_args[j] = ft_strdup(old_args[i]);
        i++;
        j++;
    }
    new_args[j] = NULL;
    return (new_args);
}

char    **copy_args(char **old_args, int i)
{
    int count;
    char    **new_args;
    count = count_args_env(old_args, i);
    new_args = fill_new_args(old_args, i, count);
    if (!new_args)
    {
        system_function_error(NULL, 7);
        return (NULL);
    }
    return (new_args);
}
