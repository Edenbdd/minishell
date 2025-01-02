/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 15:01:50 by aubertra          #+#    #+#             */
/*   Updated: 2024/02/03 20:10:37 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_nblen(int n)
{
	int	nblen;

	nblen = 0;
	if (n < 0)
	{
		nblen++;
		n = -n;
	}
	if (n == 0)
		nblen++;
	while (n > 0)
	{
		n /= 10;
		nblen++;
	}
	return (nblen);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	len = ft_nblen(n);
	str = malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	if (n < 0)
	{
		str[0] = '-';
		n = -n;
	}
	str[len] = '\0';
	len--;
	if (n == 0)
		str[len] = '0';
	while (n > 0)
	{
		str[len] = n % 10 + 48;
		n /= 10;
		len --;
	}
	return (str);
}

// int	main(void)
// {
// 	printf("%s\n", ft_itoa(42));
// 	printf("%s\n", ft_itoa(0));
// 	printf("%s\n", ft_itoa(420));
// 	printf("%s\n", ft_itoa(-42));
// 	return (0);
// }
