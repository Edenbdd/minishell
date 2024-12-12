/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 14:46:36 by smolines          #+#    #+#             */
/*   Updated: 2024/12/12 13:59:35 by aubertra         ###   ########.fr       */
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

int	is_symbols(char c)
{
	if (c == ':' || c == '!')
		return (1);
	return (0);
}

int	only_space_symbols(char *str)
{
	while (*str)
	{
		if (!ft_is_space(*str) && !is_symbols(*str))
			return (0);
		str++;	
	}
	return (1);
}


//parser la chaine de caractere saisie
int	parsing(t_manager *manager, char *line)
{
	int		i;
	char	*word;

	i = 0;
	word = NULL;
	if (line[0] == '\0')
		return (parsing_error(manager, 3)); //ok
	if (only_space_symbols(line))
		return (-1);
	// if (dir_path(manager, line))
	// 	return (-1);
	if ((count_quotes(manager, line, 34, 39) == -1) || (count_quotes(manager, line, 39, 34) % 2 == -1))
		return (-1);
	while (line[i])
	{
		manager->type = 0;
		while (line[i] && ft_is_space(line[i]))
			i++;
		i = verif_operator(manager, line, i, &(manager->type));
		// printf("after verif manager->type is %d\n", manager->type);
		if (i == -1)
			return (-1);
		if (manager->type == DOUBLE_QUOTE || manager->type == SIMPLE_QUOTE)
			i = handle_quote(line, i, manager->type, &word);
		else if (manager->type == REDIR_IN || manager->type == REDIR_OUT 
			|| manager->type == REDIR_APPEND || manager->type == REDIR_HEREDOC)
		{
			if (manager->type == REDIR_APPEND || manager->type == REDIR_HEREDOC)
				i++;
			i = handle_redir(manager, line, i, &word);
		}
		else if (manager->type == PIPE)
			i = handle_pipe(manager, line, i, &word);
		// else if (manager->type == DIR)
		// 	/////////////////////////////
		else
			i = regular_word(manager, line, i, &word);
		if (i == -1)
			return (-1);
		token_add_back(&(manager->token_first), token_new(word, manager->type));
		free(word);
	}
	return (0);
}
