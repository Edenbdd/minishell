/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_add_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 16:44:15 by aubertra          #+#    #+#             */
/*   Updated: 2025/01/02 18:35:17 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Functions to handle parsing the new variable and adding it to the export and env 
linked list and updating the manager accordingly*/

#include "minishell.h"
#include "libft.h"

int space_presence(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == '=')
            return (1);
        i++;
    }
    return (0);
}

int parsing_export_var(char *str)
{
    if (space_presence(str))
        return (1);
    else
        return (0);
}

t_export *new_var_export(char *str)
{
    t_export	*new_export;

	new_export = (t_export *)malloc(sizeof(t_export));
	if (!new_export)
		return (NULL);
	new_export->field = get_name(str);
	new_export->content = get_content(str);
	new_export->next = NULL;
	new_export->prev = NULL;
	return (new_export);
}

int add_to_export(char *str, t_manager *manager)
{
    t_export	*lastposition;
	t_export	*new;

	new = new_var_export(str);
	if (!new)
		return (-1);
	lastposition = export_last(manager->export_first);
	lastposition->next = new;
	new->prev = lastposition;
	new->next = NULL;
    return (0);
}

int export_var(char *str, t_manager *manager)
{
    int parse_check;
    
    parse_check = parsing_export_var(str);
    if (parse_check == -1)
        return (-1);
    else if (parse_check == 1)
    {
        if (add_to_export(str, manager))
            return (-1);
        env_add_back(manager->env_first, str);
    }
    else if (parse_check == 0)
    {
        if (add_to_export(str, manager))
            return (-1);
    }
    return (0);
}
