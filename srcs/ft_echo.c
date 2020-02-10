/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lacruype <lacruype@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 11:25:16 by rledrin           #+#    #+#             */
/*   Updated: 2020/02/10 15:17:08 by lacruype         ###   ########.fr       */
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
		write(fd, "\n", 1);
	if (file_name)
		close(fd);
}
