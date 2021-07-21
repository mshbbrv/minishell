/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjonell <thjonell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 17:51:05 by thjonell          #+#    #+#             */
/*   Updated: 2021/04/28 15:43:22 by thjonell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *restrict dst, const char *restrict src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	tmp;

	j = ft_strlen(dst);
	tmp = j;
	if (dstsize > j)
	{
		i = 0;
		while (j < (dstsize - 1) && ((unsigned char *)src)[i])
			((unsigned char *)dst)[j++] = ((unsigned char *)src)[i++];
		((unsigned char *)dst)[j] = '\0';
		return (ft_strlen(src) + tmp);
	}
	else
		return (ft_strlen(src) + dstsize);
}
