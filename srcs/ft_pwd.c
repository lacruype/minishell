/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rledrin <rledrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 10:38:04 by rledrin           #+#    #+#             */
/*   Updated: 2020/03/10 11:08:01 by rledrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


void		ft_pwd(char **args)
{
	int		i;

	i = 0;
	if (ft_strncmp(args[0], "pwd", 4) != 0)
	{
		printf("ERROR\n");
		return ;
	}
	while(g_envv[i] && ft_strncmp(g_envv[i], "PWD=", 4) != 0)
		i++;
	if (g_envv[i])
		ft_putstr_fd(g_envv[i], 1);
}
