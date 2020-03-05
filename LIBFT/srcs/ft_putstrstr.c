/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstrstr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lacruype <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 15:20:53 by lacruype          #+#    #+#             */
/*   Updated: 2020/02/17 16:23:02 by lacruype         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_putstrstr(char *s1, char *s2, int pos)
{
	int		i;
	int		j;
	int		k;
	size_t	len;
	char	*dest;

	i = 0;
	j = 0;
	k = 0;
	len = ft_strlen(s1) + ft_strlen(s2);
	if (!(dest = malloc(sizeof(char) * (len + 1))) || pos > (int)len)
		return (0);
	while (s1[i])
	{
		if (i == pos)
			while (s2[j])
				dest[k++] = s2[j++];
		dest[k++] = s1[i++];
	}
	dest[k] = '\0';
	free(s1);
	return (dest);
}

