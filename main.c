/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rledrin <rledrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 11:14:32 by rledrin           #+#    #+#             */
/*   Updated: 2020/02/04 14:21:32 by rledrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"




int			main(int ac, char **av)
{
	ssize_t	ret;
	char	buf[2];
	char	*cmd;
	pid_t	pid;
	int check_exit = 0;
	cmd = ft_strdup("");

	buf[1] = '\0';

	while (1)
	{
		while(read(1, buf, 1))
		{
			
			if (buf)
			if (buf[0] == '\0')
				exit(0);
		}

	}



	return (0);
}
