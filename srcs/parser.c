#include "minishell.h"

int 	empty_line(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] != '\0')
		return (1);
	return (0);
}

void	parsing_start(t_data *data)
{
	char	**tmp;
	char	*line_read;
	int		pipes_count;
	int		i;

	tmp = NULL;
	line_read = NULL;
	pipes_count = command_line_count(data->line_read);
	if (pipes_count > 0)
	{
		tmp = split_by_pipe(data->line_read);
		exec_cmd_line_with_pipes(data, tmp, pipes_count + 1);
		i = 0;
		while (tmp[i])
			free(tmp[i++]);
		free(tmp);
	}
	else
	{
		line_read = ft_strdup(data->line_read);
		split_and_exec(data, line_read);
		if (line_read)
			free(line_read);
		reset_fd_to_default(data);
	}
}

void	parsing(t_data *data)
{
	int	syntax_error;

	syntax_error = check_syntax(data->line_read);
	if (syntax_error == 1)
		error_handler("syntax error near unexpected token `|'", 258);
	else if (syntax_error == 2)
		error_handler("syntax error near unexpected token `>'", 258);
	else if (syntax_error == 3)
		error_handler("syntax error near unexpected token `newline'", 258);
	else if (syntax_error == 4)
		error_handler("syntax error near unexpected token `>>'", 258);
	else if (syntax_error == 5)
		error_handler("syntax error near unexpected token `<'", 258);
	else if (syntax_error == 6)
		error_handler("syntax error near unexpected token `<<'", 258);
	else
		parsing_start(data);
}
