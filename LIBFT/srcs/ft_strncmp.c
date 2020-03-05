/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lacruype <lacruype@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 13:45:34 by lacruype          #+#    #+#             */
/*   Updated: 2019/10/18 18:52:31 by lacruype         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*p1;
	unsigned char	*p2;

	p1 = (unsigned char *)s1;
	p2 = (unsigned char *)s2;
	i = 0;
	if (n == 0)
		return (0);
	while (p1[i] != '\0' && p2[i] != '\0' && p1[i] == p2[i] && i < (n - 1))
		i++;
	if (p1[i] != p2[i])
		return (p1[i] - p2[i]);
	else
		return (0);
}
