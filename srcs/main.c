#include "minishell.h"

void	add_shlvl(t_data *data, int new_shlvl)
{
	int		i;
	char	*tmp;
	char	*shlvl;

	i = find_env_var("SHLVL", data->envp);
	shlvl = ft_itoa(new_shlvl);
	tmp = str_3_join("SHLVL", "=", shlvl);
	free(shlvl);
	if (i == -1)
		add_env_var(data, tmp);
	else
	{
		free(data->envp[i]);
		data->envp[i] = ft_strdup(tmp);
	}
	free(tmp);
}

void	change_shlvl(t_data *data)
{
	char	*shlvl;
	int		new_shlvl;

	shlvl = NULL;
	shlvl = get_minishell_env("SHLVL", data->envp);
	if (!shlvl)
		new_shlvl = 1;
	else
	{
		new_shlvl = ft_atoi(shlvl);
		free(shlvl);
		if (new_shlvl < 0)
			new_shlvl = 0;
		else
			new_shlvl++;
	}
	add_shlvl(data, new_shlvl);
}

void	change_oldpwd(t_data *data)
{
	int	i;

	i = find_env_var("OLDPWD", data->envp);
	if (i == -1)
		return ;
	ft_strlcpy(data->envp[i], "OLDPWD", 7);
}

void	init(t_data *data, char **envp)
{
	data->line_read = NULL;
	data->cmd_lines = NULL;
	data->fd_out[0] = STDOUT_FILENO;
	data->fd_in[0] = STDIN_FILENO;
	data->fd_out[1] = dup(STDOUT_FILENO);
	data->fd_in[1] = dup(STDIN_FILENO);
	g_exit_status = 0;
	data->envp = copy_envp(envp);
	data->envp_exp = copy_envp(envp);
	change_shlvl(data);
	change_oldpwd(data);
	data->heredoc_ctrl_d = 0;
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	(void)argc;
	(void)argv;
	data = (t_data *) malloc(sizeof(t_data));
	init(data, envp);
	while (1)
	{
		readline_history("\e[32mminishell> \e[0m", data);
		if (!data->line_read)
			ctrl_d(data);
		if (data->line_read && *data->line_read && empty_line(data->line_read))
			parsing(data);
	}
}
