/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smolines <smolines@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 10:48:16 by smolines          #+#    #+#             */
/*   Updated: 2025/01/03 13:55:24 by smolines         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//built-in for pwd

#include "minishell.h"
#include "libft.h"

int builtin_error(t_manager *manager, int code, char *who)
{
	(void)manager; // see if we need it later

	if (code == 1)
	{
		ft_putstr_fd(who, 2);
		write (2, ": no option possible\n", 29);
	}
    
	if (code == 2)
	{
		ft_putstr_fd(who, 2);
		write (2, ": error /n", 9);
	}
	
	if (code == 3)
	{
		ft_putstr_fd(who, 2);
		write (2, ": too many arguments\n", 21);
	}

	if (code == 4)
	{
		ft_putstr_fd(who, 2);
		write (2, ": argument error\n", 17);
	}


	/////////////// a confirmer
	manager->exit_status = 127;
	return (-1);
}

int new_builtin_error(t_manager *manager, char *who, char *message, char *dir)
{
	write (2, "bash :", 6);
	ft_putstr_fd(who, 2);
	write (2, ": ", 2);
	ft_putstr_fd(message, 2);
	if (dir)
	{
		write (2, ": ", 2);
		ft_putstr_fd(dir, 2);
	}
	write (2, "\n", 1);
	manager->exit_status = 127;
	return (-1);
}

