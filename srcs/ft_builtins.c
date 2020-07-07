/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lacruype <lacruype@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 14:20:01 by lacruype          #+#    #+#             */
/*   Updated: 2020/07/03 14:55:14 by lacruype         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_pwd(void)
{
	char buf[256];
	char *ret;

	ret = getcwd(buf, 256);
	if (ret == NULL)
		return ;
	ft_putstr_fd(ret, 1);
	ft_putstr_fd("\n", 1);
}

void	ft_echo(char **args)
{
	int	i;
	int	option;

	i = 0;
	option = 0;
	if (!args[1])
	{
		write(1, "\n", 1);
		return ;
	}
	if (ft_strncmp(args[1], "-n", 3) == 0)
	{
		option = 1;
		i = 1;
	}
	while (args[++i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1] != NULL)
			write(1, " ", 1);
	}
	if (!option)
		write(1, "\n", 1);
}
