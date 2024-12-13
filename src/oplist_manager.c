/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oplist_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smolines <smolines@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 18:13:00 by smolines          #+#    #+#             */
/*   Updated: 2024/12/12 18:36:32 by smolines         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//a mon avis ca va se transformer en oplist_manager car les init des differentes
//struct sont dans leur fichier oplist

#include "minishell.h"
#include "libft.h"

t_manager	*init_manager(t_manager *manager, t_env first_env)
{
	manager->type = -1;
	manager->sec_type = -1;
	manager->token_first = NULL;
	manager->token_last = NULL;
	manager->size_token = -1;
	manager->cmd_first = NULL;
	manager->cmd_last = NULL;
	manager->size_cmd = -1;
	manager->export_first = NULL;
	manager->export_last = NULL;
	manager->size_export = -1;
	manager->exit_status = 0;
	manager->env_first = &first_env;
	return (manager);
}

