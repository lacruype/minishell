/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rledrin <rledrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 13:42:31 by lacruype          #+#    #+#             */
/*   Updated: 2020/02/21 14:10:41 by rledrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// static void	ft_exit(void)
// {
// 	exit(0);
// }

int		ft_error(int error)
{
	ft_putstr_fd("Minishell : ", 1);
	if (error == 0)
		ft_putstr_fd("Quotes not closed !\n", 1);
	else if (error == 1)
		ft_putstr_fd("syntax error near unexpected token\n", 1);
	else if (error == 2)
		ft_putstr_fd("Quote is not closed !\n", 1);
	else if (error == 3)
		ft_putstr_fd("Didn't find the $? !\n", 1);
	else if (error == 4)
		ft_putstr_fd("Escaping chars has failed !\n", 1);
	else if(error == 5)
		ft_putstr_fd("Command doesn't exit !\n", 1);
	return (1);
}