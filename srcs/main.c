
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

char	**init_path(char **path)
{
	int i;

	i = 0;
	if (path != NULL)
		ft_freestrarr(path);
	path = NULL;
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
	char buf[255];

	i = 0;
	while (g_envv[i] && ft_strncmp(g_envv[i], "PWD=", 4) != 0)
		i++;
	if(g_envv[i] == NULL)
	{
		ft_putstr_fd(getcwd(buf, 255), 1);
		ft_putstr_fd(" ➡ ", 1);
		return ;
	}
	ft_putstr_fd(&g_envv[i][4], 1);
	ft_putstr_fd(" ➡ ", 1);
	flag_prompt = 0;
}

char	*get_filename(char *cmd)
{
	char	*filename;
	int		i;
	int		j;
	char	*tmp;

	filename = ft_strdup("");
	i = 0;
	j = 0;

	while (cmd[i] == ' ')
		i++;
	while (cmd[i + j] && !(tmp = ft_strchr(" |<>", cmd[i + j])))
	{
		filename = ft_realloc(filename, (j + 2) * sizeof(char));
		filename[j] = cmd[i + j];
		j++;
	}
	if (tmp && (*tmp == '<' || *tmp == '>'))
	{
		printf("ERRORFILENAME\n");
		return (0);
	}
	filename[j] = '\0';
	return (filename);
}

static int	redir(char *cmd)
{
	char	*filename;
	char	*tmp;
	int		fd;
	int		j;

	j = 0;
	fd = 0;
	while (cmd[j] && cmd[j] != '|')
	{
		j = ft_check_quotes_closed(cmd, j);
		if ((tmp = ft_strchr("><", cmd[j])))
		{
			if (*tmp == '>' && cmd[j + 1] == '>')
			{
				filename = get_filename(&cmd[j + 2]);
				fd = open(filename, O_WRONLY | O_APPEND | O_APPEND, 0666);
				dup2(fd, 1);
				j += 2;
			}
			else if (*tmp == '>' && (cmd[j + 1] == ' ' || ft_isalpha(cmd[j + 1])))
			{
				filename = get_filename(&cmd[j + 1]);
				fd = open(filename, O_CREAT | O_TRUNC | O_WRONLY, 0666);
				dup2(fd, 1);
				j++;
			}
			else if (*tmp == '<' && (cmd[j + 1] == ' ' || ft_isalpha(cmd[j + 1])))
			{
				filename = get_filename(&cmd[j + 1]);
				fd = open(filename, O_RDONLY);
				dup2(fd, 0);
				j++;
			}
			else
			{
				printf("ERRORREDIR\n");
				return (-1);
			}
		}
		j++;
	}
	return(fd);
}

static int		cmpt_pipe(char *cmd)
{
	int i;
	int nb_pipe;

	i = 0;
	nb_pipe = 0;
	while (cmd[i])
	{
		i = ft_check_quotes_closed(cmd, i);
		if (cmd[i] == '|')
			nb_pipe++;
		i++;
	}
	return (nb_pipe);
}
int		exec_cmd(char *cmd_line, char **split_cmd, char **path)
{
	int	savefd[2];
	int	fd;
	int ret;

	savefd[0] = dup(0);
	savefd[1] = dup(1);
	fd = redir(cmd_line);
	ret = 0;
	if (ft_strncmp(split_cmd[0], "echo", 5) == 0)
		ft_echo(split_cmd);
	else if (ft_strncmp(split_cmd[0], "export", 7) == 0)
		ret = ft_export(split_cmd);
	else if (ft_strncmp(split_cmd[0], "unset", 6) == 0)
		ft_unset(split_cmd);
	else if (ft_strncmp(split_cmd[0], "cd", 3) == 0)
		ret = ft_cd(split_cmd);
	else if (ft_strncmp(split_cmd[0], "./", 2) == 0)
	{
		if (fork() == 0)
			if (execve(&(split_cmd[0][2]), split_cmd, g_envv) == -1)
			{
				ft_error("Minishell", split_cmd[0], 2);
				exit(0);
			}
		wait(0);
	}
	else if (ft_path(split_cmd, path) == -2)
		return (ft_error("Minishell" , "", -100));
		
	dup2(savefd[0], 0);
	dup2(savefd[1], 1);
	if (ret != -1)
		exit_status = 0;
	if (fd != 0)
		close(fd);
	return(0);
}

