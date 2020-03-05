/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rledrin <rledrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 09:34:27 by lacruype          #+#    #+#             */
/*   Updated: 2020/03/05 16:12:43 by rledrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char	*p;
	int		i;

	i = 0;
	p = (char*)s;
	while (i < (int)n)
	{
		if (p[i] == (char)c)
			return (&p[i]);
		i++;
	}
	return (0);
}
