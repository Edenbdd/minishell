/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 10:02:56 by aubertra          #+#    #+#             */
/*   Updated: 2025/01/03 13:19:05 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int export_add(char *str, char *name, t_manager *manager, t_export *current)
{
    char    *new_content;
    t_env   *current_env;
    //updating the export
    new_content = ft_strjoin(current->content, get_content(str));
    free(current->content);
    current->content = new_content;
    //updating the env
    current_env = manager->env_first;
    while (current_env)
    {
        if (!ft_strcmp(current_env->field, name))
        {
            free(current_env->content);
            current->content = new_content;
            break;
        }
        current_env = current_env->next;
    }
    return (1);
}

int export_replace(char *str, char *name, t_manager *manager, t_export *current)
{
    int     i;
    t_env   *current_env;
    
    i = 0;
    while (str[i] && str[i] != '=')
        i++;
    if (i == ft_strlen(str))
        return (-1);
    if (str[i] && str[i -1] && str[i - 1] == '+')
        return (0);
    free(current->content); //updating the export
    current->content = get_content(str);
    current_env = manager->env_first; //updating the env
    while (current_env)
    {
        if (!ft_strcmp(current_env->field, name))
        {
            free(current_env->content);
            current_env->content = get_content(str);
            break;
        }
        current_env = current_env->next;
    }
    return (1);
} //see if that update the export properly

int existing_export(char *str, t_manager *manager)
{
    t_export    *current;
    char        *var_name;
    int         found;

    current = manager->export_first;
    var_name = get_name(str, 1);
    found = 0;
    while (current)
    {
        if (!ft_strcmp(var_name, current->field))
        {
            found = 1;
            break;
        }
        current = current->next;
    }
    if (!found)
        return (0); 
    if (export_replace(str, var_name, manager, current))
        return (1);
    else
        export_add(str, var_name, manager, current);
    return (0);
}

int equal_presence(char *str)
{
    int i;
    int one_equal;
    int plus_count;

    i = 0;
    one_equal = 0;
    plus_count = 0;
    while (str[i])
    {
        if (str[i] == '=')
           one_equal++;
        if (str[i] == '+' && str[i + 1] && str[i + 1] != '=')
            return (-1);
        if ((str[i] == '+' && str[i + 1] && str[i + 1] == '='))
            plus_count++;
        i++;
    }
    if (plus_count > 1)
        return (plus_count);
    return (one_equal);
}

int parsing_export_var(char *str, t_manager *manager)
{
    int     i;
    char    *option;

    if (str[0] == '-')
    {
        option = ft_strndup(str, 2);
        return (parsing_error(manager, 5, "bash: export", option));
    }
    if (!ft_isalpha(str[0]) && str[0] != '_')
        return (parsing_error(manager, 4, "bash: export", str));
    i = 1;
    while (str[i])
    {
        if (!ft_isalnum(str[i]) && str[i] != '_' && str[i] != '='
            && str[i] != '+')
            return (parsing_error(manager, 4, "bash: export", str));
        i++;
    }
    if (equal_presence(str) > 1 || equal_presence(str) == -1)
        return (parsing_error(manager, 4, "bash: export", str));
    else if (equal_presence(str) == 1)
        return (1);
    else
        return (0);
}
