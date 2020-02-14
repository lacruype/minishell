/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lacruype <lacruype@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 09:58:23 by rledrin           #+#    #+#             */
/*   Updated: 2020/02/14 13:27:56 by lacruype         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void handle_sigint(int sig)
{
	signal(SIGINT, handle_sigint);
	printf("TEST");
}

int main()
{
	long unsigned int i = 0;

	handle_sigint();
	while(i < 1000000000)
		i++;
	return 0;
}
