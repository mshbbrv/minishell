#include "minishell.h"

void	quotes_handle(char *str, int *i, char c)
{
	int	k;

	k = *i;
	(*i)++;
	while (str[*i] != c && str[*i])
		(*i)++;
	if (str[*i] != c)
		*i = k;
}

int	command_line_count(char *str)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\"' && closed_quotes(str, i, '\"'))
			quotes_handle(str, &i, '\"');
		if (str[i] == '\'' && closed_quotes(str, i, '\''))
			quotes_handle(str, &i, '\'');
		if (str[i] == '|')
			count++;
		if (str[i])
			i++;
	}
	return (count);
}

void	line_char_count(char *str, int *i)
{
	int	tmp_i;

	while (str[*i] != '|' && str[*i])
	{
		if (str[*i] == '\"' && closed_quotes(str, *i, '\"'))
		{
			tmp_i = *i;
			(*i)++;
			while (str[*i] != '\"' && str[*i])
				(*i)++;
			if (str[*i] != '\"')
				*i = tmp_i;
		}
		if (str[*i] == '\'' && closed_quotes(str, *i, '\''))
		{
			tmp_i = *i;
			(*i)++;
			while (str[*i] != '\'' && str[*i])
				(*i)++;
			if (str[*i] != '\'')
				*i = tmp_i;
		}
		if (str[*i])
			(*i)++;
	}
}
