/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smolines <smolines@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 14:46:36 by smolines          #+#    #+#             */
/*   Updated: 2024/11/28 16:03:29 by smolines         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"


int	is_operators(char c)
{

	if (c == '<')
		return (REDIR_OUT);
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


t_manager	*parsing(t_manager *manager,char *line)
{
	int		i;
	int		j;
	char	*word;
	int		flag;
	
	i = 0;
	while (line[i])
	{
		flag = 0;
		while(line[i] && ft_is_space(line[i]))
			i++;
		if (is_operators(line[i]))
		{
			flag = is_operators(line[i]);
			i++;
		}
		j = 0;
		while (line[i + j]  && !ft_is_space(line[i]) && !is_operators(line[i]))
			j++;
		word = (char *)malloc(sizeof (char) * (j + 1));
		if (!word)
			return (NULL);
		j = 0;
		while (line[i] && !ft_is_space(line[i]) && !is_operators(line[i]))
		{
		printf("in the last loop\n");
			word[j] = line[i];
			j++;
			i++;
		}
		word[j] = '\0';
		printf("word : [%s] of type [%d]\n", word, flag);
		free(word);
	}


	return (manager);
}
