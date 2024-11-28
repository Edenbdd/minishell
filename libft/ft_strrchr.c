/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 15:06:55 by aubertra          #+#    #+#             */
/*   Updated: 2024/02/04 15:12:56 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	len;

	len = ft_strlen((char *)s);
	while (len >= 0)
	{
		if (s[len] == (char)c)
			return ((char *)s + len);
		len--;
	}
	return (NULL);
}

// int	main(void)
// {
// 	char	*s1 = "je m'appelle Enzo";
// 	printf("%p\n", ft_strrchr(s1, 'j'));
// //	printf("%p\n", strrchr(s1, 128));
// 	return (0);
// }