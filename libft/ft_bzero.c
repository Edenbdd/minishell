/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 14:12:11 by aubertra          #+#    #+#             */
/*   Updated: 2024/01/17 15:18:45 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*s2;

	s2 = s;
	while (n-- > 0)
	{
		*s2 = '\0';
		s2++;
	}
}

/*
int	main(void)
{
	char	s1[] = "blabla";
	char	s2[] = "blabla";
	int	i = 420;
	int	j = 420;
	int	*ptr = &i;
	int	*ptr1 = &j;	
	ft_bzero(s1, 3*sizeof(char));
	bzero(s2, 3*sizeof(char));
	printf("%s\n", s1);
	printf("%s\n", s2);
	ft_bzero(ptr, 1*sizeof(int));
	bzero(ptr1, 1*sizeof(int));
	printf("%d\n", i);
	printf("%d\n", j);	
	return (0);
}
*/
