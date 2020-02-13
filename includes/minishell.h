/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rledrin <rledrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 11:17:54 by rledrin           #+#    #+#             */
/*   Updated: 2020/02/13 13:38:31 by rledrin          ###   ########.fr       */
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
# include <dirent.h>
# include "libft.h"
# include "get_next_line.h"

char	**g_envv;

/*
**		main.c
*/

int		search_function(char *cmd_line, char **path);
int		start_minishell(char **path);

/*
**		ft_utils.c
*/

void	*ft_realloc(void *src, size_t new_size);
void	ft_freestrarr(char **arr);
char	*ft_jump_space(char *str);
int		create_file(char *filename, int app, int quote);
int		quote(char *cmd);


/*
**		ft_parsing01.c
*/

int		ft_parsing(char **command_line);

/*
**		ft_echo.c
*/

void	ft_echo(char *cmd);

/*
**		ft_pwd.c
*/

void	ft_pwd(char *cmd);

/*
**		ft_env.c
*/

void	ft_env(char *cmd);



/*
**		ft_envv.c
*/

int				init_g_envv(char **env);

/*
**		ft_error.c
*/

void	ft_error(int error);

#endif
