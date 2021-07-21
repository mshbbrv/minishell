/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjonell <thjonell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 15:31:23 by thjonell          #+#    #+#             */
/*   Updated: 2021/04/28 15:43:22 by thjonell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	int	i;
	int	diff;

	i = 0;
	diff = 0;
	while (diff == 0 && i < (int)n)
	{
		diff = ((unsigned char *)s1)[i] - ((unsigned char *)s2)[i];
		i++;
	}
	return (diff);
}
