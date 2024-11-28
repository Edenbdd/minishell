/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 15:09:01 by aubertra          #+#    #+#             */
/*   Updated: 2024/11/07 15:23:13 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*s2;

	s2 = s;
	if (s == NULL)
		return (NULL);
	while (n-- > 0)
	{
		*s2 = (unsigned char)c;
		s2++;
	}
	return (s);
}

// #include <stdio.h>

// int	main() {
// 	char s[43];
// 	s[43] = 0;
// 	ft_memset(s, 'A', 42);
// 	// memset(s, 'A', 42);
// 	printf("%s\n", s);
// }

/*
#include <stdio.h>
#include <string.h>
int	main(void)
{
	char	s1[] = "je m'appelle Enzo";
	char	s2[] = "je m'appelle Enzo";

	ft_memset(s1 + 4, '_', 2*sizeof(char));
	printf("%s\n", s1);
	memset(s2 + 4, '_', 2*sizeof(char));
	printf("%s\n", s2);
	return (0);
}
*/
