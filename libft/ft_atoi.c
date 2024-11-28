/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 14:54:40 by aubertra          #+#    #+#             */
/*   Updated: 2024/03/07 10:46:48 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	moins;
	int	nb;

	i = 0;
	moins = 0;
	nb = 0;
	while (nptr[i] && (nptr[i] == ' ' || (nptr[i] >= '\t' && nptr[i] <= '\r')))
		i++;
	if (nptr[i] && (nptr[i + 1] == '+' || nptr[i + 1] == '-'))
		return (nb);
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			moins++;
		i++;
	}
	while (nptr[i] && nptr[i] >= '0' && nptr[i] <= '9')
	{
		nb = nb * 10 + (nptr[i] - 48);
		i++;
	}
	if (moins % 2)
		nb = -nb;
	return (nb);
}
/*
#include <stdio.h>

int	main(void)
{
	char	*nb1;

	nb1 = " ";
  	printf("%d\n", ft_atoi(nb1));
	return (0);
}
*/
