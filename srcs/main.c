
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
	char *buf;

	buf = NULL;
	if ((buf = getcwd(buf, 255)) == NULL)
		return ;
	//MESSAGE DERREUR NOM TROP LONG
	ft_putstr_fd(buf, 0);
	ft_putstr_fd(" ➡ ", 0);
	free(buf);
}

int		search_function(char *cmd_line, char **path)
{
	int i;

	i = (ft_jump_space(cmd_line) - cmd_line);
	if (ft_strncmp((const char*)&cmd_line[i], "exit", 4) == 0 && ft_strchr(" ;",cmd_line[4]))
		return (-1);
	else if(ft_path(cmd_line, path) == -1)
		return (-1);
	return (0);
}

int		start_minishell(char **path)
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
							if (search_function(tab_cmd_line[i], path) == -1)
								exit(17);
						}
						waitpid(pid, &child_status, 0);
						if ((WEXITSTATUS(child_status)) == 17)
						{
							check_exit = 1;
							printf("%d\n", WEXITSTATUS(child_status));
						}
						i++;
					}
					ft_freestrarr(tab_cmd_line);
				}
			}
			free(cmd_line);
		}
	}
	if (check_exit)
		ft_putstr_fd("exit\n", 1);
	return (0);
}

int		main(int ac, char **av, char **env)
{
	(void)av;
	char **path;
	if (ac != 1)
		return (0);
	if (init_g_envv(env) == -1)
		return (-1);
	path = init_path();
	if (start_minishell(path) == -1)
		return (-1);
	ft_freestrarr(path);
	return (0);
}