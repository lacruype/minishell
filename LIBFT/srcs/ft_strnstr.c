/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lacruype <lacruype@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 15:09:19 by lacruype          #+#    #+#             */
/*   Updated: 2019/10/18 18:52:20 by lacruype         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t len)
{
	size_t		i;
	int			j;
	int			size;
	char		*b;

	i = 0;
	b = (char*)s1;
	size = ft_strlen(s2);
	if (size == 0)
		return (b);
	while (b[i] && i < len)
	{
		j = 0;
		while (b[i + j] && s2[j] && (i + j) < len &&
				(b[i + j] == s2[j]))
			j++;
		if (j == size)
			return (&(b[i]));
		i++;
	}
	return (0);
}
