/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 15:02:40 by aubertra          #+#    #+#             */
/*   Updated: 2024/11/07 15:23:09 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*dest_bis;
	unsigned char	*src_bis;
	size_t			i;

	i = 0;
	if (dest == NULL && src == NULL)
		return (NULL);
	dest_bis = (unsigned char *)dest;
	src_bis = (unsigned char *)src;
	if (src > dest)
	{
		while (i < n)
		{
			dest_bis[i] = src_bis[i];
			i++;
		}
	}
	else
	{
		while (n-- > 0)
			dest_bis[n] = src_bis[n];
	}
	return (dest);
}

// int	main(void)
// {
// 	char	src[100] = "je suis Enzo";
// 	char	src1[100] = "je suis Enzo";
// 	// char	dest[] = "*****";
// 	// char	dest1[] = "*****";
// 	int	n = 5;

// 	printf("%s\n", (char *)ft_memmove(src + 5, src, n));
// 	printf("%s\n", (char *)memmove(src1 + 5, src1, n));
// 	return (0);
// }