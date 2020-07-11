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

void		ft_set_pwd(char *path, int pwd_indc, int oldpwd_indc)
{
	char	*tmp;

	(void)path;
	tmp = ft_substr(g_envv[pwd_indc], 4, ft_strlen(g_envv[pwd_indc]) - 4);
	if (oldpwd_indc != -1)
		free(g_envv[oldpwd_indc]);
	if (oldpwd_indc != -1)
		g_envv[oldpwd_indc] = ft_strjoin("OLDPWD=", tmp);
	free(tmp);
	tmp = getcwd(0,0);
	free(g_envv[pwd_indc]);
	g_envv[pwd_indc] = ft_strjoin("PWD=", tmp);
	free(tmp);
}
