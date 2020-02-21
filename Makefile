# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rledrin <rledrin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/09 16:37:58 by lacruype          #+#    #+#              #
#    Updated: 2020/02/21 15:09:41 by rledrin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Minishell

PATH = srcs/

SRCS =	$(PATH)main.c \
		$(PATH)ft_echo.c \
		$(PATH)ft_utils.c \
		$(PATH)ft_utils02.c \
		$(PATH)ft_pwd.c \
		$(PATH)ft_envv.c \
		$(PATH)ft_error.c \
		$(PATH)ft_parsing01.c \
		$(PATH)ft_env.c \
		$(PATH)ft_split_semicolon.c \
		$(PATH)ft_path.c \
		$(PATH)ft_escape_char.c \
		$(PATH)ft_split_cmd.c \

LIB = includes

OBJS = ${SRCS:.c:=.o}

FLAGS = -Wall -Werror -Wextra
#FLAGS += -fsanitize=address,undefined

all:${NAME}

${NAME}:	${OBJS}
			gcc ${FLAGS} ${OBJS} -o ${NAME} -I ${LIB} LIBFT/libft.a

g3:	${OBJS}
			gcc ${FLAGS} ${OBJS} -o ${NAME} -I ${LIB} LIBFT/libft.a -g3 -fsanitize=address

clean:
	/bin/rm -f *.o

fclean: clean
	/bin/rm -f ${NAME}

re: fclean all

.PHONY:all clean fclean re g3
