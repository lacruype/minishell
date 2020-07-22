# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lacruype <lacruype@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/09 16:37:58 by lacruype          #+#    #+#              #
#    Updated: 2020/07/06 15:02:20 by lacruype         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIB_NAME	=	libft.a

LIB_DIR		=	libft

OBJ_DIR		=	obj/

SRC_DIR		=	srcs/

INCLUDE		=	includes

SRC			=	ft_builtins.c \
				ft_cd.c \
				ft_cd02.c \
				ft_env.c \
				ft_error.c \
				ft_export.c \
				ft_parsing.c \
				ft_path.c \
				ft_pipe.c \
				ft_redir.c \
				ft_split_semicolon.c \
				ft_split_semicolon02.c \
				ft_split_semicolon03.c \
				ft_split_semicolon04.c \
				ft_split_spaces_quotes_gone.c \
				ft_split_spaces_quotes_gone02.c \
				ft_split_spaces_quotes_gone03.c \
				ft_start_minishell.c \
				ft_unset.c \
				ft_utils.c \
				ft_utils02.c \
				ft_utils03.c \
				ft_utils04.c \
				main.c \

SRCS		=	${addprefix ${SRC_DIR}, ${SRC}}

OBJS		=	${patsubst ${SRC_DIR}%.c,${OBJ_DIR}%.o,${SRCS}}

NAME		=	Minishell

RM			=	rm -f

CC			=	gcc

CFLAGS		=	-Wall -Wextra -Werror

T		=	$(words ${OBJS})
N		=	0
C		=	$(words $N)${eval N := X $N}
_CYAN	=	\033[36m
_GREEN	=	\033[32m
ECHO	=	"[`expr $C  '*' 100 / $T`%]"

all:	${NAME}

${OBJ_DIR}%.o :	${SRC_DIR}%.c
			@mkdir -p ${OBJ_DIR}
			@${CC} ${CFLAGS} -I ${INCLUDE} -I ${LIB_DIR}/includes -c $< -o $@
			@printf "%-60b\r" "${_CYAN}${ECHO}${_CYAN} Compiling $@"

${NAME}: ${OBJS}
	${MAKE} -C ${LIB_DIR}
	${CC} ${CFLAGS} -o ${NAME} ${OBJS}  -L${LIB_DIR} -lft

run : all
	./${NAME}

bonus: all

clean:
	${RM} ${OBJS}
	${MAKE} -C ${LIB_DIR} clean

fclean:	clean
	${RM} ${NAME}
	${RM} ${LIB_DIR}/${LIB_NAME}

re: fclean all