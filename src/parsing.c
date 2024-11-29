/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smolines <smolines@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 14:46:36 by smolines          #+#    #+#             */
/*   Updated: 2024/11/29 12:58:19 by smolines         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int is_operators(char c, char d)
{
//gestion des erreur || && ;
	//if ((c == '|' && d == '|') || (c == '&' && d == '&') || (c == ';'))
	//	return (-1)
	if (c == '<' && d == '<')
		return (REDIR_HEREDOC);
	if (c == '>' && d == '>')
		return (REDIR_APPEND);
	if (c == '<')
		return (REDIR_IN);
	if (c == '>')
		return (REDIR_OUT);
	if (c == '"')
		return (DOUBLE_QUOTE);
	if (c == '\'')
		return (SIMPLE_QUOTE);
	if (c == '|')
		return (PIPE);
	if (c == '$')
		return (ENV_VAR);
	return (CMD_ARG); // is 0
}

int handle_quote(char *line, int i, int type, char **word)
{
	int j;
	char separator;

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

int regular_word(char *line, int i, char **word)
{
	int j;

	j = 0;
	while (line[i + j] && !ft_is_space(line[i]) && !is_operators(line[i], line[i + 1]))
		j++;
	*word = (char *)malloc(sizeof(char) * (j + 1));
	if (!(*word))
		return (-1);
	j = 0;
	while (line[i] && !ft_is_space(line[i]) && !is_operators(line[i], line[i + 1]))
	{
		(*word)[j] = line[i];
		j++;
		i++;
	}
	(*word)[j] = '\0';
	return (i);
}

t_manager *parsing(t_manager *manager, char *line)
{
	int i;
	char *word;
	int type;

	i = 0;
	word = NULL;
	while (line[i])
	{
		type = 0;
		while (line[i] && ft_is_space(line[i]))
			i++;
		if (is_operators(line[i], line[i + 1]))
		{
			type = is_operators(line[i], line[i + 1]);
			i++;
		}
		if (type == REDIR_APPEND || type == REDIR_HEREDOC)
			i++;
		if (type == DOUBLE_QUOTE || type == SIMPLE_QUOTE)
			i = handle_quote(line, i, type, &word);
		else
			i = regular_word(line, i, &word);
		printf("word : [%s] of type [%d]\n", word, type);
		token_add_back(&(manager->token_first), token_new(word, type));
		free(word);
	}
	printf("display de la liste token\n");
	token_display(manager->token_first);
	return (manager);
}
