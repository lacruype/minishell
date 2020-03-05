/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lacruype <lacruype@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 11:43:57 by lacruype          #+#    #+#             */
/*   Updated: 2019/10/18 18:51:30 by lacruype         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_checkset(char c, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (c == str[i])
			return (1);
		i++;
	}
	return (0);
}

int		ft_uni(char *set, char *str)
{
	int	i;
	int	j;

	i = 0;
	while (set[i])
	{
		j = 0;
		if (set[i] == str[j])
		{
			while (set[i] == str[j])
				j++;
			if (ft_strlen(str) == (size_t)j)
				return (1);
		}
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		i;
	int		len;
	int		j;

	i = 0;
	j = 0;
	len = ft_strlen(s1);
	if (!(str = malloc(sizeof(char) * (len - i) + 1)) || s1 == 0)
		return (NULL);
	if (set == 0)
		return ((char*)s1);
	if (ft_uni((char*)set, (char*)s1))
	{
		str[j] = '\0';
		return (str);
	}
	while (ft_checkset(s1[i], (char*)set))
		i++;
	while (ft_checkset(s1[len - 1], (char*)set))
		len--;
	while (i < len)
		str[j++] = s1[i++];
	str[j] = '\0';
	return (str);
}
