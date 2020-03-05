/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rledrin <rledrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 15:09:19 by lacruype          #+#    #+#             */
/*   Updated: 2020/03/05 16:12:43 by rledrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

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
