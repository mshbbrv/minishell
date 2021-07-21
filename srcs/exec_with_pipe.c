#include "minishell.h"

void	open_pipes(t_data *data, int tokens_count)
{
	int	i;

	i = 0;
	while (i <= tokens_count)
	{
		if (pipe(data->fd[i]) == -1)
		{
			error_handler("error with creating pipe", 1);
			exit(1);
		}
		i++;
	}
}

void	close_unused_fd_child(t_data *data, int i, int tokens_count)
{
	int	k;

	k = 0;
	while (k <= tokens_count)
	{
		if (i != k)
			close(data->fd[k][0]);
		if (i + 1 != k)
			close(data->fd[k][1]);
		k++;
	}
}

void	create_child(t_data *data, int tokens_count, pid_t *pid, char **tmp)
{
	int	i;

	i = 0;
	while (i < tokens_count)
	{
		pid[i] = fork();
		if (pid[i] < 0)
			fork_error();
		if (pid[i] == 0)
		{
			close_unused_fd_child(data, i, tokens_count);
			data->fd_out[0] = data->fd[i + 1][1];
			if (i == 0)
				data->fd_in[0] = STDIN_FILENO;
			else
				data->fd_in[0] = data->fd[i][0];
			split_and_exec(data, tmp[i]);
			close(data->fd_in[0]);
			close(data->fd_out[0]);
			exit(g_exit_status);
		}
		i++;
	}
}

void 	close_unsed_fd_parent(t_data *data, int tokens_count)
{
	int	k;

	k = 0;
	while (k <= tokens_count)
	{
		if (k != tokens_count)
			close(data->fd[k][0]);
		if (k != 0)
			close(data->fd[k][1]);
		k++;
	}
}

void	exec_cmd_line_with_pipes(t_data *data, char **tmp, int tokens_count)
{
	pid_t	*pid;
	char	c;
	char	*line_read;

	line_read = NULL;
	malloc_things(data, &pid, tokens_count);
	open_pipes(data, tokens_count);
	create_child(data, tokens_count, pid, tmp);
	close_unsed_fd_parent(data, tokens_count);
	waitpids(pid, tokens_count);
	while (read(data->fd[tokens_count][0], &c, 1) != 0)
		make_string(&line_read, c);
	close(data->fd[tokens_count][0]);
	close(data->fd[0][1]);
	if (line_read && *line_read && *line_read != '\n')
	{
		ft_putstr_fd(line_read, STDOUT_FILENO);
		free(line_read);
	}
	free_things(data, pid, tokens_count);
}
