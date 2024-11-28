/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 15:02:59 by aubertra          #+#    #+#             */
/*   Updated: 2024/03/07 11:24:00 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <sys/mman.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*s1_bis;
	unsigned char	*s2_bis;

	s1_bis = (unsigned char *)s1;
	s2_bis = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{	
		if (s1_bis[i] != s2_bis[i])
			return (s1_bis[i] - s2_bis[i]);
		i++;
	}
	return (0);
}
/*
int	main(void)
{
	int size = 10;
	char	*str = ft_strdup("........");
	char	*str1 = ft_strdup("........");
	mprotect(str - 4096 + size, 4096, PROT_READ);
	mprotect(str1 - 4096 + size, 4096, PROT_READ);
 	printf("%d\n", ft_memcmp(str, str1, 10));
 	printf("%d\n", memcmp(str, str1, 10));
	return (0);
}
*/
