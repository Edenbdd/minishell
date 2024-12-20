
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 16:12:46 by smolines          #+#    #+#             */
/*   Updated: 2024/12/13 14:18:41 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

/*
int	expand_loop(t_token *current_token, t_env *s_env, t_manager *manager)
{
	while (current_token && current_token->type != PIPE)
	{
		if (current_token->type == ENV_VAR)
		{
			if (!expand(current_token, s_env))
			{
				current_token->value = NULL;
				if (current_token->next == NULL 
					&& current_token->prev == NULL)
					return (-1);
			}
			else
			{
				current_token->type = is_operators(manager, current_token->value, 0);
				if (current_token->type == DIR)
					return (handle_dir(manager, NULL, 0, current_token));
			}
		}
		else if (current_token->type == DOUBLE_QUOTE)
		{
			expand_dquote(current_token, s_env);
			if (current_token->value == NULL)
				return (cmd_error(manager, 6, NULL));
		}
		current_token = current_token->next;
	}
	return (0);
}
*/


// expand loop / gestion du type env_var 
int exploop_env_var(t_token *current_token, t_env *s_env, t_manager *manager)
{
//     printf("\033[34mcoucou je suis dans fill cmd expand - exloop_env_var\033[0m\n");
    if (!expand(manager, current_token, s_env))
	{
//     printf("\033[34mcoucou je suis dans fill cmd expand - exloop_env_var\033[0m\n");
        current_token->value = NULL;
		if (current_token->next == NULL && current_token->prev == NULL)
            return (-1);
    }
    else
    {
//		printf("\033[34mcoucou je suis dans fill cmd expand - exloop_env_var - ELSE\033[0m\n");
		current_token->type = is_operators(manager, current_token->value, 0);
		if (current_token->type == DIR)
			return (handle_dir(manager, NULL, 0, current_token));
	}
	return (0);
}

// expand loop : gestion du type double quote
int exploop_dquote(t_token *current_token, t_env *s_env, t_manager *manager)
{
    if (current_token->type == DOUBLE_QUOTE)
    {
        expand_dquote(current_token, s_env);
        if (current_token->value == NULL)
            return (cmd_error(manager, 6, NULL));
    }
    return (0);
}

int expand_loop(t_token *current_token, t_env *s_env, t_manager *manager)
{
    while (current_token && current_token->type != PIPE)
    {
        if (current_token->type == ENV_VAR)
        {
             printf("\033[34mcoucou je suis dans fill cmd expand - expand-loop\033[0m\n");
            if (exploop_env_var(current_token, s_env, manager) == -1)
            {
                    // printf("\033[34met la je return\033[0m\n");
                return (-1);
            }
        }
        else
        {
            if (exploop_dquote(current_token, s_env, manager) == -1)
                return (-1);
        }
        current_token = current_token->next;
    }
    return (0);
}

