/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rledrin <rledrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 12:05:39 by lacruype          #+#    #+#             */
/*   Updated: 2020/03/05 16:12:43 by rledrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*dst;

	i = 0;
	if (!(dst = ft_calloc(sizeof(char), 1)))
		return (0);
	if ((dst == (char*)s) || (start > ft_strlen(s)))
	{
		dst[i] = '\0';
		return (dst);
	}
	free(dst);
	if (!(dst = malloc(sizeof(char) * (len + 1))))
		return (0);
	while (i < len)
	{
		dst[i] = s[start + i];
		i++;
	}
	if (dst)
		dst[i] = '\0';
	return (dst);
}
