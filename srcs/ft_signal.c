/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lacruype <lacruype@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 09:58:23 by rledrin           #+#    #+#             */
/*   Updated: 2020/02/14 11:29:53 by lacruype         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void handle_sigint(int sig)
{
	printf("TEST");
}

int main()
{
	long unsigned int i = 0;
	signal(SIGINT, handle_sigint);
	while(i < 1000000000)
		i++;
	return 0;
}
