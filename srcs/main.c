
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rledrin <rledrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 11:14:32 by rledrin           #+#    #+#             */
/*   Updated: 2020/02/12 18:54:14 by rledrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int pid;
int flag_prompt = 0;

void	ft_update_g_envv(int child_status)
{
	char *tmp;
	int i;

	i = 0;
	while (ft_strncmp(g_envv[i], "?=", 2) != 0 && g_envv[i] != NULL)
		i++;
	if (g_envv[i] == NULL)
		return ((void)ft_error(3));
	tmp = g_envv[i];
	free(tmp);
	tmp = ft_itoa((WEXITSTATUS(child_status)));
	g_envv[i] = ft_strjoin("?=", tmp);
	free(tmp);
}

char	**init_path(void)
{
	int i;
	char **path;

	i = 0;
	while (g_envv[i] != NULL)
	{
		if (ft_strncmp((const char*)g_envv[i], "PATH", 4) == 0)
			path = ft_split((const char*)&g_envv[i][5], ':');
		i++;
	}
	return (path);
}

void	display_prompt(void)
{
	int i;

	i = 0;
	while (ft_strncmp(g_envv[i], "PWD=", 4) != 0)
		i++;
	ft_putstr_fd(&g_envv[i][4], 1);
	ft_putstr_fd(" ➡ ", 1);
}

int		search_function(char *cmd_line, char **path)
{
	int i;
	char **split_cmd;

	i = 0;
	split_cmd = ft_split_cmd(cmd_line); // il faut gerer les quotes

	if (ft_strncmp(split_cmd[0], "exit", 4) == 0) // gerer le cas exit | echo
	{
		write(1, "exit\n", 5);
		exit(0);
	}
	if (ft_path(split_cmd, path) == -1)
		return (ft_error(5));
	return (0);
}

int		cmpt_pipe(char *cmd)
{
	int i;
	int nb_pipe;

	i = 0;
	nb_pipe = 0;
	while (cmd[i])
	{
		if (cmd[i] == '|')
			nb_pipe++;
		i++;
	}
	return (nb_pipe);
}

void	exec_pipe(char *cmd, char **path)
{
	int i;
	int k;
	int pid;
	int child_status;
	int pipe_fd[2];
	int save_fd[2];

	i = 0;
	save_fd[0] = dup(0);
	save_fd[1] = dup(1);
	while (cmd[i])
	{
		if (pipe(pipe_fd) == -1)
			write(1, "ERROR: PIPE\n", 13);
		k = 0;
		if (cmd[i] == '|')
			i++;
		while (cmd[i + k] && cmd[i + k] != '|')
			k++;
		if (cmd[i - 1] == '|')
		{
			close(pipe_fd[1]);
			dup2(pipe_fd[0], 0);
		}
		else
			close(pipe_fd[0]);
		if (cmd[i + k] == '|')
		{
			dup2(pipe_fd[1], 1);
			close(pipe_fd[0]);
		}
		else
			close(pipe_fd[1]);
		
		if (search_function(cmd, path) == -1)
			write(1, "COMMANDE PAS TROUVER\n", 22);
		// waitpid(pid, &child_status, 0);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		
		dup2(save_fd[0], 0);
		dup2(save_fd[1], 1);
		i += k;
	}
}

int		start_minishell(char **path)
{
	int		i;
	int		j;
	int		k;
	int		nb_pipe;
	char	buf[20];

	t.ret_gnl = 1;
	t.check_exit = 0;
	nb_pipe = 0;
	while (t.ret_gnl == 1 && t.check_exit == 0)
	{
		if (flag_prompt != 1)
			display_prompt();
		flag_prompt = 0;
		if (!get_next_line(0, &t.cmd_line))
		{
			ft_putstr_fd("exit\n", 1);
			exit(56);
		}
		if (t.cmd_line != NULL && (t.cmd_line = ft_parsing(t.cmd_line)) != NULL)
		{
			if ((t.tab_cmd_line = ft_split_semicolon(t.cmd_line, ';')) != NULL)
			{
				i = 0;
				while (t.tab_cmd_line[i] != NULL)
				{
					nb_pipe = cmpt_pipe(t.tab_cmd_line[i]);
					j = 0;
					k = 0;
					// if (t.tab_cmd_line[i][j] == '|')
					// 	j++;
					// while (t.tab_cmd_line[i][j + k] && t.tab_cmd_line[i][j + k] != '|')
					// 	k++;
					// if (t.tab_cmd_line[i][j - 1] == '|')
					// {
					// 	if (pipe_nb % 2 == 0)
					// 	{
					// 		dup2(pip1[0], 0);
					// 		close(pip1[1]);
					// 	}
					// 	else
					// 	{
					// 		dup2(pip2[0], 0);
					// 		close(pip2[1]);
					// 	}
					// }
					// else
					// {
					// 	close(pip1[0]);
					// 	close(pip2[0]);
					// }
					// if (t.tab_cmd_line[i][j + k] == '|')
					// {
					// 	pipe_nb++;
					// 	if (pipe_nb % 2 == 1)
					// 	{
					// 		dup2(pip1[1], 1);
					// 		close(pip1[0]);
					// 	}
					// 	else
					// 	{
					// 		dup2(pip2[1], 1);
					// 		close(pip2[0]);
					// 	}
					// }
					// else
					// {
					// 	close(pip1[1]);
					// 	close(pip2[1]);
					// }
					if (nb_pipe == 0)
						search_function(&t.tab_cmd_line[i][j], path);
					else
					{
						exec_pipe(t.tab_cmd_line[i], path);
					}
						
					i++;
				}
				ft_freestrarr(t.tab_cmd_line);
			}
			free(t.cmd_line);
		}
	}
	return (0);
}

void	handle_sigint(int sig)
{
	ft_putstr_fd("\b\b  \n", 1);
	signal(SIGINT, handle_sigint);
	display_prompt();
	flag_prompt = 1;
}

int		main(int ac, char **av, char **env)
{
	(void)av;
	char	**path;
	if (ac != 1)
		return (0);
	signal(SIGINT, handle_sigint);
	if (init_g_envv(env) == -1)
		return (-1);
	path = init_path();
	if (start_minishell(path) == -1)
		return (-1);
	ft_freestrarr(path);
	return (0);
}
