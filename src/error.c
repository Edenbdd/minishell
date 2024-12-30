/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 13:22:35 by smolines          #+#    #+#             */
/*   Updated: 2024/12/30 16:30:11 by aubertra         ###   ########.fr       */
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
			write (2, "syntax error near unexpected token ", 36);
			write (2,&operator,1);
			write (2,&dble_op,1);
			write (2,"\n",1);
		}
		else 
		{
			write(2, "bash: ",6);
			write (2, "syntax error near unexpected token " ,36);
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
	write(2, "bash: ",6);
	ft_putstr_fd(str, 2);
	if (code == 5)
	{
		write (2, ": Permission denied\n", 20);
		manager->exit_status = 1;
	}
	else if (code == 6)
	{
		write(2, ": No such file or directory\n", 28);
		manager->exit_status = 127;			
	}
	else if (code == 7)
	{
		write(2, ": Is a directory\n", 17);
		manager->exit_status = 126;			
	}
	return (-1);
}
//virer le manager qu on a jamais utilise
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
	else if (code == 9)
		write (2, "bash: opendir error\n", 19);
	return (-1);
}

int cmd_error(t_manager *manager, char *cmd, int exec_flag)
{
	if (exec_flag == 0)
	{
		write(2, "bash: ",6);
		ft_putstr_fd(cmd, 2);
		write (2, ": command not found\n", 20);
		manager->exit_status = 127;
	}
	if (exec_flag == 1)
	{
		free_env(manager->env_first);
		free_manager(manager);
		exit(127);
	}
	return (-1);
}

