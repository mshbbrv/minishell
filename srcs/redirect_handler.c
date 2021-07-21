#include "minishell.h"

int	input_redirect(char *str, int i, t_data *data)
{
	char	*filename;
	char	*error;

	while (str[i] == ' ')
		i++;
	filename = make_filename(str, i, data);
	close(data->fd_in[0]);
	data->fd_in[0] = open(filename, O_RDONLY, 0644);
	if (data->fd_in[0] == -1)
	{
		error = ft_strjoin(filename, ": ");
		free(filename);
		error_handler(ft_strjoin(error, strerror(errno)), 1);
		free(error);
		close(data->fd_in[0]);
		data->fd_in[0] = STDIN_FILENO;
		return (1);
	}
	free(filename);
	return (0);
}

int	output_redirect(char **str, int *i, t_data *data, int *fd_out_opened)
{
	int	error;

	error = 0;
	if ((*str)[*i] == '>')
	{
		if (*fd_out_opened)
			close(data->fd_out[0]);
		*fd_out_opened = 1;
		if ((*str)[*i + 1] == '>')
			error = app_redirect(*str, *i + 2, data);
		else
			error = redirect(*str, *i + 1, data);
		remove_redirect(str, i, '>');
	}
	return (error);
}

int	heredoc_redirect(char *str, int i, t_data *data)
{
	char	*word;
	int		exit_status;

	while (str[i] == ' ')
		i++;
	word = make_filename(str, i, data);
	exit_status = heredoc_read(data, word);
	if (word)
		free(word);
	return (exit_status);
}

int	input_heredoc_redirect(char **str, int *i, t_data *data, int *fd_in_opened)
{
	int	error;

	error = 0;
	if ((*str)[*i] == '<')
	{
		if (*fd_in_opened)
			close(data->fd_in[0]);
		*fd_in_opened = 1;
		if ((*str)[*i + 1] == '<')
			error = heredoc_redirect(*str, *i + 2, data);
		else
			error = input_redirect(*str, *i + 1, data);
		remove_redirect(str, i, '<');
	}
	return (error);
}

int	redirect_handler(char **str, t_data *data)
{
	int	fd_out_opened;
	int	fd_in_opened;
	int	i;
	int	error;

	fd_out_opened = 0;
	fd_in_opened = 0;
	i = 0;
	while ((*str)[i])
	{
		skip_other(*str, &i);
		error = output_redirect(str, &i, data, &fd_out_opened);
		if (error)
			return (1);
		error = input_heredoc_redirect(str, &i, data, &fd_in_opened);
		if (error)
			return (1);
		if ((*str)[i] != '>' && (*str)[i])
			i++;
	}
	return (0);
}
