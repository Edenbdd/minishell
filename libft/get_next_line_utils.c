/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 10:36:05 by aubertra          #+#    #+#             */
/*   Updated: 2024/11/19 16:34:35 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	gnl_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*gnl_strchr(char *s, int c)
{
	int	len;
	int	i;

	i = 0;
	len = gnl_strlen((char *)s) + 1;
	while (i < len)
	{
		if (s[i] == (char)c)
			return ((char *)s + i + 1);
		i++;
	}
	return (NULL);
}

char	*gnl_strdup(char *s)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = malloc(sizeof(char) * gnl_strlen(s) + 1);
	if (!tmp)
		return (NULL);
	while (s[i])
	{
		tmp[i] = s[i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}

char	*gnl_strjoin(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	str = malloc(sizeof(char) * (gnl_strlen(s1) + gnl_strlen(s2)) + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		str[i] = s2[j];
		j++;
		i++;
	}
	str[i] = '\0';
	free(s1);
	return (str);
}

void	*gnl_calloc(size_t nmemb, size_t size)
{
	size_t			i;
	unsigned char	*ptr;

	i = 0;
	if (size == 0 || nmemb == 0)
		return (malloc(0));
	if ((size * nmemb) < size || (size * nmemb) < nmemb)
		return (NULL);
	ptr = malloc(size * nmemb);
	if (!ptr)
		return (free(ptr), NULL);
	while (i < nmemb * size)
	{
		ptr[i] = 0;
		i++;
	}
	return (ptr);
}
