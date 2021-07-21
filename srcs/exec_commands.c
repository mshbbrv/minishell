#include "minishell.h"

int 	equal_str(char *str1, char *str2)
{
	size_t	len1;
	size_t	len2;

	len1 = ft_strlen(str1);
	len2 = ft_strlen(str2);
	if (len1 == len2)
		if (!ft_strncmp(str1, str2, len1))
			return (1);
	return (0);
}

void	exec_cmd(char **cmd_line, t_data *data)
{
	if (equal_str(cmd_line[0], "echo"))
		echo(cmd_line);
	else if (equal_str(cmd_line[0], "cd"))
		cd(cmd_line, data, 0);
	else if (equal_str(cmd_line[0], "pwd"))
		pwd();
	else if (equal_str(cmd_line[0], "export"))
		export(cmd_line, data);
	else if (equal_str(cmd_line[0], "unset"))
		unset(cmd_line, data);
	else if (equal_str(cmd_line[0], "env"))
		env(data);
	else if (equal_str(cmd_line[0], "exit"))
		exit_minishell(cmd_line, data);
	else
		execute_bin(cmd_line, data);
}

void	exec_commands(t_data *data)
{
	dup2(data->fd_out[0], STDOUT_FILENO);
	dup2(data->fd_in[0], STDIN_FILENO);
	exec_cmd(data->cmd_lines, data);
}

void	split_and_exec(t_data *data, char *cmd_line)
{
	int	i;

	if (redirect_handler(&cmd_line, data))
		return ;
	data->cmd_lines = split_line(cmd_line);
	i = 0;
	while (data->cmd_lines[i])
		spec_sym_handler(&data->cmd_lines[i++], data);
	if (data->cmd_lines[0])
		exec_commands(data);
	i = 0;
	while (data->cmd_lines[i])
		free(data->cmd_lines[i++]);
	free(data->cmd_lines);
}
