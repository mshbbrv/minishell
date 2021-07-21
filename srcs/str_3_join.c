#include "minishell.h"

char	*str_3_join(char const *s1, char const *s2, char const *s3)
{
	char	*str;
	int		i;
	int		j;

	if (!s1 || !s2 || !s3)
		return (NULL);
	str = malloc(ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3) + 1);
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[j])
		str[i++] = s1[j++];
	j = 0;
	while (s2[j])
		str[i++] = s2[j++];
	j = 0;
	while (s3[j])
		str[i++] = s3[j++];
	str[i] = '\0';
	return (str);
}
