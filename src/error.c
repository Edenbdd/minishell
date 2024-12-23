/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 13:22:35 by smolines          #+#    #+#             */
/*   Updated: 2024/12/23 13:03:24 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int	parsing_error_op(t_manager *manager, int code, char operator, char dble_op)
{
	if (code == 4)
	{
		if (dble_op)
		{
			write(2, "bash: ",6);
			write (2, "syntax error near unexpected token ",36);
			write (2,&operator,1);
			write (2,&dble_op,1);
			write (2,"\n",1);
		}
		else 
		{
			write(2, "bash: ",6);
			write (2, "syntax error near unexpected token ",36);
			write (2,&operator,1);
			write (2,"\n",1);
		}
		manager->exit_status = 2;	
		return (-1);
	}
	return (-1);
}
	

int parsing_error(t_manager *manager, int code)
{
	if (code == 2)
	{
			write(2, "bash: ",6);
			write (2, "syntax error near unexpected token `newline'\n",45);

		manager->exit_status = 2;
		return (-1);
	}

	if (code == 3)
	{
		manager->exit_status = 127;			
		return (-1);
	}
return (-1);
}

int access_error(t_manager *manager, int code, char *str)
{
		if (code == 5)
	{
		write(2, "bash: ",6);
		ft_putstr_fd(str, 2);
		write (2, ": Permission denied\n",20);
		manager->exit_status = 1;
		return (-1);
	}
return (-1);
}

int system_function_error(t_manager *manager, int code)
{
	(void)manager; // see if we need it later
	if (code == 1)
		write (2, "bash: open or close error\n", 26);
	else if (code == 2)
		write (2, "bash: execve error\n", 19);
	else if (code == 3)
		write (2, "bash: pipe error\n", 17);
	else if (code == 4)
		write (2, "bash: fork error\n", 17);
	else if (code == 5)
		write (2, "bash: write error\n", 18);
	else if (code == 6)
		write (2, "bash: join error\n", 17);
	else if (code == 7)
		write (2, "bash: malloc error\n", 18);	
	else if (code == 8)
		write (2, "bash: dup2 error\n", 16);	
	return (-1);
}

int cmd_error(t_manager *manager, int code, char *cmd)
{
	if (code == 6)
	{
		write(2, "bash: ",6);
		ft_putstr_fd(cmd, 2);
		write (2, ": command not found\n",20);
		manager->exit_status = 127;			
		return (-1);
	}
	return (-1);
}

