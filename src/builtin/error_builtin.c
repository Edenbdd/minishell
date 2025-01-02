/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smolines <smolines@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 10:48:16 by smolines          #+#    #+#             */
/*   Updated: 2025/01/02 14:56:28 by smolines         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

//built-in for pwd

#include "minishell.h"
#include "libft.h"

int builtin_error(t_manager *manager, int code, char *who)
{
	(void)manager; // see if we need it later

	if (code == 1)
	{
		ft_putstr_fd(who, 2);
		write (2, ": no option possible for pwd\n", 29);
	}
    
	if (code == 2)
	{
		ft_putstr_fd(who, 2);
		write (2, ": error /n", 9);
	}
	
	/////////////// a confirmer
	manager->exit_status = 127;
	return (-1);
}