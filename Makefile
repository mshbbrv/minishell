NAME		= minishell
CC			= gcc
RM			= rm -rf
CFLAGS		= -g -Wall -Wextra -Werror
SRCS_LIST	= main.c parser.c exec_commands.c syntax_handler.c spec_sym_handler.c split_by_pipe.c parser_utils.c \
			env_handler.c redirect_handler.c split_line.c split_line_utils.c split_by_pipe_utils.c \
			echo.c cd.c pwd.c export.c unset.c env.c exit_minishell.c exec_with_pipe.c exec_with_pipe_utils.c \
			strings_counter.c execute_bin.c join_str_to_arr.c get_minishell_env.c signals.c \
			redirect_handler_utils.c redirect_handler_utils_2.c envp_utils.c str_3_join.c env_handler_utils.c \
			cmd_not_found.c command_execution_utils.c cd_utils.c error_handler.c
SRCS		= $(addprefix $(SRCS_DIR)/, $(SRCS_LIST))
LIB_FT		= -Llibft -lft
RL_LIB		= -lreadline -L/Users/$(USER)/.brew/opt/readline/lib
OBJ_LIST 	= $(patsubst %.c, %.o, $(SRCS_LIST))
OBJ 		= $(addprefix $(OBJ_DIR)/, $(OBJ_LIST))
INC_DIR		= inc
RL_INC_DIR	= /Users/$(USER)/.brew/opt/readline/include
SRCS_DIR	= srcs
OBJ_DIR		= obj
all:		$(NAME)
$(NAME):	$(OBJ)
			cd libft && make bonus
			$(CC) $(CFLAGS) $(OBJ) $(LIB_FT) $(RL_LIB) -o $(NAME)
$(OBJ_DIR)/%.o : $(SRCS_DIR)/%.c | $(OBJ_DIR)
			$(CC) $(CFLAGS) -I$(INC_DIR) -I$(RL_INC_DIR) -c $< -o $@
$(OBJ_DIR):
			mkdir -p $@
clean:
			cd libft && make clean
			$(RM) $(OBJ_DIR)
fclean:		clean
			cd libft && make fclean
			$(RM) $(NAME)
re:			fclean all
.PHONY:		all clean fclean re