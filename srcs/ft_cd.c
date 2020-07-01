/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lacruype <lacruype@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 16:17:02 by lacruype          #+#    #+#             */
/*   Updated: 2020/07/01 13:48:15 by lacruype         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_find_env(int *i, char *elem)
{
	ssize_t	len;

	*i = 0;
	len = ft_strlen(elem);
	while (g_envv[(*i)])
	{
		if (!ft_strncmp(g_envv[*i], elem, len))
			return (1);
		(*i)++;
	}
	*i = -1;
	return (0);
}

static void	ft_get_dir(char **dir, char *args)
{
	int		i;

	i = 0;
	free(*dir);
	*dir = ft_strdup("");
	while (args[i])
	{
		*dir = ft_realloc(*dir, sizeof(char) * (i + 1));
		(*dir)[i] = args[i];
		i++;
		if (args[i] == '/')
			break ;
	}
	*dir = ft_realloc(*dir, sizeof(char) * (i + 1));
	(*dir)[i] = '\0';
}

static int	ft_cd2(char **args, int i, char **path)
{
	char	*tmp;
	char	*dir;
	DIR		*d;

	tmp = 0;
	dir = ft_strdup("");
	ft_get_dir(&dir, &args[1][i]);
	if (*dir)
	{
		tmp = ft_strjoin(*path, dir);
		if ((d = opendir(tmp)))
		{
			closedir(d);
			free(*path);
			*path = tmp;
		}
		else
		{
			free(tmp);
			free(*path);
			free(dir);
			return (ft_error("Minishell", "cd", 2));
		}
	}
	return (0);
}

static int	ft_cd3(char ***args, int *i, char **path)
{
	int	tmp;

	*path = ft_strdup("");
	tmp = 0;
	if ((*args)[1])
		*i = (ft_jump_space(&(**args)[1]) - &(**args)[1]);
	else
	{
		*i = 0;
		if (!ft_find_env(&tmp, "HOME="))
			return (ft_error("Minishell", "cd", -3));
		(*args)[1] = ft_strdup(&g_envv[tmp][5]);
	}
	return (tmp);
}

int		ft_cd(char **args)
{
	int		i;
	int		env[3];
	char	*path;

	if (ft_cd3(&args, &i, &path) == -1)
		return (-1);
	while (args[1][i])
	{
		if (ft_cd2(args, i, &path) == -1)
			return (-1);
		if (args[1][i] == '/')
			i++;
		while (args[1][i] && args[1][i] != '/')
			i++;
	}
	if (*path)
	{
		if (ft_find_env(&env[1], "PWD="))
			ft_find_env(&env[2], "OLDPWD=");
		if (ft_find_env(&env[1], "PWD="))
			ft_set_pwd(path, env[1], env[2]);
		chdir(path);
	}
	return (0);
}
