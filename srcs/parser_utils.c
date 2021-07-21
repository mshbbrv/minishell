#include "minishell.h"

void	reset_fd_to_default(t_data *data)
{
	dup2(data->fd_out[1], STDOUT_FILENO);
	dup2(data->fd_in[1], STDIN_FILENO);
	data->fd_out[0] = STDOUT_FILENO;
	data->fd_in[0] = STDIN_FILENO;
}

void	readline_history(char *prompt, t_data *data)
{
	if (data->line_read && *data->line_read)
	{
		free(data->line_read);
		data->line_read = NULL;
	}
	signal(SIGINT, ctrl_c);
	signal(SIGQUIT, SIG_IGN);
	tcgetattr(STDOUT_FILENO, &data->config);
	data->config.c_lflag &= ~ECHOCTL;
	tcsetattr(STDOUT_FILENO, TCSANOW, &data->config);
	data->line_read = readline(prompt);
	data->config.c_lflag |= ECHOCTL;
	tcsetattr(STDOUT_FILENO, TCSANOW, &data->config);
	signal(SIGINT, ctrl_c_child);
	signal(SIGQUIT, ctrl_slash_child);
	if (data->line_read && *data->line_read)
		add_history(data->line_read);
}

char	*string_join(char *str1, char *str2)
{
	char	*str;
	int		i;

	str = malloc(ft_strlen(str1) + ft_strlen(str2) + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (*str1)
		*(str + i++) = *str1++;
	while (*str2)
		*(str + i++) = *str2++;
	*(str + i) = '\0';
	if (*str1)
		free(str1);
	return (str);
}

char	**copy_envp(char **envp)
{
	char	**envp_copy;
	int		i;

	i = 0;
	envp_copy = malloc(sizeof(char *) * (strings_counter(envp) + 1));
	while (envp[i])
	{
		envp_copy[i] = ft_strdup(envp[i]);
		i++;
	}
	envp_copy[i] = NULL;
	return (envp_copy);
}

void	make_string(char **str, char c)
{
	char	*tmp;

	tmp = ft_calloc(ft_strlen(*str) + 2, sizeof (char));
	ft_memcpy(tmp, *str, ft_strlen(*str));
	tmp[ft_strlen(tmp)] = c;
	if (*str)
		free(*str);
	*str = tmp;
}
