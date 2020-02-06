/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lacruype <lacruype@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 12:33:14 by lacruype          #+#    #+#             */
/*   Updated: 2020/02/06 12:59:55 by lacruype         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	*ft_realloc(void *dst, size_t new_size)
{
	size_t	cur_size;
	char	*newdst;

	if (dst == 0)
		return (malloc(new_size));
	cur_size = sizeof(dst);
	if (new_size <= cur_size)
		return (dst);
	newdst = malloc(new_size);
	ft_memcpy(dst, newdst, (int)cur_size);
	free(dst);
	return (newdst);
}

int		ft_jump_space(char *str, int i)
{
	while (str[i] == ' ')
		i++;
	return (i);
}
