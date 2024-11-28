/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 15:08:21 by aubertra          #+#    #+#             */
/*   Updated: 2024/02/03 17:55:57 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	len;
	int	i;

	i = 0;
	len = ft_strlen((char *)s) + 1;
	while (i < len)
	{
		if (s[i] == (char)c)
			return ((char *)s + i);
		i++;
	}
	return (NULL);
}

/*
int	main(void)
{
	char	*s1 = "je m'appelle Enzo";

	printf("%s\n", ft_strchr(s1, 128));
	printf("%s\n", strchr(s1, 128));
	return (0);
}
*/
