#include "minishell.h"

void	fork_process(char *path_to_bin, char **cmd_line, t_data *data)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		error_handler(strerror(errno), 1);
	if (equal_str(path_to_bin, "./minishell"))
		signal(SIGINT, ctrl_c_child_m);
	if (pid == 0)
		execve(path_to_bin, cmd_line, data->envp_exp);
	else
	{
		waitpid(pid, &status, 0);
		g_exit_status = WEXITSTATUS(status);
		if (WIFSIGNALED(status))
			g_exit_status = 128 + WTERMSIG(status);
		else if (WIFEXITED(status))
			g_exit_status = WEXITSTATUS(status);
	}
}

int	is_executable(char *path_to_bin)
{
	int			fd;
	struct stat	sb;
	int			res;

	res = -1;
	fd = open(path_to_bin, O_RDONLY);
	if (fd != -1 && stat(path_to_bin, &sb) == 0 && sb.st_mode & S_IXUSR)
		res = 0;
	if (fd > 0)
		close(fd);
	return (res);
}

int	check_and_exec_paths(char *path_value, char **cmd_line, t_data *data)
{
	char	*path_to_bin;
	char	**paths;
	int		i;
	int		flag;

	i = 0;
	flag = 0;
	paths = ft_split(path_value, ':');
	free(path_value);
	while (paths[i])
	{
		path_to_bin = str_3_join(paths[i], "/", cmd_line[0]);
		if (is_executable(path_to_bin) == 0)
		{
			fork_process(path_to_bin, cmd_line, data);
			flag = 1;
			free(path_to_bin);
			break ;
		}
		free(path_to_bin);
		i++;
	}
	free_splited_arr(paths);
	return (flag);
}

void	execute_bin(char **cmd_line, t_data *data)
{
	int		flag;
	char	*path_value;
	char	*tmp;

	flag = 0;
	path_value = get_minishell_env("PATH", data->envp);
	if (path_value)
		flag = check_and_exec_paths(path_value, cmd_line, data);
	if (!flag && is_executable(cmd_line[0]) == 0)
		fork_process(cmd_line[0], cmd_line, data);
	else if (!path_value)
	{
		tmp = ft_strjoin(cmd_line[0], ": No such file or directory");
		error_handler(tmp, 127);
		free(tmp);
	}
	else if (!flag)
		cmd_not_found(cmd_line[0], data);
}
