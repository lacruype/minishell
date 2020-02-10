/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rledrin <rledrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 11:17:54 by rledrin           #+#    #+#             */
/*   Updated: 2020/02/10 12:57:15 by rledrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define BUFFER_SIZE 1

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <signal.h>

# include <stdio.h>
# include <limits.h>
# include "libft.h"
# include "get_next_line.h"

char	**g_envv;

/*
**		main.c
*/

int		search_function(char **cmd_line_split);
int		start_minishell(void);

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
