/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 15:08:27 by aubertra          #+#    #+#             */
/*   Updated: 2024/03/07 14:02:00 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_all(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{	
		free(str[i]);
		i++;
	}
	free(str);
}

static int	count_words(const char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] && str[i] != c)
		{
			count++;
			while (str[i] && str[i] != c)
				i++;
		}
		else
			i++;
	}
	return (count);
}

static int	count_char(const char *str, char c, int index)
{
	int	count;

	count = 0;
	while (str[index] && str[index] != c)
	{
		count++;
		index++;
	}
	return (count);
}

static char	*ft_strndup(const char *str, int index, int n)
{
	int		i;
	char	*tab;

	tab = malloc(sizeof (char) * (n + 1));
	i = 0;
	if (!tab)
		return (0);
	while (str[i] && i < n)
	{
		tab[i] = str[index + i];
		i++;
	}
	tab[i] = '\0';
	return (tab);
}

char	**ft_split(const char *str, char c)
{
	int		i;
	int		j;
	char	**splitter;

	if (!str)
		return (NULL);
	splitter = ft_calloc(sizeof(char *), (count_words(str, c) + 1));
	if (!splitter)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != c)
		{
			splitter[j++] = ft_strndup(str, i, count_char(str, c, i));
			if (!splitter[j - 1])
				return (free_all(splitter), NULL);
			while (str[i] && str[i] != c)
				i++;
		}
		if (str[i] != '\0')
			i++;
	}
	return (splitter);
}

/*
int	main(int ac, char **argv)
{
	if(ac == 3)
	{
		char **strs;
		int i;
		
		i = 0;
		strs = ft_split(argv[1], argv[2]);
		while (strs[i])
		{
			printf("%s\n", strs[i]);
			i++;
		}
	}
	return(0);
}
*/
