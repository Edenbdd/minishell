/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 15:07:33 by aubertra          #+#    #+#             */
/*   Updated: 2024/03/07 13:12:34 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	size_t	len;
	char	*copy;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	copy = ft_calloc(sizeof(char), len + 1);
	if (!copy)
		return (NULL);
	i = 0;
	while (i < len)
	{
		copy[i] = f(i, s[i]);
		i++;
	}
	return (copy);
}
/*
char	plus1(unsigned int i, char c)
{
	(void)i;
	c = c + 1;
	return (c);
}

int	main(void)
{
	char	(*ptrf)(unsigned int, char);

	ptrf = &plus1;
	printf("%s\n", ft_strmapi("je m'appelle Enzo", ptrf));
	return (0);
}
*/
