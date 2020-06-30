/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lacruype <lacruype@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 13:42:31 by lacruype          #+#    #+#             */
/*   Updated: 2020/06/30 15:17:15 by lacruype         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_error(char *cmd, char *arg, int error)
{
	ft_putstr_fd(cmd, 1);
	ft_putstr_fd(": ", 1);
	exit_status = 1;
	if (*arg && error != 1)
	{
		ft_putstr_fd(arg, 1);
		ft_putstr_fd(" : ", 1);
	}
	if (error == -100)
	{
		exit_status = 127;
		ft_putstr_fd("command not found", 1);
	}
	else if (error == -10)
	{
		exit_status = 258;
		ft_putstr_fd("syntax error near unexpected token '", 1);
		ft_putstr_fd(arg, 1);
		ft_putstr_fd("'", 1);
	}
	else if (error == -3)
		ft_putstr_fd("HOME not set", 1);
	else if (error == -4)
	{
		ft_putstr_fd("quotes not closed ", 1);
		ft_putstr_fd(arg, 1);
	}
	else
	{
		errno = error;
		ft_putstr_fd(strerror(errno), 1);
	}
	ft_putchar_fd('\n', 1);
	// else if (error == 6)
	// 	ft_putstr_fd("not a valid idetifier\n", 1);
	return (-1);
}
