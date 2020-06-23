/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lacruype <lacruype@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 10:38:04 by rledrin           #+#    #+#             */
/*   Updated: 2020/06/23 15:57:52 by lacruype         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		ft_pwd(void)
{
	char buf[256];
	char *ret;

	ret = getcwd(buf, 256);
	if (ret == NULL)
		return ;
	ft_putstr_fd(ret, 1);
}
