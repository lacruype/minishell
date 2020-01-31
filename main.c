/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rledrin <rledrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 11:14:32 by rledrin           #+#    #+#             */
/*   Updated: 2020/01/31 12:02:41 by rledrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			main(int ac, char **av)
{
	ssize_t	ret;
	char	buf[2];
	char	*cmd;

	cmd = ft_strdup("");
	while (1)
	{
		ft_putstr("Prompt:");
		while ((ret = read(0, buf, 1)) >= 0)
		{

			


		}
		// if (ctrlC)
		// 	break;
	


	}



	return (0);
}
