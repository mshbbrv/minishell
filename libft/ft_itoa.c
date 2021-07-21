/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjonell <thjonell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 17:11:10 by thjonell          #+#    #+#             */
/*   Updated: 2021/04/28 15:43:22 by thjonell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_negative(char *str, int nbr, int i, int n)
{
	while (nbr)
	{
		nbr /= 10;
		if (nbr)
			i++;
	}
	str = (char *)malloc(sizeof(char) * (i + 3));
	if (!str)
		return (NULL);
	i += 2;
	str[i] = '\0';
	while (i > 0)
	{
		str[--i] = 48 - (n % 10);
		n /= 10;
	}
	str[i] = '-';
	return (str);
}

char	*ft_positive(int nbr, int n)
{
	int		i;
	char	*str;

	i = 0;
	while (nbr)
	{
		nbr /= 10;
		if (nbr)
			i++;
	}
	str = (char *)malloc(sizeof(char) * (i + 2));
	if (!str)
		return (NULL);
	str[++i] = '\0';
	while (i)
	{
		str[--i] = (n % 10) + 48;
		n /= 10;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		i;
	int		nbr;

	nbr = n;
	i = 0;
	str = NULL;
	if (n < 0)
		str = ft_negative(str, nbr, i, n);
	else
		str = ft_positive(nbr, n);
	return (str);
}
