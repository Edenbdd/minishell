/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smolines <smolines@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 10:48:19 by smolines          #+#    #+#             */
/*   Updated: 2025/01/02 14:56:27 by smolines         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

//built-in for cd

#include "minishell.h"
#include "libft.h"

int handle_cd(t_manager *manager, t_cmd *cmd)
{
    
   //aller au repertoire home
if (!(cmd->args[1])) || (ft_strcmp(cmd->args[1], "~"))
{
 
}

   //aller au repertoire precedant
if (ft_strcmp(cmd->args[1], "-"))
{
 
}

//changer de repertoire
if (chdir(cmd->args[1]) != 0) {
    return (builtin_error(manager, 2, "cd"));


    return (0);
}