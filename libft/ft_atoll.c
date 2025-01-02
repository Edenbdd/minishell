/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 09:47:34 by aubertra          #+#    #+#             */
/*   Updated: 2024/11/07 10:22:37 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long	ft_atoll(char *str)
{
	int			pos;
	int			sign;
	long long	result;

	pos = 0;
	sign = 1;
	result = 0;
	while (str[pos] && ft_is_space(str[pos]))
		pos++;
	if (str[pos] == '+')
		pos++;
	else if (str[pos] == '-')
	{
		sign = -1;
		pos++;
	}
	while (str[pos] && ft_is_space(str[pos]))
		pos++;
	while (str[pos] && !ft_is_space(str[pos]))
	{
		result *= 10;
		result += str[pos] - 48;
		pos++;
	}
	return (result * sign);
}
