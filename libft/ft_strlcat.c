/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 15:07:15 by aubertra          #+#    #+#             */
/*   Updated: 2024/03/07 11:38:08 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	len_dst;
	size_t	len_src;

	len_src = ft_strlen(src);
	if (!dst)
		return (len_src);
	len_dst = ft_strlen(dst);
	if (len_dst >= dstsize)
		len_dst = dstsize;
	if (len_dst == dstsize)
		return (len_dst + len_src);
	if (len_src < (dstsize - len_dst))
		ft_memcpy(dst + len_dst, src, len_src + 1);
	else
	{
		ft_memcpy(dst + len_dst, src, dstsize - len_dst - 1);
		dst[dstsize - 1] = '\0';
	}
	return (len_src + len_dst);
}
