
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
int savefd[2];

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
	while (g_envv[i] && ft_strncmp(g_envv[i], "PWD=", 4) != 0)
		i++;
	if(g_envv[i] == NULL)
		return ;
	ft_putstr_fd(&g_envv[i][4], 1);
	ft_putstr_fd(" ➡ ", 1);
}

char	*get_filename(char *cmd)
{
	char	*filename;
	int		i;
	int		j;

	filename = 0;
	i = 0;
	j = 0;
	i = ft_jump_space(cmd) - cmd;
	
	while (cmd[i + j] && cmd[i + j] != ' ')
	{
		filename = ft_realloc(filename, j);
		filename[j] = cmd[i + j];
		j++;
	}
	return (filename);
}

int		search_function(char *cmd_line, char **path)
{
	int i;
	int j;
	char **split_cmd;
	char *tmp;
	char *filename;

	i = 0;
	j = 0;
	while (cmd_line[j])
	{
		if ((tmp = ft_strchr("><", cmd_line[j])))
		{
			if (*tmp == '>' && cmd_line[j + 1] == '>')
			{
				filename = get_filename(&cmd_line[j + 2]);
				dup2(open(filename, O_CREAT | O_APPEND | O_WRONLY, 0666), savefd[1]);
			}
			else if (*tmp == '>')
			{
				filename = get_filename(&cmd_line[j + 1]);
				dup2(open(filename, O_CREAT | O_TRUNC | O_WRONLY, 0666), savefd[1]);
			}
			else if (*tmp == '<')
			{
				filename = get_filename(&cmd_line[j + 1]);
				dup2(open(filename, O_RDONLY), savefd[0]);
			}
			else
			{
				printf("ERROR\n");
				return (-1);
			}
		}
		j++;
	}
	split_cmd = ft_split_cmd(cmd_line);

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

static void	exec_command(char *cmd, int in, int out, char **path)
{
	printf("IN = %d et OUT = %d\n", in, out);
	if (in != 0)
	{
		dup2(in, 0);
		close(in);
	}
	if (out != 1)
	{
		dup2(out, 1);
		close(out);
	}
	search_function(cmd, path);
}

void	exec_pipe(char *cmd, char **path, int nb_pipe)
{
	int i;
	int pipe_num;
	int pid;
	int child_status;
	int pipe_fd[2];
	int pipe_fd2[2];
	int j = 0;

	i = 0;
	savefd[0] = dup(0);
	savefd[1] = dup(1);
	pipe_num = 0;
	if (pipe(pipe_fd) == -1 || pipe(pipe_fd2) == -1)
	{
		write(1, "ERROR: PIPE\n", 13);
		exit(EXIT_FAILURE);
	}
	while (cmd[i])
	{
		j = i;
		if (cmd[i] == '|')
		{
			pipe_num++;
			i++;
		}
		if (pipe_num == 0)
		{
			if ((pid = fork()) == 0)
			{
				close(pipe_fd[0]);
				exec_command(&cmd[i], 0, pipe_fd[1], path);
				exit(0);
			}
			else if (pid == -1)
				printf("Error fork\n");
			close(pipe_fd[1]);
			wait(NULL);
		}
		else if (pipe_num == nb_pipe)
		{
			printf("pipe num = %d\n", pipe_num);
			if ((pid = fork()) == 0)
			{
				if (pipe_num % 2 == 0)
					exec_command(&cmd[i], pipe_fd2[0], 1, path);
				else
					exec_command(&cmd[i], pipe_fd[0], 1, path);
				exit(0);
			}
			else if (pid == -1)
				printf("Error fork2\n");
			if (pipe_num % 2 == 0)
				close(pipe_fd2[0]);
			else
				close(pipe_fd[0]);
			wait(NULL);
		}
		else
		{
			printf("pipe num = %d\n", pipe_num);
			if (pipe_num % 2 == 0)
			{
				if (pipe(pipe_fd) == -1)
				{
					write(1, "ERROR: PIPE\n", 13);
					exit(EXIT_FAILURE);
				}
			}
			else
			{
				if (pipe(pipe_fd2) == -1)
				{
					write(1, "ERROR: PIPE\n", 13);
					exit(EXIT_FAILURE);
				}
			}
			if ((pid = fork()) == 0)
			{
				if (pipe_num % 2 == 0)
					exec_command(&cmd[i], pipe_fd2[0], pipe_fd[1], path);
				else
					exec_command(&cmd[i], pipe_fd[0], pipe_fd2[1], path);
				exit(0);
			}
			else if (pid == -1)
				printf("Error fork2\n");
			if (pipe_num % 2 == 0)
			{
				close(pipe_fd2[0]);
				close(pipe_fd[1]);
			}
			else
			{
				close(pipe_fd[0]);
				close(pipe_fd2[1]);
			}
			waitpid(pid, &child_status, 0);
		}
		while (cmd[i] != '|' && cmd[i] != '\0')
			i++;
	}
}

int		start_minishell(char **path)
{
	int		i;
	int		j;
	int		k;
	int		nb_pipe;

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
					if (nb_pipe == 0)
						search_function(&t.tab_cmd_line[i][j], path);
					else
						exec_pipe(t.tab_cmd_line[i], path, nb_pipe);
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
	if (sig == SIGINT)
	{
		ft_putstr_fd("\b\b  \n", 1);
		signal(SIGINT, handle_sigint);
		display_prompt();
		flag_prompt = 1;
	}
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
