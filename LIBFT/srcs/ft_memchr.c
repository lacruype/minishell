/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lacruype <lacruype@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 09:34:27 by lacruype          #+#    #+#             */
/*   Updated: 2019/10/18 18:50:01 by lacruype         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
