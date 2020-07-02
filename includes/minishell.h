/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lacruype <lacruype@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 11:17:54 by rledrin           #+#    #+#             */
/*   Updated: 2020/07/02 17:05:41 by lacruype         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define BUFFER_SIZE 1

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <signal.h>
# include <errno.h>
# include <stdio.h>
# include <limits.h>
# include <dirent.h>
# include "../libft/includes/libft.h"

char	**g_envv;
char	**g_var;
int		exit_status;
int		ctrl_backslash;


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
int		start_minishell(void);
void	handle_sigquit(int sig);

int	redir(char *cmd);

/*
**		ft_utils.c 
*/

void	*ft_realloc(void *src, size_t new_size);
void	ft_freestrarr(char **arr);
char	*ft_jump_space(char *str);
int		create_file(char *filename, int app, int quote);
int		quote(char *cmd);

/*
**		ft_utils02.c ✅
*/

char	*ft_cmd_env(char *cmd, int i);
void    ft_cmd_to_lower(char **cmd);

/*
**		ft_utils03.c ✅
*/

void    f(char c);
int		ft_check_var_name(char *arg);
int		exec_cmd(char *cmd_line, char **split_cmd, char **path);

/*
**		ft_parsing.c ✅
*/

char	*ft_parsing(char *command_line);

/*
**		ft_echo.c ✅
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

int		ft_error(char *cmd, char *arg, int error);
void	ft_error02(char *arg, int error);

/*
**		LE_SPLIT.c
*/

char	**ft_split_semicolon(char const *s, char c);

/*
**		ft_path.c ✅
*/

int		ft_path(char **cmd, char **path);

/*
**		ft_escape_char.c
*/

int		ft_check_quotes_closed(const char *str, int i);

int			ft_export(char **args);
char			**ft_split_redir(char *s);

/*
**		ft_escape_char.c
*/

char        **ft_split_spaces_quotes_gone(char const *s, char c);

/*
**		ft_unset.c
*/

void	ft_unset(char **args);
char		**ft_delete_env(char **tab, int i);

/*
**		ft_cd.c
*/

int  	ft_cd(char **args);
void	ft_set_pwd(char *path, int pwd_indc, int oldpwd_indc);

#endif
