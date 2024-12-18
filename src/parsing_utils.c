/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 09:47:46 by smolines          #+#    #+#             */
/*   Updated: 2024/12/18 20:24:20 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

//Utils de parsing lies au operators, quotes et regular word (cmd/arg)



//a revoir entierement car pb avec count quote -> il me faut une nouvelle fonction pour le heredoc
int	handle_quote(char *line, int i, t_manager *manager)
{
	int		j;
	char	separator;
	int		sec_type;

	// printf("line [%s]\n", line);
	// printf("type is %d\n", manager->type);
	sec_type = is_operators(manager, line, i);
	// printf("after update type is %d\n", sec_type);
	if (sec_type == 1)
		separator = '\'';
	else
		separator = '"';
	// printf("sep is [%c]\n", separator);
	j = 0;
	if (line[i + j] == separator)
		j++;
	// printf("char is now [%c]\n", line[i + j]);
	while (line[i + j] && line[i + j] != separator)
		j++;
	if (j == 0)
		return (cmd_error(manager, 6, ""));
	// printf("j is %d\n", j);
	manager->word = (char *)malloc(sizeof(char) * (j + 1));
	if (!manager->word)
		return (-1);
	j = 0;
	i++;
	while (line[i] && line[i] != separator)
	{
		manager->word[j] = line[i];
		j++;
		i++;
	}
	manager->word[j] = '\0';
	// printf("end of handle word, word is [%s]\n", manager->word);
	return (i + 1);
}

//recuperer un token "mot"
int	regular_word(t_manager *manager, char *line, int i)
{
	int	j;

	j = 0;
	while (line[i + j] && !ft_is_space(line[i]) 
			&& (!is_operators(manager, line, i)
			|| is_operators(manager, line, i) == DIR))
		j++;
	manager->word = (char *)malloc(sizeof(char) * (j + 1));
	if (!manager->word)
		return (-1);
	j = 0;
	while (line[i] && !ft_is_space(line[i]) 
			&& (!is_operators(manager, line, i)
			|| is_operators(manager, line, i) == DIR))
	{
		manager->word[j] = line[i];
		j++;
		i++;
	}
	manager->word[j] = '\0';
	return (i);
}

//compter les quotes hors other quotes
int	count_quotes(t_manager *manager, char *line, char quote1, char quote2)
{
	int dquote;
	int i;

	(void)quote2;
	dquote = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == quote1)
			dquote++;
		// if (line[i] == quote2)
		// 	{
		// 		i++;
		// 		while (line[i] && line[i] != quote2)
		// 		i++;
		// 	}
		i++;
	}
	if (dquote % 2 != 0)
	{
		// printf("is it in count quotes?\n");
		return (parsing_error_op(manager, 4, quote1, 0)); // OK comportement indefini de bash
	}
	return (dquote);
}
