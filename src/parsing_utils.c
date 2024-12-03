/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smolines <smolines@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 09:47:46 by smolines          #+#    #+#             */
/*   Updated: 2024/12/03 09:50:05 by smolines         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

//checker les operateurs non geres
int check_operator_err(t_manager *manager, char *line, int i)
{
	if ((line[i] == '|' && line[i + 1] == '|') 
		|| (line[i] == '&' && line[i + 1] == '&')
		|| (line[i] == ';') || (line[i] == '#') || (line[i] == '\\')
		|| (line[i] == '<' && line[i + 1] == '<' && line[i + 2] == '<')
		|| (line[i] == '>' && line[i + 1] == '>' && line[i + 2] == '>'))
			return (parsing_error(manager, 1));
	return (0);
}

//recuperer un toker "operator"
int	is_operators(t_manager *manager, char *line, int i)
{
	if (check_operator_err(manager, line, i) == -1)
		return (-1);
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

//recuperer un toker "entre quote"
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

//recuperer un token "mot"
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

//compter les quotes hors other quotes
int	count_quotes(t_manager *manager, char *line, char quote1, char quote2)
{
	int dquote;
	int i;

	dquote = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == quote1)
			dquote++;
		if (line[i] == quote2)
			{
				i++;
				while (line[i] && line[i] != quote2)
				i++;
			}
		i++;
	}
	if (dquote % 2 != 0)
		return (parsing_error(manager, 2));
	return (dquote);
}