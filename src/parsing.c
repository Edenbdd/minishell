/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smolines <smolines@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 14:46:36 by smolines          #+#    #+#             */
/*   Updated: 2024/12/02 15:19:55 by smolines         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"


int	is_operators(t_manager *manager, char *line, int i)
{
	if ((line[i] == '|' && line[i + 1] == '|') 
		|| (line[i] == '&' && line[i + 1] == '&')
		|| (line[i] == ';') || (line[i] == '#') || (line[i] == '\\')
		|| (line[i] == '<' && line[i + 1] == '<' && line[i + 2] == '<')
		|| (line[i] == '>' && line[i + 1] == '>' && line[i + 2] == '>'))
			return (parsing_error(manager, 1));
	if (line[i] == '<' && line[i + 1] == '<')
		return (REDIR_HEREDOC);
	if (line[i] == '>' && line[i + 1] == '>')
		return (REDIR_APPEND);
	if (line[i] == '<')
		return (REDIR_IN);
	if (line[i] == '>')
		return (REDIR_OUT);
	if (line[i] == '"')
		return (DOUBLE_QUOTE);
	if (line[i] == '\'')
		return (SIMPLE_QUOTE);
	if (line[i] == '|')
		return (PIPE);
	if (line[i] == '$')
		return (ENV_VAR);
	return (CMD_ARG); // is 0
}

int	handle_quote(char *line, int i, int type, char **word)
{
	int		j;
	char	separator;

	if (type == 1)
		separator = '\'';
	else
		separator = '"';
	j = 0;
	while (line[i + j] && line[i] != separator)
		j++;
	*word = (char *)malloc(sizeof(char) * (j + 1));
	if (!(*word))
		return (-1);
	j = 0;
	while (line[i] && line[i] != separator)
	{
		(*word)[j] = line[i];
		j++;
		i++;
	}
	(*word)[j] = '\0';
	return (i + 1);
}

int	regular_word(t_manager *manager, char *line, int i, char **word)
{
	int	j;

	j = 0;
	while (line[i + j] && !ft_is_space(line[i]) && !is_operators(manager, line, i))
		j++;
	*word = (char *)malloc(sizeof(char) * (j + 1));
	if (!(*word))
		return (-1);
	j = 0;
	while (line[i] && !ft_is_space(line[i]) && !is_operators(manager, line, i))
	{
		(*word)[j] = line[i];
		j++;
		i++;
	}
	(*word)[j] = '\0';
	return (i);
}


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


t_manager	*parsing(t_manager *manager, char *line)
{
	int		i;
	char	*word;
	int		type;

	i = 0;
	word = NULL;
	while (line[i])
	{
		type = 0;
		while (line[i] && ft_is_space(line[i]))
			i++;
		i = verif_operator(manager, line, i, &type);
			if (type == REDIR_APPEND || type == REDIR_HEREDOC)
			i++;
		if (type == DOUBLE_QUOTE || type == SIMPLE_QUOTE)
			i = handle_quote(line, i, type, &word);
		else
			i = regular_word(manager, line, i, &word);
		printf("word : [%s] of type [%d]\n", word, type);
		token_add_back(&(manager->token_first), token_new(word, type));
		free(word);
	}
	printf("display de la liste token\n");
	token_display(manager->token_first);
	return (manager);
}
