/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oplist_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 18:13:00 by smolines          #+#    #+#             */
/*   Updated: 2024/12/12 17:34:41 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//a mon avis ca va se transformer en oplist_manager car les init des differentes
//struct sont dans leur fichier oplist

#include "minishell.h"
#include "libft.h"

t_manager	*init_manager(t_manager *manager)
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
	return (manager);
}

