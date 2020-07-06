/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lacruype <lacruype@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 11:17:54 by rledrin           #+#    #+#             */
/*   Updated: 2020/07/06 16:51:26 by lacruype         ###   ########.fr       */
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
# include <sys/wait.h>
# include "../libft/includes/libft.h"

char			**g_envv;
char			**g_var;
int				g_exit_status;
int				g_ctrl_backslash;
int				g_flag_prompt;

typedef struct	s_variables_minishell
{
	int			ret_gnl;
	int			ret_sf;
	int			check_exit;
	int			child_status;
	char		*cmd_line;
	char		**tab_cmd_line;
	char		**path;
	int			i;
	int			j;
	int			k;
	int			l;
	int			nb_pipe;
	int			ret;
	int			pi;
	int			pipe_fd[2];
	int			pi_fd2[2];
	char		**split_cmd;
	pid_t		pid;
}				t_var_minishell;

/*
**		ft_builtins.c ✅
*/

void			ft_pwd(void);
void			ft_echo(char **args);

/*
**		ft_cd.c
*/

int				ft_cd(char **args);

/*
**		ft_cd02.c
*/

void			ft_set_pwd(char *path, int pwd_indc, int oldpwd_indc);

/*
**		ft_env.c
*/

int				get_size_env(char **env);
int				init_g_envv(char **env);
void			ft_env(char **args);

/*
**		ft_error.c ✅
*/

int				ft_error(char *cmd, char *arg, int error);

/*
**		ft_export.c ✅
*/

int				ft_export(char **args);

/*
**		ft_parsing.c ✅
*/

char			*ft_parsing(char *command_line);

/*
**		ft_start_minishell.c ✅
*/

void			display_prompt(void);
int				start_minishell(t_var_minishell *p);

/*
**		ft_redir.c ✅
*/

char			**ft_split_redir(char *cmd);
int				redir(char *cmd);

/*
**		ft_utils.c ✅
*/

void			*ft_realloc(void *src, size_t new_size);
void			ft_freestrarr(char **arr);
char			*ft_jump_space(char *str);
int				create_file(char *filename, int app, int quote);
int				quote(char *cmd);

/*
**		ft_utils02.c ✅
*/

char			*ft_cmd_env(char *cmd, int i);
void			ft_cmd_to_lower(char **cmd);

/*
**		ft_utils03.c ✅
*/

void			f(char c);
int				ft_check_var_name(char *arg);
int				exec_cmd(char *cmd_line, char **split_cmd, char **path);

/*
**		ft_parsing.c ✅
*/

char			*ft_parsing(char *command_line);

/*
**		ft_path.c ✅
*/

int				ft_path(char **cmd, char **path);

/*
**		ft_pipe.c ✅
*/

int				cmpt_pipe(char *cmd);
void			exec_pipe(t_var_minishell *t, char *cmd);

/*
**		ft_redir.c ✅
*/

char			**ft_split_redir(char *cmd);
int				redir(char *cmd);

/*
**		ft_split_semicolon.c
*/

char			**ft_split_semicolon(char const *s, char c);
int				nb_words_semicolon(char const *str, char c);
int				size_words06(char strc, char ***tab, int *words, int *t);
void			place06(int *taille, int *words, int *i);
char			**size_words_semicolon(char const *str, char c, char **tab);
char			**place_words_semicolon(char const *str, char c, char **tab);

/*
**		ft_split_spaces_quotes_gone.c ✅
*/

char			**ft_split_spaces_quotes_gone(char const *s, char c);

/*
**		ft_split_spaces_quotes_gone02.c ✅
*/

int				nb_word_ssqg(char const *str, char c);

/*
**		ft_split_spaces_quotes_gone03.c ✅
*/

char			**size_ssqg(char const *str, char c, char **tab);

/*
**		ft_start_minishell.c ✅
*/

void			display_prompt(void);
int				start_minishell(t_var_minishell *t);

/*
**		ft_unset.c ✅
*/

char			**ft_delete_env(char **tab, int i);
void			ft_unset(char **args);

/*
**		ft_path.c ✅
*/

int				cmpt_pipe(char *cmd);
void			exec_pipe(t_var_minishell *t, char *cmd);

/*
**		ft_utils.c ✅
*/

void			*ft_realloc(void *ptr, size_t size);
void			ft_freestrarr(char **arr);
char			*ft_jump_space(char *str);
int				create_file(char *filename, int app, int quote);
int				quote(char *cmd);

/*
**		ft_utils02.c ✅
*/

void			ft_cmd_to_lower(char **cmd);
char			*ft_cmd_env(char *cmd, int i);

/*
**		ft_utils03.c ✅
*/

void			f(char c);
int				ft_check_quotes_closed(const char *s, int i);
int				ft_check_var_name(char *arg);
int				exec_cmd(char *cmd_line, char **split_cmd, char **path);

/*
**		main.c ✅
*/

int				search_function(char *cmd_line, char **path);
void			exec_com(char *cmd, int in, int out, char **path);
void			handle_sigint(int sig);
void			handle_sigquit(int sig);
int				redir(char *cmd);

#endif
