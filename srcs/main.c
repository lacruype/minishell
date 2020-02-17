
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
		return ; //ERROR
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

int		search_function(char *cmd_line, char **path, int *pip)
{
	int i;

	i = (ft_jump_space(cmd_line) - cmd_line);
	if (ft_strncmp((const char*)&cmd_line[i], "exit", 4) == 0 && ft_strchr(" ;",cmd_line[4]))
		return (-1);
	else if(ft_path(cmd_line, path, pip) == -1)
		return (-1);
	return (0);
}

int		start_minishell(char **path, int *pip)
{
	int		i;
	int		ret;
	int		check_exit;
	char	*cmd_line;
	char	**tab_cmd_line;
	int		child_status;
	pid_t	pid;

	ret = 1;
	check_exit = 0;
	while (ret == 1 && check_exit == 0)
	{
		display_prompt();
		ret = get_next_line(0, &cmd_line);

		if (cmd_line != NULL)
		{
			ft_parsing(&cmd_line);
			if (cmd_line)
			{
				if ((tab_cmd_line = ft_split_semicolon(cmd_line, ';')) != NULL)
				{
					i = 0;
					while (tab_cmd_line[i] != NULL)
					{
						if ((pid = fork()) == 0)
						{
							if (search_function(tab_cmd_line[i], path, pip) == -1)
								exit(17);
						}
						waitpid(pid, &child_status, 0);
						ft_update_g_envv(child_status);
						if ((WEXITSTATUS(child_status)) == 17)
							check_exit = 1;
						
						i++;
					}
					ft_freestrarr(tab_cmd_line);
				}
			}
			free(cmd_line);
		}
	}	
	if (ret == 0)
		ft_putstr_fd("\nexit\n", 1);
	else if (check_exit == 1)
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