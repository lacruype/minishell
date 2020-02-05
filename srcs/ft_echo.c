/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rledrin <rledrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 11:25:16 by rledrin           #+#    #+#             */
/*   Updated: 2020/02/05 12:06:18 by rledrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_echo(char *str, char *file_name, int option)
{
	int	fd;
	if (file_name)
		fd = open(file_name, O_CREAT | O_WRONLY);
	else
		fd = 1;
	write(fd, str, ft_strlen(str));
	if (option)
		write(fd, "\n", 2);
	if (file_name)
		close(fd);
}