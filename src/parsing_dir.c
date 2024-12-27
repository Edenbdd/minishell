/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_dir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 09:47:46 by smolines          #+#    #+#             */
/*   Updated: 2024/12/27 10:43:17 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"


int	is_a_dir(char *line, int i)
{
	while (line[i] && !ft_is_space(line[i]))
	{
		if (line[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

int handle_dir(t_manager *manager, char *line, int i, t_token *current)
{
	char	*to_test;

	if (line)
		regular_word(manager, line, i);
	if (!current)
		to_test = manager->word;
	else
		to_test = current->value;
	write(2, "bash: ", 6);
	if (current && current-> prev && current->space == 0)
		ft_putstr_fd(current->prev->value, 2);
	ft_putstr_fd(to_test, 2);
	if (access(to_test, F_OK)) //changer par access error
	{
		write(2, ": No such file or directory\n",28);
		manager->exit_status = 127;			
		return (-1);
	}
	else
	{
		write(2, ": Is a directory\n",17);
		manager->exit_status = 126;			
	}
	return (-1);
}


