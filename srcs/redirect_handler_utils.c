#include "minishell.h"

char	*make_filename(char *str, int i, t_data *data)
{
	int		tmp;
	char	*tmp_str;

	if (str[i] == '\"' && closed_quotes(str, i, '\"'))
	{
		tmp = i++;
		while (str[i] != '\"')
			i++;
	}
	else if (str[i] == '\'' && closed_quotes(str, i, '\''))
	{
		tmp = i++;
		while (str[i] != '\'')
			i++;
	}
	else
	{
		tmp = i;
		while (str[i] != ' ' && str[i] != '>' && str[i] != '<' && str[i])
			i++;
		i--;
	}
	tmp_str = ft_substr(str, tmp, i - tmp + 1);
	spec_sym_handler(&tmp_str, data);
	return (tmp_str);
}

void	skip_other(char *str, int *i)
{
	while (str[*i] != '>' && str[*i] != '<' && str[*i])
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
		if (str[*i])
			(*i)++;
	}
}

void	remove_redirect(char **str, int *i, char c)
{
	char	*new_str;
	char	*first_part;
	int		start;

	start = *i;
	while ((*str)[*i] == c)
		(*i)++;
	while ((*str)[*i] == ' ')
		(*i)++;
	skip_filename(*str, i);
	first_part = ft_substr(*str, 0, start);
	new_str = ft_strjoin(first_part, *str + *i + 1);
	free(first_part);
	*str = ft_strdup(new_str);
	free(new_str);
	*i = start;
}

int	redirect(char *str, int i, t_data *data)
{
	char	*filename;
	char	*error;

	while (str[i] == ' ')
		i++;
	filename = make_filename(str, i, data);
	close(data->fd_out[0]);
	data->fd_out[0] = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (data->fd_out[0] == -1)
	{
		error = ft_strjoin(filename, ": ");
		free(filename);
		error_handler(ft_strjoin(error, strerror(errno)), 1);
		free(error);
		close(data->fd_out[0]);
		data->fd_out[0] = STDOUT_FILENO;
		return (1);
	}
	free(filename);
	return (0);
}

int 	app_redirect(char *str, int i, t_data *data)
{
	char	*filename;
	char	*error;

	while (str[i] == ' ')
		i++;
	filename = make_filename(str, i, data);
	close(data->fd_out[0]);
	data->fd_out[0] = open(filename, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (data->fd_out[0] == -1)
	{
		error = ft_strjoin(filename, ": ");
		free(filename);
		error_handler(ft_strjoin(error, strerror(errno)), 1);
		free(error);
		close(data->fd_out[0]);
		data->fd_out[0] = STDOUT_FILENO;
		return (1);
	}
	free(filename);
	return (0);
}
