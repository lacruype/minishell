/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lacruype <lacruype@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 15:48:18 by lacruype          #+#    #+#             */
/*   Updated: 2020/02/10 15:53:01 by lacruype         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	int		get_size_env(char **env)
{
	int i;

	i = -1;
	while (env[++i])
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
	return (0);
}
