/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 13:58:50 by aubertra          #+#    #+#             */
/*   Updated: 2024/12/04 14:42:31 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Parsing utils function dealing with redirections token

#include "minishell.h"
#include "libft.h"

int	handle_redir(t_manager *manager, char *line, int i, char **word)
{
	int	j;

	while (line[i] && ft_is_space(line[i]))
		i++;
	j = 0;
	while (line[i + j] && !ft_is_space(line[i + j]) 
			&& (!is_operators(manager, line, i + j) 
			|| is_operators(manager, line, i + j) == ENV_VAR))
		j++;
	*word = (char *)malloc(sizeof(char) * (j + 1));
	if (!(*word))
		return (-1);
	j = 0;
	while (line[i] && !ft_is_space(line[i]) 
			&& (!is_operators(manager, line, i) 
			|| is_operators(manager, line, i) == ENV_VAR))
	{
		(*word)[j] = line[i];
		i++;
		j++;
	}
	(*word)[j] = '\0';	
	printf("in handle redir word is [%s]\n", *word);
	return (i);
}

int	handle_lim(t_manager *manager, char *line, int i, char **word)
{
	int	type;
	
	type = 0;
	while (line[i] && ft_is_space(line[i]))
		i++;
	i = verif_operator(manager, line, i, &type);
	if (type == DOUBLE_QUOTE)
		i = handle_quote(line, i, type, word);
	else if (type == CMD_ARG)
		i = regular_word(manager, line, i, word);
	return (i);
}