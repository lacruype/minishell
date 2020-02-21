
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
	ft_putstr_fd(" ➡ ", 0);
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

int		start_minishell(char **path, int *pip)
{
	int		i;
	int		j;
	int		k;
	var_minishell t;

	t.ret_gnl = 1;
	t.check_exit = 0;
	while (t.ret_gnl == 1 && t.check_exit == 0)
	{
		display_prompt();
		t.ret_gnl = get_next_line(0, &t.cmd_line);
		if (t.cmd_line != NULL && (t.cmd_line = ft_parsing(t.cmd_line)) != NULL)
		{
			if (t.cmd_line)
			{
				if ((t.tab_cmd_line = ft_split_semicolon(t.cmd_line, ';')) != NULL)
				{
					i = 0;
					while (t.tab_cmd_line[i] != NULL)
					{
						j = 0;
						//printf ("char = %c",t.tab_cmd_line[i][j]);
						while (t.tab_cmd_line[i][j])
						{
							k = 0;
							while (t.tab_cmd_line[i][j + k] && t.tab_cmd_line[i][j + k] != '|')
							{
								//printf ("K = %d char = %c", k, t.tab_cmd_line[i][j + k]);
								k++;
							}
							if ((t.pid = fork()) == 0)
							{
								if (t.tab_cmd_line[i][j] == '|')
								{
									//write(1, "first TEST\n", 5);
									dup2(pip[0], 0);
									j++;
									//printf ("char = %c\n",t.tab_cmd_line[i][j]);
								}
								else
									close(pip[0]);
								if (t.tab_cmd_line[i][j + k] == '|')
								{
									//write(1, "second TEST\n", 5);
									dup2(pip[1], 1);
								}
								else
									close(pip[1]);
								if ((t.ret_sf = search_function(&t.tab_cmd_line[i][j], path)) == 1)
									exit(17);
								else if (t.ret_sf == -1)
									exit(18);
								
							}
							waitpid(t.pid, &t.child_status, 0);
							ft_update_g_envv(t.child_status);
							if ((WEXITSTATUS(t.child_status)) == 17)
							{
								t.check_exit = 1;
								break ;
							}
							j += k;
						}
						i++;
					}
					ft_freestrarr(t.tab_cmd_line);
				}
			}
			free(t.cmd_line);
		}
	}	
	if (t.ret_gnl == 0)
		ft_putstr_fd("\nexit\n", 1);
	else if (t.check_exit == 1)
		ft_putstr_fd("exit\n", 1);
	return (0);
}

void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		display_prompt();
		signal(SIGINT, handle_sigint);
	}
}

int		main(int ac, char **av, char **env)
{
	(void)av;
	char	**path;
	int		pip[2];

	if (pipe(pip) == -1|| ac != 1)
		return (0);
	signal(SIGINT, handle_sigint);
	if (init_g_envv(env) == -1)
		return (-1);
	path = init_path();

	if (start_minishell(path, pip) == -1)
		return (-1);
	ft_freestrarr(path);
	return (0);
}