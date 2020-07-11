/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lacruype <lacruype@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 15:02:35 by lacruype          #+#    #+#             */
/*   Updated: 2020/07/03 14:23:15 by lacruype         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int				get_size_env(char **env)
{
	int i;

	i = -1;
	while (env[++i] != NULL)
		;
	return (i);
}

int				init_g_envv(char **env)
{
	int i;

	i = -1;
	if (!(g_envv = malloc(sizeof(char*) * (get_size_env(env) + 1))))
		return (-1);
	while (env[++i])
		g_envv[i] = ft_strdup((const char *)env[i]);
	g_envv[i] = NULL;
	if (!(g_var = calloc(1, sizeof(char*))))
		return (0);
	return (0);
}

static	void	ft_print_env(void)
{
	int i;

	i = 0;
	while (g_envv[i] != NULL)
	{
		ft_putstr_fd(g_envv[i], 1);
		ft_putchar_fd('\n', 1);
		i++;
	}
}

int			ft_env(char **args)
{
	int	i;
	int j;

	i = 1;
	while (args[i] != NULL)
	{
		j = 0;
		while (args[i][j] != '=' && args[i][j])
			j++;
		if (args[i][j] != '=')
			return (ft_error("env", args[i], 2));
		i++;
	}
	ft_print_env();
	i = 1;
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		write(1, "\n", 1);
		i++;
	}
	return (0);
}

int				ft_right(char *path, char mod)
{
	struct stat buf;
	int ret = 0;

	ret = stat(path, &buf);
	if (ret == -1)
		return (2);
	if (mod == 'r' && buf.st_mode & S_IRUSR)
		return (1);
	else if (mod == 'x' && buf.st_mode & S_IXUSR)
		return (1);
	return (13);
}
