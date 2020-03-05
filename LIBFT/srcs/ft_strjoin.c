/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lacruype <lacruype@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 13:16:06 by lacruype          #+#    #+#             */
/*   Updated: 2019/10/18 18:52:04 by lacruype         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		size1;
	int		size2;
	char	*str;
	int		j;

	i = 0;
	j = 0;
	size1 = ft_strlen(s1);
	size2 = ft_strlen(s2);
	if (!(str = (char*)ft_calloc((size1 + size2 + 1), sizeof(char))))
		return (0);
	while (i < size1)
	{
		str[i] = s1[i];
		i++;
	}
	while (j < size2)
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
}
