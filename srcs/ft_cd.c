/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lacruype <lacruype@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 14:05:05 by rledrin           #+#    #+#             */
/*   Updated: 2020/02/17 10:38:31 by lacruype         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		ft_cd(char *cmd)
{
	int		i;
	DIR		*pDir;
	char	*loc;
	int		j;
	int		k;
	int		locsize;

	loc = ft_strdup("");
	i = 0;
	locsize = 0;
	j = 0;
	k = 0;
	k = ft_jump_space(&cmd[i]) - cmd;
	k = ft_jump_space(&cmd[i + 2]) - cmd;

	while (ft_strncmp(g_envv[i], "PWD=", 4) != 0)
		i++;
	while (ft_strncmp(g_envv[j], "OLDPWD=", 7) != 0)
		j++;
	g_envv[j] = ft_realloc(g_envv[j], ft_strlen(g_envv[i]) + 3)
	g_envv[j] = ft_memcpy(g_envv[j], "OLDPWD=", 7);
	g_envv[j] = ft_memcpy(g_envv[j], &g_envv[i][4], ft_strlen(&g_envv[i][4]));

	if ((locsize = quote(&cmd[i])) > 0)
		loc = ft_substr(cmd, i + 1, locsize - 2);
	else
	{
		while(cmd[i] && !ft_strchr("|<>", cmd[i]))
		{
			loc = ft_realloc(loc, sizeof(char) * (j + 2));
			loc[j] = cmd[i];
			loc[j + 1] = '\0';
			j++;
			i++;
		}
	}
	
	pDir = opendir(loc);
	if (!pDir)
	{
		; //ERROR
		return (-1);
	}
	closedir(pDir);
	k = ft_jump_space(&cmd[i]);
	if (cmd[i] == '>')
	{
		//fonction redirection
	}


	free(filename);

	

}
