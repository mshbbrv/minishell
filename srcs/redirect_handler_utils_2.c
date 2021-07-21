#include "minishell.h"

int	get_out_from_child(char *tmp, char *heredoc, int *fd, t_data *data)
{
	if (tmp && *tmp)
		free(tmp);
	data->config.c_lflag |= ECHOCTL;
	tcsetattr(STDOUT_FILENO, TCSANOW, &data->config);
	write(fd[1], heredoc, ft_strlen(heredoc) + 1);
	free(heredoc);
	close(fd[1]);
	if (data->heredoc_ctrl_d == 0)
		ft_putstr_fd("\e[1A\e[2C", STDOUT_FILENO);
	exit(0);
}

void	read_heredoc_from_child(int *fd, char *word, t_data *data)
{
	int		do_read;
	char	*tmp;
	char	*heredoc;

	tmp = ft_strdup("");
	data->config.c_lflag &= ~ECHOCTL;
	tcsetattr(STDOUT_FILENO, TCSANOW, &data->config);
	heredoc = readline("> ");
	if (!heredoc)
		get_out_from_child(tmp, heredoc, fd, data);
	do_read = equal_str(word, heredoc);
	heredoc = string_join(heredoc, "\n");
	while (!do_read)
	{
		heredoc = string_join(heredoc, tmp);
		if (tmp)
			free(tmp);
		tmp = readline("> ");
		if (!tmp)
			get_out_from_child(tmp, heredoc, fd, data);
		do_read = equal_str(word, tmp);
		tmp = string_join(tmp, "\n");
	}
	data->heredoc_ctrl_d = 1;
	get_out_from_child(tmp, heredoc, fd, data);
}

int	heredoc_parent(t_data *data, int *fd)
{
	char	*heredoc;
	int		status;
	char	c;

	close(fd[1]);
	heredoc = NULL;
	while (read(fd[0], &c, 1))
		make_string(&heredoc, c);
	close(data->fd_in[0]);
	wait(&status);
	data->fd_in[0] = open("/tmp/heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	ft_putstr_fd(heredoc, data->fd_in[0]);
	free(heredoc);
	close(data->fd_in[0]);
	data->fd_in[0] = open("/tmp/heredoc", O_RDONLY, 0644);
	if (WIFSIGNALED(status))
	{
		g_exit_status = 1;
		return (1);
	}
	else if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	signal(SIGINT, ctrl_c);
	unlink("/tmp/heredoc");
	return (0);
}

int	heredoc_read(t_data *data, char *word)
{
	int		fd[2];
	pid_t	pid_child;

	if (pipe(fd) == -1)
	{
		error_handler("error with creating pipe", 1);
		return (1);
	}
	pid_child = fork();
	if (pid_child < 0)
	{
		error_handler("Error with creating process", 1);
		return (1);
	}
	if (pid_child == 0)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, SIG_DFL);
		close(fd[0]);
		read_heredoc_from_child(fd, word, data);
	}
	else
		return (heredoc_parent(data, fd));
	return (0);
}

void	skip_filename(char *str, int *i)
{
	if (str[*i] == '\"' && closed_quotes(str, *i, '\"'))
	{
		(*i)++;
		while (str[*i] != '\"')
			(*i)++;
	}
	else if (str[*i] == '\'' && closed_quotes(str, *i, '\''))
	{
		(*i)++;
		while (str[*i] != '\'')
			(*i)++;
	}
	else
	{
		while (str[*i] != ' ' && str[*i] != '>' && str[*i] != '<' && str[*i])
			(*i)++;
		(*i)--;
	}
}
