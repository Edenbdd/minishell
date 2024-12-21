/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_operators_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 14:53:07 by aubertra          #+#    #+#             */
/*   Updated: 2024/12/21 14:54:51 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int	is_symbols(char c)
{
	if (c == ':' || c == '!')
		return (1);
	return (0);
}

int	only_space_symbols(char *str)
{
	while (*str)
	{
		if (!ft_is_space(*str) && !is_symbols(*str))
			return (0);
		str++;	
	}
	return (1);
}

int	only_space(char *str)
{
	while (*str)
	{
		if (!ft_is_space(*str))
			return (0);
		str++;	
	}
	return (1);
}
