/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lacruype <lacruype@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 09:05:28 by lacruype          #+#    #+#             */
/*   Updated: 2019/10/18 18:53:19 by lacruype         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	int			i;
	char		*d;
	const char	*s;

	d = (char*)dst;
	s = (const char*)src;
	i = 0;
	if (d < s)
	{
		while (i < (int)len)
		{
			d[i] = s[i];
			i++;
		}
	}
	else
	{
		while (i < (int)len)
		{
			d[(len - 1) - i] = s[(len - 1) - i];
			i++;
		}
	}
	return (dst);
}
