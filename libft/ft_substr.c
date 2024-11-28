/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 15:04:48 by aubertra          #+#    #+#             */
/*   Updated: 2024/02/04 15:55:53 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	j;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s) || len == 0)
		return (ft_calloc(1, sizeof(char)));
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	j = 0;
	sub = ft_calloc(len + 1, sizeof(char));
	if (!sub)
		return (NULL);
	while (j < len)
	{
		sub[j] = s[j + start];
		j++;
	}
	sub[j] = '\0';
	return (sub);
}

/*
int	main(void)
{
 	printf("%s\n", ft_substr("0123456789", 9, 10));
	printf("%s\n", ft_substr("tripouille", 0, 42000));
 	return (0);
}
*/
