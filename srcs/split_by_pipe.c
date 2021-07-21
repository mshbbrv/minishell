#include "minishell.h"

void	*cmd_line_malloc(char **str_arr, char *str)
{
	int	cl_count;
	int	i;
	int	start;

	cl_count = 0;
	i = 0;
	while (str[i])
	{
		start = i;
		line_char_count(str, &i);
		str_arr[cl_count] = (char *) malloc(sizeof(char) * (i - start + 1));
		cl_count++;
		if (str[i])
			i++;
	}
	return (str_arr);
}

void	*cmd_lines_malloc(char **str_arr, char *str)
{
	int	count;

	count = command_line_count(str) + 1;
	str_arr = (char **)malloc(sizeof(char *) * (count + 1));
	if (!str_arr)
		return (NULL);
	return (cmd_line_malloc(str_arr, str));
}

char	**split_by_pipe(char *str)
{
	char	**str_arr;
	int		cl_count;
	int		i;
	int		cmd_chr;
	int		start;

	str_arr = NULL;
	str_arr = cmd_lines_malloc(str_arr, str);
	cl_count = 0;
	i = 0;
	while (str[i])
	{
		start = i;
		line_char_count(str, &i);
		cmd_chr = 0;
		while (start < i)
			str_arr[cl_count][cmd_chr++] = str[start++];
		str_arr[cl_count][cmd_chr] = '\0';
		cl_count++;
		if (str[i])
			i++;
	}
	str_arr[cl_count] = NULL;
	return (str_arr);
}
