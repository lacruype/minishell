# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lacruype <lacruype@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/10 11:44:06 by lacruype          #+#    #+#              #
#    Updated: 2020/03/05 16:01:45 by lacruype         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ROOT	=	./srcs/

HROOT	=	includes/

FILES	=	ft_atoi.c			ft_bzero.c				ft_isalnum.c			ft_strlcat.c	\
			ft_isalpha.c		ft_isascii.c			ft_isdigit.c			ft_isprint.c	\
			ft_itoa.c			ft_putstr_fd.c 			ft_putnbr_fd.c 			ft_putendl_fd.c	\
			ft_memcmp.c			ft_memcpy.c				ft_strtrim.c			ft_memset.c		\
			ft_split.c			ft_strchr.c				ft_strdup.c								\
			ft_strjoin.c		ft_strlcpy.c 			ft_putchar_fd.c 		ft_memchr.c		\
			ft_strlen.c			ft_strmapi.c			ft_strncmp.c			ft_strnstr.c	\
			ft_strrchr.c		ft_substr.c				ft_tolower.c 							\
			ft_toupper.c		ft_calloc.c				ft_memccpy.c 			ft_memmove.c	\
			ft_putstrstr.c		get_next_line.c			get_next_line_utils.c 	\

SRCS	=	$(addprefix ${ROOT}, ${FILES})

OBJS	=	${SRCS:.c=.o}

NAME	=	libft.a

CC		=	gcc

RM		=	rm -f

CFLAGS	=	-Wall -Wextra -Werror -I ${HROOT}

T		=	$(words ${OBJS})
N		=	0
C		=	$(words $N)${eval N := X $N}
_CYAN	=	\033[36m
_GREEN	=	\033[32m
ECHO	=	"[`expr $C  '*' 100 / $T`%]"

.PHONY:	fclean clean re


%.o :	%.c
		@${CC} ${CFLAGS} -c $< -o ${<:.c=.o}
		@printf "%-60b\r" "${_CYAN}${ECHO}${_CYAN} Compiling $@"

${NAME}:	${OBJS}
	@ar rcs ${NAME} ${OBJS}
	@printf "\r%b" "${_GREEN}Library ${NAME} compiled successfully! :D\n"
	

all:	${NAME}

bench:
	gcc ${CFLAGS} -shared -o libft.so -fPIC ${ROOT}ft_*.c

clean:
		@${RM} ${OBJS}

fclean:	clean
		@${RM} ${NAME}
		@${RM} libft.so

re:		fclean all