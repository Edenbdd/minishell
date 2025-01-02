/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 15:06:24 by aubertra          #+#    #+#             */
/*   Updated: 2025/01/02 15:19:55 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int handle_builtin_export(t_manager *manager, t_cmd *cmd)
{
    if (!ft_strcmp(cmd->args[0], "export") && !cmd->args[1])
        export_display(manager->export_first);
    return (0);
}