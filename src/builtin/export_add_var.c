/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_add_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 16:44:15 by aubertra          #+#    #+#             */
/*   Updated: 2025/01/03 18:58:27 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Functions to handle adding the new variable to the export and env 
linked list or update and updating the manager accordingly, ! parsing of the var is in a 
separate file*/

#include "minishell.h"
#include "libft.h"

t_export *new_var_export(char *str)
{
    t_export	*new_export;

	new_export = (t_export *)malloc(sizeof(t_export));
	if (!new_export)
		return (NULL);
	new_export->field = get_name(str, 1);
	new_export->content = get_content(str, equal_presence(str));
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
    int existing_var;

    existing_var = existing_export(str, manager);
    if (existing_var)
        return (existing_var);
    parse_check = parsing_export_var(str, manager);
    if (parse_check == -1)
        return (-1);
    else if (parse_check == 1)
    {
        if (add_to_export(str, manager))
            return (-1);
        env_add_back(manager->env_first, str, 1);
    }
    else if (parse_check == 0)
    {
        if (add_to_export(str, manager))
            return (-1);
    }
    return (0);
}
