/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lacruype <lacruype@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 11:17:54 by rledrin           #+#    #+#             */
/*   Updated: 2020/06/23 16:54:00 by lacruype         ###   ########.fr       */
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
# include "../libft/includes/libft.h"

char	**g_envv;
char	**g_var;

typedef struct	variables_minishell
{
	int		ret_gnl;
	int		ret_sf;
	int		check_exit;
	int		child_status;
	char	*cmd_line;
	char	**tab_cmd_line;
	pid_t	pid;
}				var_minishell;

var_minishell t;

/*
**		main.c
*/

int		ft_path_pipe(char **cmd, char **path);
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
**		ft_utils02.c
*/

void    ft_cmd_to_lower(char **cmd);

/*
**		ft_parsing01.c
*/

char	*ft_parsing(char *command_line);

/*
**		ft_echo.c
*/

void	ft_echo(char **args);

/*
**		ft_pwd.c
*/

void	ft_pwd(void);

/*
**		ft_env.c
*/

void	ft_env(char **args);

/*
**		ft_envv.c
*/

int		get_size_env(char **env);
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

int		ft_path(char **cmd, char **path);

/*
**		ft_escape_char.c
*/

int		ft_check_quotes_closed(const char *str, int i);

void			ft_export(char **args);
char			**ft_split_redir(char *s);

/*
**		ft_escape_char.c
*/

char        **ft_split_spaces_quotes_gone(char const *s, char c);

/*
**		ft_escape_char.c
*/

void	ft_unset(char **args);

/*
**		ft_cd.c
*/

void 	ft_cd(char **args);

#endif
