/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 16:12:46 by smolines          #+#    #+#             */
/*   Updated: 2024/12/05 13:13:27 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	expand(t_token *token, t_env *s_env)
{
	t_env	*current;
	
	current = s_env;
	while (current)
	{
		if (!ft_strcmp(token->value, current->field))
		{
			free(token->value);
			token->value = ft_strdup(current->content);
			break;
		}
		current = current->next;
		// si pas de correspondance trouvee entre current->content et token->value : ERROR status =0 command not found
	}
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
	return (to_expand);
}

//int	(char *str, char *to_expand)
//{
//}

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


char	*replace_expand(char *str, int pos, char *expansion)
{
	char	*result;
	int		i;
	int		j;
	int		k;
	int		l;

	i = 0;
	j = 0;
	while (str[j + i])
	{	
		if ((j + i) == pos)
		{
			while (str[i + j] && !ft_is_space(str[i + j]))
				j++;
		}
		i++;
	}
	result = (char *)malloc(sizeof(char) * (i + ft_strlen(expansion) + 1));
	if (!result)
		return (NULL);
	j = 0;
	k = 0;
	l = 0;
	while (str[j])
	{	
		if (j == pos)
		{
			while (str[j] && !ft_is_space(str[j]))
			{
				j++;
			}
			while (expansion[k])
			{
				result[l] = expansion[k];
				k++;
				l++;
			}
		}
		result[l] = str[j];
		l++;
		j++;
	}
	result[i + j] = '\0';
	return (result);	
}

char	*cut_expand(char *str, int pos)
{
	char	*result;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	while (str[j + i])
	{	
		if ((j + i) == pos)
		{
			while (str[i + j] && !ft_is_space(str[i + j]))
				j++;
		}
		i++;
	}
	result = (char *)malloc(sizeof(char) * (i - j + 1));
	if (!result)
		return (NULL);
	j = 0;
	k = 0;
	i = 0;
	while (str[j])
	{	
		if (j == pos)
		{
			while (str[j] && !ft_is_space(str[j]))
				j++;
		}
		result[i] = str[j];
		i++;
		j++;
	}
	result[j] = '\0';
	return (result);	
}


void	expand_dquote(t_token *current_token, t_env *s_env)
{
	char	*str;
	int		i;
	char	*to_expand;
	char	*expansion;

	str = current_token->value;
	i = 0;
	while (str[i])
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
}