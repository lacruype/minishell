/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lacruype <lacruype@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 11:06:48 by lacruype          #+#    #+#             */
/*   Updated: 2019/10/18 18:53:48 by lacruype         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	const char		*s;
	char			*d;

	i = 0;
	s = src;
	d = (char*)dst;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dst);
}
