/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oplist_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 18:13:00 by smolines          #+#    #+#             */
/*   Updated: 2024/12/29 13:34:45 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Manager initialisation*/

#include "minishell.h"
#include "libft.h"

t_manager	*init_manager(t_manager *manager, t_env *first_env, int exitcode)
{
	manager->type = -1;
	manager->sec_type = -1;
	manager->word = NULL;
	manager->token_first = NULL;
	manager->size_token = -1;
	manager->cmd_first = NULL;
	manager->size_cmd = -1;
	manager->export_first = NULL;
	manager->exit_status = exitcode;
	manager->heredoc_line = 0;
	manager->env_first = first_env;
	return (manager);
}

