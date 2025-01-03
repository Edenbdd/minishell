/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smolines <smolines@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 15:32:13 by smolines          #+#    #+#             */
/*   Updated: 2025/01/03 17:28:41 by smolines         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//built-in for exit

#include "minishell.h"
#include "libft.h"


int exit_and_free_all(t_manager *manager, t_cmd *cmd)
{
		write (1, "exit\n", 5);
		close_fds(cmd, NULL, manager, 0);
		free_manager(manager);
		free_env(manager->env_first);
//		rl_clear_history();
		exit (manager->exit_status);
}

int is_arg_a_nb(char *cmd)
{
	int i;

	i = 0;
	if (cmd[0] == '-' || cmd[0] == '+')
			i++;
	while (cmd[i])
	{
		if (cmd[i] >= '0' && cmd[i] <= '9')
			i++;
		else return (1);
	}
	return (0);
}

long long	almost_atoll(const char *nptr, int *error)
{
	int	i;
	int	sign;
	long long int	nb;

	i = 0;
	sign = 1;
	nb = 0;
	while (nptr[i] && (nptr[i] == ' ' || (nptr[i] >= '\t' && nptr[i] <= '\r')))
		i++;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-')
		sign = -1;
	if (nptr[i] == '-' || nptr[i] == '+')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		nb = nb * 10 + (nptr[i] - 48);
		i++;
	}
	nb = nb * sign;
	
	if ((sign == 1 && nb < 0) || (sign == -1 && nb > 0))
			*error = 1;
	return (nb);
}

int     handle_exit(t_manager *manager, t_cmd *cmd)
{
	int	nb_arg;
	long long int	arg_exit;
	int error;

	arg_exit = 0;
	error = 0;
	nb_arg = count_cmd_args(cmd);
	if (!cmd->args[1])
		exit_and_free_all(manager, cmd);
	if (is_arg_a_nb(cmd->args[1]) != 0)
		return (new_builtin_error(manager, "exit", cmd->args[1], "numeric argument required"));
	if (nb_arg > 2) 
		return (new_builtin_error(manager, "exit", "too many arguments", NULL));
	if (cmd->args[1])
	{
		arg_exit = almost_atoll(cmd->args[1], &error);
		if (error == 1)
			return (new_builtin_error(manager, "exit", cmd->args[1], "numeric argument required"));
		manager->exit_status = arg_exit % 256;
		exit_and_free_all(manager, cmd);
	}
		manager->exit_status = arg_exit;
		exit_and_free_all(manager, cmd);
    return (0);
}
