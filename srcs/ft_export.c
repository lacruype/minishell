/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lacruype <lacruype@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 13:54:43 by rledrin           #+#    #+#             */
/*   Updated: 2020/07/03 13:31:49 by lacruype         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	void	ft_export_only(void)
{
	int i;
	int j;

	i = -1;
	while (g_envv[++i])
	{
		j = 0;
		ft_putstr_fd("declare -x ", 1);
		while (g_envv[i][j])
		{
			(j > 0 && g_envv[i][j - 1] == '=') ? f('"') : write(1, "", 0);
			ft_putchar_fd(g_envv[i][j++], 1);
		}
		(g_envv[i][j - 1] == '=') ? ft_putchar_fd('"', 1) : write(1, "", 0);
		ft_putstr_fd("\"\n", 1);
	}
	i = -1;
	while (g_var[++i])
	{
		j = 0;
		ft_putstr_fd("declare -x ", 1);
		while (g_var[i][j] != '\0')
			ft_putchar_fd(g_var[i][j++], 1);
		write(1, "\n", 2);
	}
}

static	void	ft_add_var(int equal, char *var)
{
	int		tmp;

	if (equal)
	{
		g_envv = ft_realloc(g_envv, (get_size_env(g_envv) + 2) * sizeof(char*));
		g_envv[get_size_env(g_envv) + 1] = NULL;
		g_envv[get_size_env(g_envv)] = ft_strdup(var);
	}
	else
	{
		tmp = get_size_env(g_var);
		if (tmp == 0)
		{
			g_var = ft_realloc(g_var, (tmp + 2) * sizeof(char*));
			g_var[1] = NULL;
			g_var[0] = ft_strdup(var);
		}
		else
		{
			tmp++;
			g_var = ft_realloc(g_var, (tmp + 1) * sizeof(char*));
			g_var[tmp] = NULL;
			g_var[tmp - 1] = ft_strdup(var);
		}
	}
}

static	int		ft_check_var_exist02(char *args, int e)
{
	int i;

	i = 0;
	while (g_envv[i])
	{
		if (!ft_strncmp(args, g_envv[i], e - 1) && g_envv[i][e - 1] == '=')
		{
			g_envv = ft_delete_env(g_envv, i);
			return (0);
		}
		i++;
	}
	i = 0;
	while (g_var[i])
	{
		if (!ft_strncmp(args, g_var[i], e - 1))
		{
			g_var = ft_delete_env(g_var, i);
			return (0);
		}
		i++;
	}
	return (0);
}

/*
** e = equal ⬇️
*/

static	int		ft_check_var_exist01(char *args, int e)
{
	int	i;

	i = 0;
	if (e)
		return (ft_check_var_exist02(args, e));
	else
	{
		while (g_var[i])
		{
			if (!ft_strncmp(args, g_var[i],
				ft_strlen(args)) && g_var[i][ft_strlen(args)] == '\0')
				return (-1);
			i++;
		}
		i = 0;
		while (g_envv[i])
		{
			if (!ft_strncmp(args, g_envv[i], ft_strlen(args)))
				return (-1);
			i++;
		}
	}
	return (0);
}

int				ft_export(char **args)
{
	int all[4];

	all[0] = 0;
	all[3] = 0;
	if (!args[1])
		ft_export_only();
	else
	{
		while (args[++all[0]])
		{
			if (ft_check_var_name(args[all[0]]) == -1)
			{
				all[3] = ft_error("Minishell", args[all[0]], -2);
				continue ;
			}
			all[2] = 0;
			all[1] = 0;
			while (args[all[0]][all[1]])
				if (args[all[0]][all[1]++] == '=')
					all[2] = all[1];
			if (ft_check_var_exist01(args[all[0]], all[2]) != -1)
				ft_add_var(all[2], args[all[0]]);
		}
	}
	return (all[3]);
}
