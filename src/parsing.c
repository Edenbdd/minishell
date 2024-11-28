/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smolines <smolines@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 14:46:36 by smolines          #+#    #+#             */
/*   Updated: 2024/11/28 18:10:20 by smolines         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"


int	is_operators(char c, char d)
{
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
	return (CMD_ARG); //is 0
}

int	handle_quote(char *line, int i, int flag, char *to_return)
{
	char 	*word;
	int		j;
	char	separator;

	if (flag == 1)
		separator = '\'';
	else
		separator = '"';
	j = 0;
	while (line[i + j]  && line[i] != separator)
		j++;
	word = (char *)malloc(sizeof (char) * (j + 1));
	if (!word)
		return (-1);
	j = 0;
	while (line[i] && line[i] != separator)
	{
		word[j] = line[i];
		j++;
		i++;
	}
	to_return = ft_strdup(word);
	free(word);
	return (i + 1);
}

int	regular_word(char *line, int i, char  *to_return)
{
	char 	*word;
	int		j;

	j = 0;
	while (line[i + j]  && !ft_is_space(line[i]) && !is_operators(line[i], line[i + 1]))
		j++;
	word = (char *)malloc(sizeof (char) * (j + 1));
	if (!word)
		return (-1);
	j = 0;
	while (line[i] && !ft_is_space(line[i]) && !is_operators(line[i], line[i + 1]))
	{
		word[j] = line[i];
		j++;
		i++;
	}
	word[j] = '\0';
	to_return =  ft_strdup(word);
	printf("word [%s], to return [%s]\n", word, to_return);
	free(word);
	return (i);
}

t_manager	*parsing(t_manager *manager,char *line)
{
	int		i;
	char	*word;
	int		flag;
	
	i = 0;
	word = NULL;
	while (line[i])
	{
		flag = 0;
		while(line[i] && ft_is_space(line[i]))
			i++;
		if (is_operators(line[i], line[i + 1]))
		{
			flag = is_operators(line[i], line[i + 1]);
			i++;
		}
		if (flag == REDIR_APPEND || flag == REDIR_HEREDOC)
			i++;
		if (flag == DOUBLE_QUOTE || flag == SIMPLE_QUOTE)
		{
			i = handle_quote(line, i, flag, word);
			printf("after handle quote i is %d and word is [%s]\n", i, word);
		}
		else
		{
			//word = regular_word(&line[i])
			i = regular_word(line, i, word);
			printf("after regular i is %d\n", i);
		}
		printf("word : [%s] of type [%d]\n", word, flag);
		free(word);
	}
	return (manager);
}
