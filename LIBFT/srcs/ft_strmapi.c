/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rledrin <rledrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 13:49:45 by lacruype          #+#    #+#             */
/*   Updated: 2020/03/05 16:12:43 by rledrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	f(unsigned int i, char c)
{
	return (i + c);
}

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int		size;
	char				*str;
	unsigned int		i;

	if (!s || !f)
		return (0);
	size = ft_strlen(s);
	i = 0;
	if (!(str = ft_calloc(size + 1, sizeof(char))))
		return (0);
	while (i < size)
	{
		str[i] = (*f)(i, s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}
