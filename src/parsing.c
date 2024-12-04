/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 14:46:36 by smolines          #+#    #+#             */
/*   Updated: 2024/12/04 16:57:46 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"


//recuperer les doubles operateurs
int	verif_operator(t_manager *manager, char *line, int i, int *type)
{
	if 	(is_operators(manager, line, i) == -1)
			return (-1);
	else if (is_operators(manager, line, i))
	{
		*type = is_operators(manager, line, i);
		i++;
	}
	return (i);
}

//parser la chaine de caractere saisie
int	parsing(t_manager *manager, char *line)
{
	int		i;
	char	*word;
	int		type;

	i = 0;
	word = NULL;
	if (line[0] == '\0')
		return (parsing_error(manager, 3));
	if ((count_quotes(manager, line, 34, 39) == -1) || (count_quotes(manager, line, 39, 34) % 2 == -1))
		return (-1);
	while (line[i])
	{
		type = 0;
		while (line[i] && ft_is_space(line[i]))
			i++;
		i = verif_operator(manager, line, i, &type);
		if (i == -1)
			return (-1);
		if (type == DOUBLE_QUOTE || type == SIMPLE_QUOTE)
			i = handle_quote(line, i, type, &word);
		else if (type == REDIR_IN || type == REDIR_OUT 
			|| type == REDIR_APPEND || type == REDIR_HEREDOC)
		{
			if (type == REDIR_APPEND || type == REDIR_HEREDOC)
				i++;
			if (type == REDIR_HEREDOC)
				i = handle_lim(manager, line, i, &word);
			else
				i = handle_redir(manager, line, i, &word);
		}
		else
			i = regular_word(manager, line, i, &word);
		token_add_back(&(manager->token_first), token_new(word, type));
		free(word);
	}
	return (0);
}
