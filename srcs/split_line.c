#include "minishell.h"

void	malloc_word(char *str, int *i, char **split_string, char s)
{
	*split_string = (char *)malloc(sizeof(char)
			   * (char_count(str, i, s) + 1));
	if (str[*i] == s)
		(*i)++;
}

void	*split_words_malloc(char **split_string, char *str)
{
	int	i;
	int	words_count;

	words_count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' && closed_quotes(str, i, '\''))
			malloc_word(str, &i, &split_string[words_count++], '\'');
		if (str[i] == '\"' && closed_quotes(str, i, '\"'))
			malloc_word(str, &i, &split_string[words_count++], '\"');
		if (str[i] != ' ' && str[i])
			split_string[words_count++] = (char *)malloc(sizeof(char)
					* (not_qs_char_count(str, &i) + 1));
		if (str[i])
			i++;
	}
	return (split_string);
}

int	count_words(char *str, int i, int count)
{
	while (str[i])
	{
		if (str[i] == '\'' && closed_quotes(str, i, '\''))
		{
			char_count(str, &i, '\'');
			count++;
			if (str[i] == '\'')
				i++;
		}
		if (str[i] == '\"' && closed_quotes(str, i, '\"'))
		{
			char_count(str, &i, '\"');
			count++;
			if (str[i] == '\"')
				i++;
		}
		if (str[i] != ' ' && str[i])
		{
			not_qs_char_count(str, &i);
			count++;
		}
		if (str[i])
			i++;
	}
	return (count);
}

void	*split_string_malloc(char **split_string, char *str)
{
	split_string = (char **)malloc(sizeof(char *)
			* (count_words(str, 0, 0) + 1));
	if (!split_string)
		return (NULL);
	return (split_words_malloc(split_string, str));
}

char	**split_line(char *str)
{
	char	**split_string;
	int		i;
	int		words_count;

	split_string = NULL;
	split_string = split_string_malloc(split_string, str);
	words_count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' && closed_quotes(str, i, '\''))
			copy_word(str, &i, &split_string[words_count++], '\'');
		if (str[i] == '\"' && closed_quotes(str, i, '\"'))
			copy_word(str, &i, &split_string[words_count++], '\"');
		if (str[i] != ' ' && str[i])
			copy_space_word(str, &i, &split_string[words_count++]);
		if (str[i])
			i++;
	}
	split_string[words_count] = NULL;
	return (split_string);
}