int		search_function(char *cmd_line, char **path)
{
	char **split_cmd;
	int	savefd[2];
	// int	fd;

	savefd[0] = dup(0);
	savefd[1] = dup(1);
	split_cmd = ft_split_redir(cmd_line);
	ft_cmd_to_lower(&split_cmd[0]);
	if (ft_strncmp(split_cmd[0], "exit", 4) == 0 && cmpt_pipe(cmd_line) == 0)
	{
		write(1, "exit\n", 5);
		exit(0);
	}
	
	exec_cmd(cmd_line, split_cmd, path);

	// fd = redir(cmd_line);
	// if (ft_path(split_cmd, path) == -1)
	// 	return (ft_error(5));
	// dup2(savefd[0], 0);
	// dup2(savefd[1], 1);
	// if (fd != 0)
	// 	close(fd);
	return (0);
}

// int		search_function(char *cmd_line, char **path)
// {
// 	int	i;
// 	char **split_cmd;
// 	int	savefd[2];
// 	int	fd;

// 	savefd[0] = dup(0);
// 	savefd[1] = dup(1);
// 	i = 0;
// 	split_cmd = ft_split_redir(cmd_line);


// 	if (ft_strncmp(split_cmd[0], "exit", 4) == 0 && cmpt_pipe(cmd_line) == 0)
// 	{
// 		write(1, "exit\n", 5);
// 		exit(0);
// 	}
// 	fd = redir(cmd_line);
// 	if (ft_path(split_cmd, path) == -1)
// 		return (ft_error(5));
// 	dup2(savefd[0], 0);
// 	dup2(savefd[1], 1);
// 	if (fd != 0)
// 		close(fd);
// 	return (0);
// }

static void	exec_command(char *cmd, int in, int out, char **path)
{
	int i;

	i = 0;
	while (cmd[i] && !ft_strchr("<>", cmd[i]))
		i++;
	if (cmd[i])
		search_function(cmd, path);
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
	char **split_cmd;
	i = 0;
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
		split_cmd = ft_split_redir(&cmd[i]);
		ft_cmd_to_lower(&split_cmd[0]);
		if (ft_strncmp(split_cmd[0], "exit", 5) == 0)
		{
			while (cmd[i] != '|' && cmd[i] != '\0')
				i++;
			ft_freestrarr(split_cmd);
			continue ;
		}
		ft_freestrarr(split_cmd);
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

int		start_minishell()
{
	int		i;
	int		j;
	int		nb_pipe;
	char	**path;

	t.ret_gnl = 1;
	t.check_exit = 0;
	nb_pipe = 0;
	flag_prompt = 1;
	path = NULL;
	while (t.ret_gnl == 1 && t.check_exit == 0)
	{
		ctrl_backslash = 0;
		path = init_path(path);
		if (flag_prompt == 1)
			display_prompt();
		if (!get_next_line(0, &t.cmd_line))
		{
			ft_putstr_fd("exit\n", 1);
			exit(56);
		}
		flag_prompt = 1;
		if (t.cmd_line[0] == '\0')
			continue ;
		if (t.cmd_line != NULL && (t.cmd_line = ft_parsing(t.cmd_line)) != NULL)
		{
			if ((t.tab_cmd_line = ft_split_semicolon(t.cmd_line, ';')) != NULL)
			{
				i = 0;
				while (t.tab_cmd_line[i] != NULL)
				{
					nb_pipe = cmpt_pipe(t.tab_cmd_line[i]);
					j = 0;
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
	ft_freestrarr(path);
	return (0);
}

void	handle_sigint(int sig)
{
	flag_prompt = 0;
	if (sig == SIGINT)
	{
		ft_putstr_fd("\b\b  \n", 1);
		signal(SIGINT, handle_sigint);
		display_prompt();
	}
}

void	handle_sigquit(int sig)
{
	if (sig == SIGQUIT && ctrl_backslash != 0)
	{
		flag_prompt = 0;
		signal(SIGQUIT, handle_sigquit);
		ft_putstr_fd("Quit: 3\n", 1);
		display_prompt();
	}
	else
		ft_putstr_fd("\b\b  \b\b", 1);
}

int		main(int ac, char **av, char **env)
{
	(void)av;
	if (ac != 1)
		return (0);
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT,handle_sigquit);
	if (init_g_envv(env) == -1)
		return (-1);
	if (start_minishell() == -1)
		return (-1);
	return (0);
}
