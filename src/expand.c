/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smolines <smolines@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 16:12:46 by smolines          #+#    #+#             */
/*   Updated: 2024/12/20 16:51:47 by smolines         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "minishell.h"
#include "libft.h"

/*fonction handling the expansion, included in between quotes and in heredoc*/

int	expand(t_manager *manager, t_token *token, t_env *s_env)
{
	t_env	*current;
	int		found_something;

	found_something = 0;
	current = s_env;
	printf("\033[34mAU DEBUT dans expand - expand\033[0m\n");
	while (current)
	{
		if (*(token)->value == '?')	
		{
			printf("\033[34mdans expand - expand\033[0m\n");
			token->value = expand_errno(manager, token->value);
			found_something = 1;
		}	
		
		if (!ft_strcmp(token->value, current->field))
		{
			free(token->value);
			token->value = ft_strdup(current->content);
			found_something = 1;
			break;
		}
		current = current->next;
	}
	return (found_something);
}
char	*get_toexpand(char *str, int i)
{
	int	j;
	char *to_expand;

	j = 0;
	while (str[i + j] && !ft_is_space(str[i + j]))
		j++;
	to_expand = (char *)malloc(sizeof(char) * (j + 1));
	if (!to_expand)
		return (NULL);
	j = 0;
	while (str[i + j]  && !ft_is_space(str[i + j]))
	{
		to_expand[j] = str[i + j];
		j++;
	}
	to_expand[j] = '\0';
	return (to_expand);
}

char	*expand_exists(char *to_expand, t_env *s_env)
{
	t_env	*current;

	current = s_env;
	while (current)
	{
		if (!ft_strcmp(current->field, to_expand))
			return (current->content); 
		current = current->next;
	}
	return (NULL);
}


void	expand_dquote(t_token *current_token, t_env *s_env)
{
	char	*str;
	int		i;
	char	*to_expand;
	char	*expansion;

	str = current_token->value;
	i = 0;
	while (str && str[i])
	{
		if (str[i] == '$' && !ft_is_space(str[i + 1]) && str[i + 1] != '\0')
		{
			i++;
			to_expand = get_toexpand(str, i);
			expansion = expand_exists(to_expand, s_env);
			if (expansion)
				str = replace_expand(str, i - 1, expansion);
			else
				str = cut_expand(str, i - 1);
		}
		i++;
	}
	current_token->value = str;
}

//potentiellement fusionner avec une fonction derivee de expand_dquote
char	*expand_heredoc(char *current_line, t_env *s_env)
{
	int		i;
	char	*expansion;
	char 	*to_expand;
	i = 0;

	while (current_line && current_line[i] && current_line[i] != '\n')
	{
		if (current_line[i] == '$' && isalnum(current_line[i + 1]) 
			&& !ft_is_space(current_line[i + 1]))
		{
			i++;
			to_expand = get_toexpand(current_line, i);
			expansion = expand_exists(to_expand, s_env);
			if (expansion)
				current_line = replace_expand(current_line, i - 1, expansion);
			else
			{
				current_line = cut_expand(current_line, i - 1);
				if (!current_line)
				{
					current_line = ft_strdup("\n");
					i = 0;
				}
			}	
		}
		i++;
	}
	return (current_line);
}