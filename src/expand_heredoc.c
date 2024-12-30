/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 14:02:24 by aubertra          #+#    #+#             */
/*   Updated: 2024/12/23 14:11:08 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

char    *expand_line(char *current_line, int *i, t_env  *s_env)
{
    char	*expansion;
	char 	*to_expand;

    to_expand = get_toexpand(current_line, *i);
    expansion = expand_exists(to_expand, s_env);
    free(to_expand);
    if (expansion)
        current_line = replace_expand(current_line, *i - 1, expansion);
    else
    {
        current_line = cut_expand(current_line, *i - 1);
        if (!current_line)
        {
            current_line = ft_strdup("\n");
            *i = 0;
        }
    }
    return (current_line);
}

char	*expand_heredoc(char *current_line, t_env *s_env)
{
	int		i;
	int		went_in_if;

	i = 0;
	went_in_if = 0;
	while (current_line && current_line[i] && current_line[i] != '\n')
	{
		if (current_line[i] == '$' && isalnum(current_line[i + 1]) 
			&& !ft_is_space(current_line[i + 1]))
        {
            i++;
            went_in_if++;
            current_line = expand_line(current_line, &i, s_env);
        }
        i++;
	}
	if (went_in_if == 0)
		return (ft_strdup(current_line));
	return (current_line);
}


// /*Original funciton (too long)*/
// char	*expand_heredoc(char *current_line, t_env *s_env)
// {
// 	int		i;
// 	char	*expansion;
// 	char 	*to_expand;
// 	int		went_in_if;
// 	char	*result;

// 	i = 0;
// 	went_in_if = 0;
// 	while (current_line && current_line[i] && current_line[i] != '\n')
// 	{
// 		if (current_line[i] == '$' && isalnum(current_line[i + 1]) 
// 			&& !ft_is_space(current_line[i + 1]))
// 		{
// 			i++;
// 			went_in_if++;
// 			to_expand = get_toexpand(current_line, i);
// 			expansion = expand_exists(to_expand, s_env);
// 			free(to_expand);
// 			if (expansion)
// 				current_line = replace_expand(current_line, i - 1, expansion);
// 			else
// 			{
// 				current_line = cut_expand(current_line, i - 1);
// 				if (!current_line)
// 				{
// 					current_line = ft_strdup("\n");
// 					i = 0;
// 				}
// 			}	
// 		}
// 		i++;
// 	}
// 	if (went_in_if == 0)
// 	{
// 		result = ft_strdup(current_line);
// 		return (result);
// 	}
// 	return (current_line);
// }