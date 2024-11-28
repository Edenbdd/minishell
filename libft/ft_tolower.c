/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 15:04:40 by aubertra          #+#    #+#             */
/*   Updated: 2024/01/18 10:01:47 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 65 && c <= 90)
		c += 32;
	return (c);
}

/*
int	main(void)
{
	int	i = 97;
	int	j = 97;

	printf("%d\n", ft_tolower(146));
	printf("%d\n", tolower(146));
	return (0);
}
*/
