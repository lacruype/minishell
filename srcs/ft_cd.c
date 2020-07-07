/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lacruype <lacruype@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 16:17:02 by lacruype          #+#    #+#             */
/*   Updated: 2020/07/02 15:03:54 by lacruype         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// char	**g_envv;

// static int	ft_set_pwd2(int pwd_indc, int *i, int *j, char **path)
// {
// 	char	*tmp;

// 	(*i) = ft_strlen(g_envv[pwd_indc]);
// 	if (!ft_strncmp(&(*path)[*j], ".", 2))
// 		return (0);
// 	else if (!ft_strncmp(&(*path)[*j], "./", 2))
// 	{
// 		(*j) += 2;
// 		return (1);
// 	}
// 	else if (!ft_strncmp(&(*path)[*j], "..", 2))
// 	{
// 		while (--(*i) > 3 && g_envv[pwd_indc][*i] != '/')
// 			;
// 		tmp = ft_substr(g_envv[pwd_indc], 0, *i);
// 		free(g_envv[pwd_indc]);
// 		g_envv[pwd_indc] = tmp;
// 		*j += 2;
// 		if ((*path)[*j] == '/')
// 			(*j)++;
// 		return (1);
// 	}
// 	return (0);
// }

// static void	ft_set_pwd3(int pwd_indc, int *i, int *j, char **path)
// {
// 	*i = ft_strlen(g_envv[pwd_indc]);
// 	g_envv[pwd_indc] = ft_realloc(g_envv[pwd_indc], (*i) + 2);
// 	g_envv[pwd_indc][(*i)++] = '/';
// 	if ((*path)[(*j)] == '/')
// 		(*j)++;
// 	while ((*path)[(*j)] && (*path)[(*j)] != '/')
// 	{
// 		g_envv[pwd_indc] = ft_realloc(g_envv[pwd_indc], (*i) + 2);
// 		g_envv[pwd_indc][(*i)] = (*path)[(*j)];
// 		(*j)++;
// 		(*i)++;
// 	}
// 	g_envv[pwd_indc][(*i)] = '\0';
// }

// void		ft_set_pwd(char *path, int pwd_indc, int oldpwd_indc)
// {
// 	char	*tmp;
// 	int		i;
// 	int		j;

// 	j = 0;
// 	tmp = ft_substr(g_envv[pwd_indc], 4, ft_strlen(g_envv[pwd_indc]) - 4);
// 	printf("TMP = [%s]\n", tmp);
// 	if (oldpwd_indc != -1)
// 		free(g_envv[oldpwd_indc]);
// 	if (oldpwd_indc != -1)
// 		g_envv[oldpwd_indc] = ft_strjoin("OLDPWD=", tmp);
// 	free(tmp);
// 	tmp = NULL;
// 	if (path[0] == '/')
// 		free(g_envv[pwd_indc]);
// 	if (path[0] == '/')
// 		g_envv[pwd_indc] = ft_strdup("PWD=");
// 	while (path[j])
// 	{
// 		if (ft_set_pwd2(pwd_indc, &i, &j, &path))
// 			continue ;
// 		ft_set_pwd3(pwd_indc, &i, &j, &path);
// 		if (!path[j])
// 			break ;
// 		j++;
// 	}
// }

// int				ft_init_g_envv(char **env)
// {
// 	int i;

// 	i = -1;
// 	if (!(g_envv = malloc(sizeof(char*) * (get_size_env(env) + 1))))
// 		return (-1);
// 	while (env[++i])
// 		g_envv[i] = ft_strdup((const char *)env[i]);
// 	g_envv[i] = NULL;
// 	if (!(g_var = calloc(1, sizeof(char*))))
// 		return (0);
// 	return (0);
// }



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
	free(dir);
	return (0);
}

static int	ft_cd3(char ***args, int *i, char **path)
{
	int	tmp;

	tmp = 0;
	*path = ft_strdup("");
	if ((*args)[1])
		*i = (ft_jump_space(&(**args)[1]) - &(**args)[1]);
	else
	{
		*i = 0;
		free(*path);
		if (!ft_find_env(&tmp, "HOME="))
			return (ft_error("Minishell", "cd", -3));
		*path = ft_strdup(&g_envv[tmp][5]);
	}
	return (tmp);
}

int			ft_cd(char **args)
{
	int		i;
	int		env[3];
	char	*path;

	if (ft_cd3(&args, &i, &path) == -1)
		return (-1);
	while (args[1] && args[1][i])
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
		free(path);
	}
	return (0);
}

// int main(int ac, char **av, char ** env)
// {
// 	ft_init_g_envv(env);

// 	ft_cd(ft_split("cd", ' '));
// 	return (0);
// }
