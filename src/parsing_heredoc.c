/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 15:17:44 by aubertra          #+#    #+#             */
/*   Updated: 2024/12/21 13:37:57 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Fonctions necessaires au parsing du limiter (cmd->lim) associe au heredoc,
notamment la gestion des quotes et des $*/

#include "minishell.h"
#include "libft.h"

/*Find limiter size once unused $ and quotes are removed*/
int	get_size_lim(char *limiter)
{
	int	count_char;
	int	i;

	count_char = 0;
	i = 0;
	while (limiter[i])
	{
		if (limiter[i] == '\'' || limiter[i] == '"')
			i++;
		else if (limiter[i + 1] && limiter[i] == '$' 
			&& (limiter[i + 1] == '\'' || limiter[i + 1] == '"') 
			&& !quotes_before(limiter, i - 1))
			i += 2;
		else
		{
			count_char++;
			i++;
		}
	}
	return (count_char);	
}
int		quotes_before(char *str, int i)
{
	while (i >= 0)
	{
		if (str[i] == '"')
			return (1);
		i--;
	}
	return (0);
}

/*Fill the limiter*/
char	*fill_lim(char *limiter, t_manager *manager, int i)
{
	int	count_char;
	char *clean_lim;

	clean_lim = (char *)malloc(sizeof(char) * (get_size_lim(limiter) + 1));
	if (!clean_lim)
	{
		open_close_error(manager, 7);
		return (NULL);
	}
	count_char = 0;
	while (limiter[i])
	{
		if (limiter[i] != '$' && limiter[i] != '\'' && limiter[i] != '"')
		{
			clean_lim[count_char] = limiter[i];
			i++;
			count_char++;
		}
		else if (limiter[i - 1] && limiter[i - 1] == '$' && limiter[i] == '$')
		{
			clean_lim[count_char] = limiter[i];
			i++;
			count_char++;
		}
		else if (limiter[i + 1] && (limiter[i + 1] == '$' && limiter[i] == '$'))
		{
			clean_lim[count_char] = limiter[i];
			i++;
			count_char++;
		}
		else if (limiter[i] == '\'' || limiter[i] == '"')
			i++;
		else if (limiter[i + 1] && limiter[i] == '$' 
			&& (limiter[i + 1] == '\'' || limiter[i + 1] == '"'))
			i += 2;
		else
		{
			clean_lim[count_char] = limiter[i];
			i++;
			count_char++;
		}
	}
	clean_lim[count_char] = '\0';
	// printf("clean lim is [%s] with i %d char malloc\n", clean_lim, i);
	return (clean_lim);
}

/*Check for uneven quotes number and clean the limiter*/
int	parse_lim(t_token *current_token, t_cmd *cmd, t_manager *manager)
{
	char	*limiter;
	int		i;

	cmd->heredoc_count++;
	if (check_heredoc(manager) == - 1)
		return (-1);
	limiter = ft_strdup(current_token->value);
	if (!limiter)
		return (-1);
	if (count_quotes(manager, limiter, 34, 39) == -1 //check nb de quotes impair
		|| count_quotes(manager, limiter, 39, 34) == -1)
        return (-1);
	if (count_quotes(manager, limiter, 34, 39) > 0 //check nb de quotes impair
		|| count_quotes(manager, limiter, 39, 34) > 0)
		cmd->heredoc_quotes++;
	i = 0;
	cmd->lim = fill_lim(limiter, manager, i);
	if (!cmd->lim)
		return (-1);
	free(limiter);
    printf("at the end of parse_lim, cmd->lim is [%s]\n", cmd->lim);
	return (0);
}

int	heredoc_quotes(char *line, int i, t_manager *manager)
{
	int		j;
	char	*limiter;

	j = 0;
	// printf("starting char is [%c]\n", line[i + j]);
	while (line[i + j] && !ft_is_space(line[i + j]))
		j++;
	limiter = (char *)malloc(sizeof(char) * (j + 1));
	if (!limiter)
		return (-1);
	// printf("j is %d\n", j);
	j = 0;
	while (line[i + j] && !ft_is_space(line[i + j]))
	{	
		limiter[j] = line[i + j];
		j++;
	}
	limiter[j] = '\0';
	manager->word = limiter;
    // printf("at the end of heredoc quotes, word is [%s]\n", manager->word);
	return (i + j + 1);
}
