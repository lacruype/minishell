
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
int flag = 0;

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
		return (1);
	if (ft_path(split_cmd, path) == -1)
		return (ft_error(5));
	return (0);
}

int		start_minishell(char **path)
{
	int		i;
	int		j;
	int		k;
	int		pip[2];

	t.ret_gnl = 1;
	t.check_exit = 0;

	if (pipe(pip) == -1)
		return (0);
	while (t.ret_gnl == 1 && t.check_exit == 0)
	{
		if ((WEXITSTATUS(t.child_status)) == 56)
			exit(0);
		if (flag != 1)
			display_prompt();
		flag = 0;
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
					j = 0;
					while (t.tab_cmd_line[i][j])
					{
						k = 0;
						if (t.tab_cmd_line[i][j] == '|')
							j++;
						while (t.tab_cmd_line[i][j + k] && t.tab_cmd_line[i][j + k] != '|')
							k++;
						if ((pid = fork()) == 0)
						{
							if (j > 0 && t.tab_cmd_line[i][j - 1] == '|')
							{
								dup2(pip[0], 0);
								//char te = -12;
								//write(pip[1], "FIN", 3);
								// write(pip[1], "\0", 1);
								//printf("J = %d char = [%c]\n", j, t.tab_cmd_line[i][j]);
								//close(pip[0]);
							}
							else
								close(pip[0]);
							//ft_putstr_fd("JE TEST A", 1);
							if (t.tab_cmd_line[i][j + k] == '|')
							{
								dup2(pip[1], 1);
								//write (1, "QQQ", 3);
								//close(pip[1]);
							}
							else
								close(pip[1]);
							//dup2(open("Makefile", O_RDWR), 0);
							// (void)path;
							//ft_putstr_fd("JE TEST A", 1);
							if ((t.ret_sf = search_function(&t.tab_cmd_line[i][j], path)) == 1)
								exit(17);
							else if (t.ret_sf == -1)
								exit(18);
							//ft_putstr_fd("TESTEST\n", 1);
							// close(pip[0]);
							// close(pip[1]);
							exit(0);
						}
						waitpid(t.pid, &t.child_status, 0);
						ft_update_g_envv(t.child_status);
						if ((WEXITSTATUS(t.child_status)) == 17)
						{
							ft_putstr_fd("exit\n", 1);
							exit(56);
						}
						close(pip[1]);
						dup2(pip[0], 0);
						execve("/bin/cat", ft_split("cat -e", ' '), NULL);
						close(pip[0]);
						//printf("J = %d K = %d char = %c\n", j, k, t.tab_cmd_line[i][j]);
						j += k;
					}
					i++;
				}
				ft_freestrarr(t.tab_cmd_line);
			}
			free(t.cmd_line);
		}
		waitpid(pid, &t.child_status, 0);
	}
	return (0);
}

void	handle_sigint(int sig)
{
	ft_putstr_fd("\b\b  \n", 1);
	signal(SIGINT, handle_sigint);
	display_prompt();
	flag = 1;
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
