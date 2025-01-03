/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_dir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 09:47:46 by smolines          #+#    #+#             */
/*   Updated: 2025/01/03 09:08:35 by aubertra         ###   ########.fr       */
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
	if (access(to_test, F_OK) == -1) //changer par access error
		return (access_error(manager, 6, to_test, "bash"));
	return (i + ft_strlen(to_test));
}
