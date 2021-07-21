/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjonell <thjonell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 14:44:13 by thjonell          #+#    #+#             */
/*   Updated: 2021/04/28 15:43:22 by thjonell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	**ft_free(char **strs, int i)
{
	while (i >= 0)
		free(strs[i--]);
	free(strs);
	return (NULL);
}

static void	*ft_strmalloc(char **strs, char const *s, char c)
{
	int	i;
	int	k;
	int	j;

	i = 0;
	k = 0;
	while (s[k])
	{
		if (s[k] != c)
		{
			j = 0;
			while (s[k] != c && s[k] != '\0')
			{
				k++;
				j++;
			}
			strs[i] = (char *)malloc(sizeof(char) * (j + 1));
			if (!strs[i])
				return (ft_free(strs, i));
			i++;
		}
		if (s[k] != '\0')
			k++;
	}
	return (strs);
}

static void	*ft_strsmalloc(char **strs, char const *s, char c)
{
	int	k;
	int	i;

	i = 0;
	k = 0;
	while (s[k])
	{
		if (s[k] != c)
			i++;
		while (s[k] != c && s[k])
			k++;
		if (s[k])
			k++;
	}
	strs = (char **)malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	return (ft_strmalloc(strs, s, c));
}

char	**ft_split(char const *s, char c)
{
	char	**strs;
	int		i;
	int		j;
	int		k;

	strs = NULL;
	strs = ft_strsmalloc(strs, s, c);
	if (!s || !strs)
		return (NULL);
	i = 0;
	k = 0;
	while (s[k])
	{
		if (s[k] != c)
		{
			j = 0;
			while (s[k] != c && s[k] != '\0')
				strs[i][j++] = s[k++];
			strs[i++][j] = '\0';
		}
		if (s[k])
			k++;
	}
	strs[i] = NULL;
	return (strs);
}
