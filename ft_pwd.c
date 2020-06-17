/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lacruype <lacruype@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 10:38:04 by rledrin           #+#    #+#             */
/*   Updated: 2020/06/17 15:09:45 by lacruype         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

size_t ft_strlen(const char *str)
{
	int i;

	i = 0;
	while (str[i])
	i++;
	return (i);
}

void	ft_putstr_fd(char *s, int fd)
{
	size_t i;

	i = 0;
	while (i < ft_strlen(s))
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
}

void		ft_pwd(void)
{
	char buf[256];
	char *ret;

	ret = getcwd(buf, 256);
	if (ret == NULL)
		return ;
	ft_putstr_fd(ret, 1);
}

int main(void)
{
	ft_pwd();
	return (0);
}