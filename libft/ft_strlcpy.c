/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 15:07:51 by aubertra          #+#    #+#             */
/*   Updated: 2024/02/03 19:18:22 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	int		len;

	len = ft_strlen(src);
	i = 0;
	if (dstsize == 0)
		return (len);
	while (src[i] && i < (dstsize - 1))
	{
		dst[i] = src [i];
		i++;
	}
	dst[i] = '\0';
	return (len);
}

/*
int	main(void)
{
	char	dst[] = "*****";
	char	dst1[] = "*****";
	char	*src = "abcde";
	printf("%ld\n", ft_strlcpy(dst, src, 6));
	printf("%ld\n", strlcpy(dst1, src, 6));
	printf("%s\n", dst);
	printf("%s\n", dst1);
	return (0);
}
*/
