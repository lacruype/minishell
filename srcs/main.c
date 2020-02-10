/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lacruype <lacruype@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 11:14:32 by rledrin           #+#    #+#             */
/*   Updated: 2020/02/10 14:54:02 by lacruype         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_is_space(char *str)
{
	int i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == ' ' && str[i + 1] == ' ')
		return (-1);
	}
	return (1);
}

void	ft_freestrarr(char **arr)
{
	int i;

	i = -1;
	if (!arr)
		return ;
	if (*arr)
	{
		while (arr[++i])
			free(arr[i]);
	}
	free(arr);
	arr = NULL;
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

int		get_size_env(char **env)
{
	int i;

	i = -1;
	while (env[++i])
		;
	return (i);
}

int		init_g_envv(char **env)
{
	int i;

	i = -1;
	if (!(g_envv = malloc(sizeof(char*) * (get_size_env(env) + 1))))
		return (-1);
	while (env[++i])
		g_envv[i] = ft_strdup((const char *)env[i]);
	g_envv[i] = NULL;
	return (0);
}

int		search_function(char **cmd_line_split)
{
	int i;
	char **path;

	i = 0;
	if (ft_strncmp((const char*)cmd_line_split[0], "exit",
		ft_strlen((const char*)cmd_line_split[0])) == 0)
			return (-1);
	i = 0;
	while (g_envv[i] != NULL)
	{
		if (ft_strncmp((const char*)g_envv[i], "PATH", 4) == 0)
			path = ft_split((const char*)g_envv[i], ':');
		i++;
	}
	i = 0;
	while (path[i] != NULL)
	{
		printf("PATH %d = %s\n", i, path[i]);
		i++;
	}
	ft_freestrarr(path);
	return (0);
}

int		start_minishell(void)
{
	int		i;
	int		ret;
	int		check_exit;
	char	*cmd_line;
	char	**cmd_line_split;

	ret = 1;
	check_exit = 0;
	while (ret == 1 && check_exit == 0)
	{
		i = 0;
		display_prompt();
		ret = get_next_line(0, &cmd_line);
		write(1, "HEY\n", 4);
		cmd_line_split = ft_split(cmd_line, ' ');
		write(1, "HOH\n", 4);
		if (cmd_line_split[0] != NULL)
			if (search_function(cmd_line_split) == -1)
				check_exit = 1;
		ft_freestrarr(cmd_line_split);
		free(cmd_line);

	}
	return (0);
}

int		main(int ac, char **av, char **env)
{
	(void)av;
	if (ac != 1)
		return (0);
	if (init_g_envv(env) == -1)
		return (-1);
	if (start_minishell() == -1)
		return (-1);
	//ft_freestrarr(g_envv);
	return (0);
}
