/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd02.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lacruype <lacruype@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 13:44:40 by lacruype          #+#    #+#             */
/*   Updated: 2020/07/01 13:45:21 by lacruype         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_set_pwd2(int pwd_indc, int *i, int *j, char **path)
{
	char	*tmp;

	(*i) = ft_strlen(g_envv[pwd_indc]);
	if (!ft_strncmp(&(*path)[*j], ".", 2))
		return (0);
	else if (!ft_strncmp(&(*path)[*j], "./", 2))
	{
		(*j) += 2;
		return (1);
	}
	else if (!ft_strncmp(&(*path)[*j], "..", 2))
	{
		while (--(*i) > 3 && g_envv[pwd_indc][*i] != '/')
			;
		tmp = ft_substr(g_envv[pwd_indc], 0, *i);
		free(g_envv[pwd_indc]);
		g_envv[pwd_indc] = tmp;
		*j += 2;
		if ((*path)[*j] == '/')
			(*j)++;
		return (1);
	}
	return (0);
}

static void	ft_set_pwd3(int pwd_indc, int *i, int *j, char **path)
{
	*i = ft_strlen(g_envv[pwd_indc]);
	g_envv[pwd_indc] = ft_realloc(g_envv[pwd_indc], (*i) + 2);
	g_envv[pwd_indc][(*i)++] = '/';
	if ((*path)[(*j)] == '/')
		(*j)++;
	while ((*path)[(*j)] && (*path)[(*j)] != '/')
	{
		g_envv[pwd_indc] = ft_realloc(g_envv[pwd_indc], (*i) + 2);
		g_envv[pwd_indc][(*i)] = (*path)[(*j)];
		(*j)++;
		(*i)++;
	}
	g_envv[pwd_indc][(*i)] = '\0';
}

void		ft_set_pwd(char *path, int pwd_indc, int oldpwd_indc)
{
	char	*tmp;
	int		i;
	int		j;

	j = 0;
	tmp = ft_substr(g_envv[pwd_indc], 4, ft_strlen(g_envv[pwd_indc]) - 4);
	if (oldpwd_indc != -1)
		free(g_envv[oldpwd_indc]);
	if (oldpwd_indc != -1)
		g_envv[oldpwd_indc] = ft_strjoin("OLDPWD=", tmp);
	free(tmp);
	if (path[0] == '/')
		free(g_envv[pwd_indc]);
	if (path[0] == '/')
		g_envv[pwd_indc] = ft_strdup("PWD=");
	while (path[j])
	{
		if (ft_set_pwd2(pwd_indc, &i, &j, &path))
			continue ;
		ft_set_pwd3(pwd_indc, &i, &j, &path);
		if (!path[j])
			break ;
		j++;
	}
}
