/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lacruype <lacruype@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 17:06:25 by lacruype          #+#    #+#             */
/*   Updated: 2020/03/10 14:24:03 by lacruype         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	int		i;
	void	*p;
	char	*pp;

	i = 0;
	if (!(p = malloc(size * count)))
		return (0);
	pp = (char*)p;
	while (i < (int)(size * count))
	{
		pp[i] = '\0';
		i++;
	}
	return (p);
}
