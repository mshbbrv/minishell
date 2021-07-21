# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thjonell <thjonell@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/29 20:54:40 by thjonell          #+#    #+#              #
#    Updated: 2021/04/28 15:43:22 by thjonell         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= libft.a

CC			= gcc

RM			= rm -f

CFLAGS		= -Wall -Wextra -Werror

SOURCE		= ft_putnbr_fd.c ft_putendl_fd.c ft_putstr_fd.c ft_putchar_fd.c \
			ft_strmapi.c ft_itoa.c ft_split.c ft_strtrim.c ft_strjoin.c \
			ft_substr.c ft_strdup.c ft_calloc.c ft_tolower.c ft_toupper.c \
			ft_isprint.c ft_isascii.c ft_isalnum.c ft_isdigit.c ft_isalpha.c \
			ft_atoi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strchr.c \
			ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_memcmp.c ft_memchr.c \
			ft_memmove.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c

BONUS_SRS	= ft_lstmap.c ft_lstiter.c ft_lstclear.c ft_lstdelone.c \
			ft_lstadd_back.c ft_lstlast.c ft_lstsize.c ft_lstadd_front.c \
			ft_lstnew.c

OBJECTS 	= ${SOURCE:.c=.o}

BONUS_OBJ	= ${BONUS_SRS:.c=.o}

INCLUDE		= libft.h

.c.o:
			${CC} ${CFLAGS} -I${INCLUDE} -c $< -o ${<:.c=.o}

all:		${NAME}

$(NAME):	${OBJECTS}
			ar rc	${NAME} ${OBJECTS}
			ranlib	${NAME}

bonus:		${NAME}	${BONUS_OBJ}
			ar rc	${NAME} ${BONUS_OBJ}
			ranlib	${NAME}

clean:
			${RM} ${OBJECTS} ${BONUS_OBJ}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

rebonus:	fclean bonus

.PHONY:		all clean fclean re bonus rebonus