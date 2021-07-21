#include "minishell.h"

void	copy_word_qs(char *str, int *i, char **split_string, int *count)
{
	(*split_string)[(*count)++] = str[(*i)++];
	while (str[*i] != '\'' && str[*i])
		(*split_string)[(*count)++] = str[(*i)++];
	(*split_string)[(*count)++] = str[(*i)++];
}

void 	copy_word(char *str, int *i, char **split_string, char s)
{
	int	count;

	count = 0;
	(*split_string)[count++] = str[(*i)++];
	while (str[*i] != s && str[*i])
		(*split_string)[count++] = str[(*i)++];
	(*split_string)[count++] = str[(*i)++];
	while (str[*i] != ' ' && str[*i])
	{
		if (str[*i] == '\"' && closed_quotes(str, *i, '\"'))
		{
			(*split_string)[count++] = str[(*i)++];
			while (str[*i] != '\"' && str[*i])
				(*split_string)[count++] = str[(*i)++];
			(*split_string)[count++] = str[(*i)++];
		}
		if (str[*i] == '\'' && closed_quotes(str, *i, '\''))
			copy_word_qs(str, i, split_string, &count);
		if (str[*i] != ' ' && str[*i])
			(*split_string)[count++] = str[(*i)++];
	}
	(*split_string)[count] = '\0';
}

void	copy_space_word(char *str, int *i, char **split_string)
{
	int	char_count;

	char_count = 0;
	while (str[*i] != ' ' && str[*i])
	{
		if (str[*i] == '\'' && closed_quotes(str, *i, '\''))
		{
			(*split_string)[char_count++] = str[(*i)++];
			while (str[*i] != '\'' && str[*i])
				(*split_string)[char_count++] = str[(*i)++];
		}
		if (str[*i] == '\"' && closed_quotes(str, *i, '\"'))
		{
			(*split_string)[char_count++] = str[(*i)++];
			while (str[*i] != '\"' && str[*i])
				(*split_string)[char_count++] = str[(*i)++];
		}
		if (str[*i] != ' ' && str[*i])
			(*split_string)[char_count++] = str[(*i)++];
	}
	(*split_string)[char_count] = '\0';
}

int	char_count(char *str, int *i, char s)
{
	int	count;

	count = 0;
	(*i)++;
	count++;
	while (str[*i] != s && str[*i])
	{
		(*i)++;
		count++;
	}
	(*i)++;
	count++;
	while (str[*i] != ' ' && str[*i])
	{
		if (str[*i] == '\"' && closed_quotes(str, *i, '\"'))
			count += char_count(str, i, '\"');
		if (str[*i] == '\'' && closed_quotes(str, *i, '\''))
			count += char_count(str, i, '\'');
		if (str[*i] != ' ' && str[*i])
		{
			(*i)++;
			count++;
		}
	}
	return (count);
}

int	not_qs_char_count(char *str, int *i)
{
	int	count;

	count = 0;
	while (str[*i] != ' ' && str[*i])
	{
		if (str[*i] == '\'' && closed_quotes(str, *i, '\''))
			count += char_count(str, i, '\'');
		if (str[*i] == '\"' && closed_quotes(str, *i, '\"'))
			count += char_count(str, i, '\"');
		if (str[*i] != ' ' && str[*i])
		{
			(*i)++;
			count++;
		}
	}
	return (count);
}
