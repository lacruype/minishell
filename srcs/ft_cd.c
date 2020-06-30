/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lacruype <lacruype@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 16:17:02 by lacruype          #+#    #+#             */
/*   Updated: 2020/06/30 15:10:57 by lacruype         ###   ########.fr       */
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
			break;
	}
	*dir = ft_realloc(*dir, sizeof(char) * (i + 1));
	(*dir)[i] = '\0';
}

static void	ft_set_pwd(char *path, int pwd_indc, int oldpwd_indc)
{
	char	*tmp;
	int		i;
	int		j;

	j = 0;
	printf("Groueorg = %d\n", oldpwd_indc);
	tmp = ft_substr(g_envv[pwd_indc], 4, ft_strlen(g_envv[pwd_indc]) - 4);
	if (oldpwd_indc != -1)
		g_envv[oldpwd_indc] = ft_strjoin("OLDPWD=", tmp);
	if (path[0] == '/')
		g_envv[pwd_indc] = ft_strdup("PWD=");
	else
		g_envv[pwd_indc] = ft_strdup(g_envv[pwd_indc]);
	while (path[j])
	{
		i = ft_strlen(g_envv[pwd_indc]);
		if (!ft_strncmp(&path[j], ".", 2))
			return ;
		else if (!ft_strncmp(&path[j], "./", 2))
		{
			j += 2;
			continue;
		}
		else if (!ft_strncmp(&path[j], "..", 2))
		{
			while (--i > 3 && g_envv[pwd_indc][i] != '/')
				;
			tmp = ft_substr(g_envv[pwd_indc], 0, i);
			free(g_envv[pwd_indc]);
			g_envv[pwd_indc] = tmp;
			j += 2;
			if(path[j] == '/')
				j++;
			continue;
		}
		i = ft_strlen(g_envv[pwd_indc]);
		g_envv[pwd_indc] = ft_realloc(g_envv[pwd_indc], i + 2);
		g_envv[pwd_indc][i++] = '/';
		if(path[j] == '/')
				j++;
		while (path[j] && path[j] != '/')
		{
			g_envv[pwd_indc] = ft_realloc(g_envv[pwd_indc], i + 2);
			g_envv[pwd_indc][i] = path[j];
			j++;
			i++;
		}
		g_envv[pwd_indc][i] = '\0'; 
		if (!path[j])
			break;
		j++;
	}
}

void		ft_cd(char **args)
{
	int		i;
	int		env[3];
	char	*dir;
	char	*path;
	char	*tmp;
	DIR		*d;

	tmp = 0;
	dir = ft_strdup("");
	path = ft_strdup("");
	if (args[1])
		i = ft_jump_space(args[1]) - args[1];
	else
	{
		i = 0;
		if (!ft_find_env(&env[0], "HOME="))
			return ((void)ft_error("Minishell", "cd", -3));
		args[1] = ft_strdup(&g_envv[env[0]][5]);
	}
	while (args[1][i])
	{
		ft_get_dir(&dir, &args[1][i]);
		if (*dir)
		{
			if ((d = opendir((tmp = ft_strjoin(path, dir)))))
			{
				closedir(d);
				free(path);
				path = tmp;
				tmp = 0;
			}
			else
			{
				free(tmp);
				free(path);
				free(dir);
				tmp = 0;
				ft_error("Minishell", "cd", 2);
				return ;
			}
		}
		if (args[1][i] == '/')
			i++;
		while (args[1][i] && args[1][i] != '/')
			i++;
	}
	if (*path)
	{
		if (ft_find_env(&env[1], "PWD="))
		{
			ft_find_env(&env[2], "OLDPWD=");
			ft_set_pwd(path, env[1], env[2]);
		}
		chdir(path);
	}
}
