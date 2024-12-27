
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

// expand loop / gestion du type env_var 
int exploop_env_var(t_token *current_token, t_env *s_env, t_manager *manager)
{
    if (!expand(current_token, s_env))
    {
        current_token->value = NULL;
        if (current_token->next == NULL && current_token->prev == NULL)
            return (-1);
    }
    else
    {
        current_token->type = is_operators(manager, current_token->value, 0);
        if (current_token->type == DIREC)
            return (handle_dir(manager, NULL, 0, current_token));
        else if (current_token->type == -1)
            return (-1);
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
            if (exploop_env_var(current_token, s_env, manager) == -1)
                return (-1);
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

