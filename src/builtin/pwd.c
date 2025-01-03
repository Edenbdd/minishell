/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smolines <smolines@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 10:48:16 by smolines          #+#    #+#             */
/*   Updated: 2025/01/02 11:34:47 by smolines         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

//built-in for pwd

#include "minishell.h"
#include "libft.h"


int     handle_pwd(t_manager *manager, t_cmd *cmd)
{
	char	*cwd;
	if (cmd->args[1] && cmd->args[1][0] == '-')
        return (new_builtin_error(manager, "pwd", cmd->args[1], "invalid option"));
	cwd = getcwd(NULL, 0);
	printf("cwd is : %s\n", cwd);
	if (!cwd)
   		return (new_builtin_error(manager, "pwd", "error", NULL));
	ft_putstr_fd(cwd, 1);
	ft_putstr_fd("\n", 1);
	free(cwd);

    return (0);
}


