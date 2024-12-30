/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oplist_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 22:30:11 by smolines          #+#    #+#             */
/*   Updated: 2024/12/23 13:42:57 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

t_env	*env_new(char *str)
{
	t_env	*new_env;

	new_env = (t_env *)malloc(sizeof(t_env));
	if (!new_env)
		return (NULL);
	new_env->field = get_name(str);
	new_env->content = get_content(str);
	new_env->next = NULL;
	new_env->prev = NULL;
	return (new_env);
}

//Add a new env node at the end of env linked list
void	env_add_back(t_env *first_env, char *str)
{
	t_env	*lastposition;
	t_env	*new;

	new = env_new(str);
	if (!first_env)
		return ;
	lastposition = env_last(first_env);
	lastposition->next = new;
	new->prev = lastposition;
	new->next	= NULL;	
}

//Find last element of env
t_env	*env_last(t_env *env)
{
	if (env == NULL)
		return (0);
	while (env->next)
		env = env->next;
	return (env);
}
void	env_display(t_env *env)
{
	if (!env)
		return ;
	while (env)
	{
		printf("env value :[%s] -- content : [%s]\n", env->field, env->content);
		env = env->next;
	}
}
