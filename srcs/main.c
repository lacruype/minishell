/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rledrin <rledrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 11:14:32 by rledrin           #+#    #+#             */
/*   Updated: 2020/02/05 12:14:18 by rledrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>

int			main(int ac, char **av)
{

	(void)ac;
	(void)av;
	char	buf[2];
	char	*cmd;
	pid_t	pid;
	int		test[2];
	char	retest[100];
	cmd = ft_strdup("");

	pipe(test);

	buf[1] = '\0';
	
	if ((pid = fork()) == 0)
	{
		write(test[1], "AAA", 4);
		close(test[1]);
		exit(EXIT_SUCCESS);
	}
	wait(0);
	read(test[0], retest, 100);
	printf("pid = %d %s",pid, retest);

	return (0);
}
