/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lacruype <lacruype@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 13:54:43 by rledrin           #+#    #+#             */
/*   Updated: 2020/07/01 16:52:50 by lacruype         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_check_var_name(char *arg)
{
	int i;

	i = 0;
	if (ft_isdigit(arg[0]))
		return (-1);
	while (arg[i] && arg[i] != '=')
	{
		if (arg[i] == '\'' || arg[i] == '\\' || arg[i] == '"' || arg[i] == '-')
			return (-1);
		i++;
	}
	return (0);
}

static void	ft_print_env(void)
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
			(j > 0 && g_envv[i][j - 1] == '=') ? ft_putchar_fd('"', 1) : write(1, "", 0);
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

static void	ft_add_var(int equal, char *var)
{
	int		tmp;

	if (equal)
	{
		tmp = get_size_env(g_envv);
		g_envv = ft_realloc(g_envv, (tmp + 2) * sizeof(char*));
		g_envv[tmp + 1] = NULL;
		g_envv[tmp] = ft_strdup(var);
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
			g_var = ft_realloc(g_var, (tmp + 1) * sizeof(char*));
			g_var[tmp] = NULL;
			g_var[tmp - 1] = ft_strdup(var);
		}
	}
}

static int	ft_check_var_exist(char *args, int equal)
{
	int	i;

	i = 0;
	if (equal)
	{
		while (g_envv[i])
		{
			if (!ft_strncmp(args, g_envv[i], equal - 1))
			{
				g_envv = ft_delete_env(g_envv, i);
				return (0);
			}
			i++;
		}
		i = 0;
		while (g_var[i])
		{
				printf("TEST = [%s] equal = [%d]\n", g_var[i], equal);

			if (!ft_strncmp(args, g_var[i], equal - 1))
			{
				g_var = ft_delete_env(g_var, i);
				return (0);
			}
			i++;
		}
	}
	else
	{
		while(g_var[i])
		{
			if (!ft_strncmp(args, g_var[i], ft_strlen(args)))
				return(-1);
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

int			ft_export(char **args)
{
	int all[4];

	all[0] = 0;
	all[3] = 0;
	if (!args[1])
		ft_print_env();
	else
	{
		while (args[++all[0]])
		{
			if (ft_check_var_name(args[all[0]]) == -1)
			{
				all[3] = ft_error("Minishell", args[all[0]++], -2);
				continue ;
			}
			all[2] = 0;
			all[1] = 0;
			while (args[all[0]][all[1]])
				if (args[all[0]][all[1]++] == '=')
					all[2] = all[1];
			if (ft_check_var_exist(args[all[0]], all[2]) != -1)
				ft_add_var(all[2], args[all[0]]);
		}
	}
	return (all[3]);
}
