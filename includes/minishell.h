/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lacruype <lacruype@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 11:17:54 by rledrin           #+#    #+#             */
/*   Updated: 2020/02/06 16:51:23 by lacruype         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define BUFFER_SIZE 1

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <signal.h>
# include <sys/wait.h>
# include <stdio.h>
# include "libft.h"
# include "get_next_line.h"

/*
**		main.c
*/

int		search_function(char **cmd_line_split, char **env);
int		start_minishell(char **env);

/*
**		ft_utils.c.c
*/

void	*ft_realloc(void *dst, size_t new_size);
int		ft_jump_space(char *str, int i);

/*
**		ft_parsing01.c
*/

int		ft_parsing(char *command_line);

#endif
