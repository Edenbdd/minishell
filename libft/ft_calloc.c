/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 14:56:06 by aubertra          #+#    #+#             */
/*   Updated: 2024/02/04 15:06:57 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t			i;
	unsigned char	*ptr;

	i = 0;
	if (size == 0 || nmemb == 0)
		return (malloc(0));
	if ((size * nmemb) < size || (size * nmemb) < nmemb)
		return (NULL);
	ptr = malloc(size * nmemb);
	if (!ptr)
		return (NULL);
	while (i < nmemb * size)
	{
		ptr[i] = 0;
		i++;
	}
	return (ptr);
}

/*
int	main(void)
{
	printf("%s\n", (char *)ft_calloc(5, 4));
	printf("%s\n", (char *)calloc(5, 4));
	return (0);
}
*/
