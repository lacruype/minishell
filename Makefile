# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lacruype <lacruype@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/09 16:37:58 by lacruype          #+#    #+#              #
#    Updated: 2020/02/06 13:05:06 by lacruype         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Minishell

PATH = srcs/

SRCS =	$(PATH)main.c \
		$(PATH)ft_echo.c \
		$(PATH)ft_utils.c \
		$(PATH)get_next_line.c \
		$(PATH)get_next_line_utils.c \
		$(PATH)ft_pwd.c \

LIB = includes

OBJS = ${SRCS:.c:=.o}

FLAGS = -Wall -Werror -Wextra

all:${NAME}

${NAME}:	${OBJS}
			gcc ${FLAGS} ${OBJS} -o ${NAME} -I ${LIB} LIBFT/libft.a

clean:
	/bin/rm -f *.o

fclean: clean
	/bin/rm -f ${NAME}

re: fclean all

.PHONY:all clean fclean re