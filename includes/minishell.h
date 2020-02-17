/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lacruype <lacruype@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 11:17:54 by rledrin           #+#    #+#             */
/*   Updated: 2020/02/17 15:56:31 by lacruype         ###   ########.fr       */
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

char	**g_envv;

/*
**		main.c
*/

int		search_function(char *cmd_line, char **path, int *pip);
int		start_minishell(char **path, int *pip);

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

int		init_g_envv(char **env);

/*
**		ft_error.c
*/

int		ft_error(int error);

/*
**		LE_SPLIT.c
*/

char	**ft_split_semicolon(char const *s, char c);

/*
**		ft_path.c
*/

int		ft_path(char *cmd, char **path, int *pip);

/*
**		ft_escape_char.c
*/

int		jump_quotes(const char *str, int i);

#endif
