#include "minishell.h"

int	pipe_syntax_check(char *str, int *i)
{
	int	tmp;

	if (str[*i] == '|')
	{
		tmp = *i + 1;
		if (*i > 0)
			(*i)--;
		while (str[*i] == ' ' && *i > 0)
			(*i)--;
		if (str[*i] == ' ' || str[*i] == '|')
			return (1);
		*i = tmp;
		while (str[*i] == ' ')
			(*i)++;
		if (str[*i] == '|' || str[*i] == '\0')
			return (1);
	}
	return (0);
}

int	redirect_syntax_check(char *str, int *i)
{
	if (str[*i] == '>' && str[*i + 1] != '>')
	{
		(*i)++;
		while (str[*i] == ' ')
			(*i)++;
		if (str[*i] == '>')
			return (2);
		if (str[*i] == '\0')
			return (3);
	}
	if (str[*i] == '>' && str[*i + 1] == '>')
	{
		(*i) += 2;
		while (str[*i] == ' ')
			(*i)++;
		if (str[*i] == '>')
			return (4);
		if (str[*i] == '\0')
			return (3);
	}
	return (0);
}

int	input_redirect_syntax_check(char *str, int *i)
{
	if (str[*i] == '<' && str[*i + 1] != '<')
	{
		(*i)++;
		while (str[*i] == ' ')
			(*i)++;
		if (str[*i] == '<')
			return (5);
		if (str[*i] == '\0')
			return (3);
	}
	if (str[*i] == '<' && str[*i + 1] == '<')
	{
		(*i) += 2;
		while (str[*i] == ' ')
			(*i)++;
		if (str[*i] == '<')
			return (6);
		if (str[*i] == '\0')
			return (3);
	}
	return (0);
}

void	skip_quotes(char *str, int *i)
{
	if (str[*i] == '\'' && closed_quotes(str, *i, '\''))
	{
		(*i)++;
		while (str[*i] != '\'' && str[*i])
			(*i)++;
	}
	if (str[*i] == '\"' && closed_quotes(str, *i, '\"'))
	{
		(*i)++;
		while (str[*i] != '\"' && str[*i])
			(*i)++;
	}
}

int	check_syntax(char *str)
{
	int	i;
	int	syntax_error;

	i = 0;
	while (str[i])
	{
		skip_quotes(str, &i);
		syntax_error = pipe_syntax_check(str, &i);
		if (syntax_error)
			return (syntax_error);
		syntax_error = redirect_syntax_check(str, &i);
		if (syntax_error)
			return (syntax_error);
		syntax_error = input_redirect_syntax_check(str, &i);
		if (syntax_error)
			return (syntax_error);
		if (str[i])
			i++;
	}
	return (0);
}
