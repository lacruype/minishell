/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lacruype <lacruype@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 11:14:32 by rledrin           #+#    #+#             */
/*   Updated: 2020/02/06 18:18:58 by lacruype         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		search_function(char **cmd_line_split, char **env)
{
	int i;
	char **path;

	i = 0;
	if (ft_strncmp((const char*)cmd_line_split[0], "exit",
		ft_strlen((const char*)cmd_line_split[0])) == 0)
			return (-1);
	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp((const char*)env[i], "PATH", 4) == 0)
			path = ft_split((const char*)env[i], ':');
		i++;
	}
	i = 0;
	while (path[i] != NULL)
	{
		printf("PATH %d = %s\n", i, path[i]);
		i++;
	}
	return (0);
}

int		start_minishell(char **env)
{
	int		i;
	int		ret;
	int		check_exit;
	char	*cmd_line;
	char	**cmd_line_split;

	(void)env;
	ret = 1;
	check_exit = 0;
	while (ret == 1 && check_exit == 0)
	{
		i = 0;
		ft_putstr_fd("Minishell ➡ ", 0);
		ret = get_next_line(0, &cmd_line);
		cmd_line_split = ft_split(cmd_line, ' ');
		if (search_function(cmd_line_split, env) == -1)
			check_exit = 1;
		while (cmd_line_split[i] != NULL)
			free(cmd_line_split[i++]);
		free(cmd_line_split);
		free(cmd_line);
	}
	return (0);
}

int		main(int ac, char **av, char **env)
{
	(void)av;
	if (ac != 1)
		return (0);
	if (start_minishell(env) == 0)
		return (0);
	return (-1);
}
