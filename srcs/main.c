/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lacruype <lacruype@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 11:14:32 by rledrin           #+#    #+#             */
/*   Updated: 2020/02/10 15:50:20 by lacruype         ###   ########.fr       */
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
			path = ft_split((const char*)g_envv[i], ':');
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

	(void)path;
	i = (ft_jump_space(cmd_line) - cmd_line);
	if (ft_strncmp((const char*)&cmd_line[i], "exit", 4) == 0)
		return (-1);
	return (0);
}

int		start_minishell(char **path)
{
	int		i;
	int		ret;
	int		check_exit;
	char	*cmd_line;

	ret = 1;
	check_exit = 0;
	while (ret == 1 && check_exit == 0)
	{
		i = 0;
		display_prompt();
		ret = get_next_line(0, &cmd_line);
		if (cmd_line != NULL)
			if (search_function(cmd_line, path) == -1)
				check_exit = 1;
		free(cmd_line);
	}
	if (check_exit == 1)
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
