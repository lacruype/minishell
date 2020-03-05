/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lacruype <lacruype@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 13:49:45 by lacruype          #+#    #+#             */
/*   Updated: 2019/10/18 18:53:05 by lacruype         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
