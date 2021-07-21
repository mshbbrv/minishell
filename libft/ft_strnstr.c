/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjonell <thjonell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 20:25:11 by thjonell          #+#    #+#             */
/*   Updated: 2021/04/28 15:43:22 by thjonell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	tmp;

	tmp = 0;
	if (needle[tmp] == '\0')
		return ((char *)haystack);
	i = 0;
	while (haystack[i])
	{
		while (haystack[i + tmp] == needle[tmp] && (tmp + i) < len)
		{
			if (haystack[i + tmp] == '\0' && needle[tmp] == '\0')
				return ((char *)&haystack[i]);
			tmp++;
		}
		if (needle[tmp] == '\0')
			return ((char *)&haystack[i]);
		tmp = 0;
		i++;
	}
	return (NULL);
}
