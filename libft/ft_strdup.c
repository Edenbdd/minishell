/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smolines <smolines@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 15:08:14 by aubertra          #+#    #+#             */
/*   Updated: 2024/11/29 11:29:11 by smolines         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = malloc(sizeof(char) * ft_strlen(s) + 1);
	if (!tmp)
		return (NULL);
	while (s && s[i])
	{
		tmp[i] = s[i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}

/*
int	main(int argc, char **argv)
{
	(void)argc;
	printf("%s\n", ft_strdup(argv[1]));
	printf("%s\n", strdup(argv[1]));
	return (0);
}
*/
