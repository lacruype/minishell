/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lacruype <lacruype@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 13:42:31 by lacruype          #+#    #+#             */
/*   Updated: 2020/02/14 09:56:51 by lacruype         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// static void	ft_exit(void)
// {
// 	exit(0);
// }

void	ft_error(int error)
{
	ft_putstr_fd("Minishell : ", 1);
	if (error == 0)
		ft_putstr_fd("Error !\n", 1);
	else if (error == 1)
		ft_putstr_fd("syntax error near unexpected token\n", 1);
	else if (error == 2)
		ft_putstr_fd("Quote is not closed !\n", 1);
	
}