/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lacruype <lacruype@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 13:42:31 by lacruype          #+#    #+#             */
/*   Updated: 2020/07/06 16:43:39 by lacruype         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void			f(char c)
{
	write(1, &c, 1);
}

static void		ft_error02(char *arg, int error)
{
	if (error == -10)
	{
		g_exit_status = 258;
		ft_putstr_fd("syntax error near unexpected token '", 1);
		ft_putstr_fd(arg, 1);
		ft_putstr_fd("'", 1);
	}
	else if (error == -100)
	{
		g_exit_status = 127;
		ft_putstr_fd("command not found", 1);
	}
	else
	{
		errno = error;
		ft_putstr_fd(strerror(errno), 1);
	}
}

int				ft_error(char *cmd, char *arg, int error)
{
	ft_putstr_fd(cmd, 1);
	ft_putstr_fd(": ", 1);
	g_exit_status = 1;
	if (*arg && error != -10)
	{
		ft_putstr_fd(arg, 1);
		ft_putstr_fd(" : ", 1);
	}
	if (error == -2)
		ft_putstr_fd("not a valid identifier", 1);
	else if (error == -3)
		ft_putstr_fd("HOME not set", 1);
	else if (error == -4)
	{
		ft_putstr_fd("quotes not closed ", 1);
		ft_putstr_fd(arg, 1);
	}
	else
		ft_error02(arg, error);
	ft_putchar_fd('\n', 1);
	return (-1);
}
