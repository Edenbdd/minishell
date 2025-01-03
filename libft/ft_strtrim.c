/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 15:06:46 by aubertra          #+#    #+#             */
/*   Updated: 2025/01/03 13:28:39 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_set(char c, char const *set)
{
	int	count;

	count = 0;
	while (set[count])
	{
		if (c == set[count])
			return (1);
		count++;
	}
	return (0);
}

static char	*ft_strnduptrim(const char *str, int index, int n)
{
	int		i;
	char	*tab;

	tab = malloc(sizeof(char) * (n - index + 1));
	i = 0;
	if (!tab)
		return (0);
	while (str[i] && i < (n - index))
	{
		tab[i] = str[index + i];
		i++;
	}
	tab[i] = '\0';
	return (tab);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		len;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	len = ft_strlen(s1);
	while (s1[i] && is_set(s1[i], set))
		i++;
	while (len > 0 && is_set(s1[len - 1], set))
		len--;
	if ((len - i) <= 0)
		return (ft_strdup(""));
	return (ft_strnduptrim(s1, i, len));
}

// int	main(void)
// {
//  	printf("%s\n", ft_strtrim("   xxxtripouille", " x"));
//  	return (0);
// }
