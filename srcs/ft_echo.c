/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lacruype <lacruype@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 14:00:13 by lacruype          #+#    #+#             */
/*   Updated: 2020/06/30 14:00:15 by lacruype         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_echo(char **args)
{
	int	i;
	int	j;
	int	option;

	i = 0;
	j = 0;
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
