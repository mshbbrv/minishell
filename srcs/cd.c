#include "minishell.h"

void	cd_err_handler(char *str1, char *str2, char *str3)
{
	char	*tmp;
	char	*tmp2;

	tmp = str_3_join(str1, str2, str3);
	tmp2 = ft_strjoin(tmp, strerror(errno));
	error_handler(tmp2, 1);
	free(tmp);
	free(tmp2);
}

int	check_getcwd_func(char *str)
{
	if (!str)
	{
		error_handler(strerror(errno), 1);
		return (-1);
	}
	return (0);
}

int	cd_home(t_data *data)
{
	char	*home;

	home = get_minishell_env("HOME", data->envp);
	if (!home)
	{
		error_handler("cd: HOME not set", 1);
		return (1);
	}
	if (chdir(home) == -1)
	{
		cd_err_handler("cd: ", home, ": ");
		free(home);
		return (1);
	}
	free(home);
	return (0);
}

void	check_and_change_oldpwd(char *old_pwd, t_data *data)
{
	char	*tmp;

	tmp = get_minishell_env("OLDPWD", data->envp);
	if (!old_pwd && tmp)
	{
		add_env_var(data, "OLDPWD=\0");
		free(tmp);
	}
	else
		change_envp_oldpwd("OLDPWD", old_pwd, data);
}

int	cd(char **cmd_line, t_data *data, int ret)
{
	char	*old_pwd;
	char	*pwd;

	old_pwd = get_minishell_env("PWD", data->envp);
	check_and_change_oldpwd(old_pwd, data);
	if (strings_counter(cmd_line) == 1)
		ret = cd_home(data);
	else if (chdir(cmd_line[1]) == -1)
	{
		cd_err_handler("cd: ", cmd_line[1], ": ");
		ret = 1;
	}
	pwd = getcwd(NULL, 0);
	if (check_getcwd_func(pwd) == -1)
		return (1);
	if (old_pwd)
		change_envp_pwd("PWD", pwd, data);
	free(pwd);
	free(old_pwd);
	return (ret);
}
