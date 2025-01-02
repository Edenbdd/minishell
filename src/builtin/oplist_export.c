/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oplist_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 14:35:01 by aubertra          #+#    #+#             */
/*   Updated: 2025/01/02 15:21:33 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

t_export    *env_to_export(t_env *first_env)
{
    t_export    *first_export;
    t_env       *current_env;
    int         i;

    current_env = first_env;
    i = 0;
    while (current_env)
    {
        if (i == 0)
            first_export = export_new(first_env);
        else
            export_add_back(first_export, current_env);
        i++;
        current_env = current_env->next;
    }
    return (first_export);;
}

t_export	*export_new(t_env *current_env)
{
	t_export	*new_export;

	new_export = (t_export *)malloc(sizeof(t_export));
	if (!new_export)
		return (NULL);
	new_export->field = ft_strdup(current_env->field);
	new_export->content = ft_strdup(current_env->content);
	new_export->next = NULL;
	new_export->prev = NULL;
	return (new_export);
}

//Add a new export node at the end of export linked list
void	export_add_back(t_export *first_export, t_env *current_env)
{
	t_export	*lastposition;
	t_export	*new;

	new = export_new(current_env);
	if (!first_export)
		return ;
	lastposition = export_last(first_export);
	lastposition->next = new;
	new->prev = lastposition;
	new->next	= NULL;	
}

//Find last element of export
t_export	*export_last(t_export *export)
{
	if (!export)
		return (NULL);
	while (export->next)
		export = export->next;
	return (export);
}
void	export_display(t_export *export)
{
	if (!export)
		return ;
	while (export)
	{
		printf("export %s=\"%s\"\n", export->field, export->content);
		export = export->next;
	}
}
