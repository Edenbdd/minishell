/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smolines <smolines@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 17:20:46 by smolines          #+#    #+#             */
/*   Updated: 2025/01/02 20:08:58 by smolines         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//built-in for echo

#include "minishell.h"
#include "libft.h"

int	isthere_only_n(char *str, char c)
{
	size_t	i;

	i = 2;
	while (str[i])
	{
		if (str[i] != c)
			return (0);
		i++;
	}
	return (1);
}

int echo_isthere_n(t_cmd *cmd)
{
	int option_n;
	
	if (cmd->args[1][0] == '-' && cmd->args[1][1] == 'n'
		&& isthere_only_n(cmd->args[1], 'n'))
		option_n = 1;
	else
        option_n = 0;
	return (option_n);
}

int skip_n(t_cmd *cmd)
{
	int i;

	i = 2;
	while (cmd->args[i])
	{
		if (cmd->args[i][0] == '-' && cmd->args[i][1] == 'n'
			&& isthere_only_n(cmd->args[i], 'n'))
				i++;
		else
			return (i);
	}
	return (i);
}



int handle_echo(t_manager *manager, t_cmd *cmd)
{

	printf("display de la liste d'arguments : \n");
	cmd_args_display(cmd);
	
	int 	real_arg;
//	int		len_to_print; 
//	char 	*line_to_print;

	(void)manager;	
	if (echo_isthere_n(cmd) == 1)
			real_arg = skip_n(cmd);
	else 
			real_arg = 1;

while (cmd->args[real_arg])
{
	ft_putstr_fd(cmd->args[real_arg], 1);
	real_arg++;
	if (cmd->args[real_arg])
		ft_putstr_fd(" ", 1);
}

if (echo_isthere_n(cmd) == 0)
	ft_putstr_fd("\n", 1);

    return (0);
}
