/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lacruype <lacruype@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 12:33:14 by lacruype          #+#    #+#             */
/*   Updated: 2020/02/10 15:36:59 by lacruype         ###   ########.fr       */
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

void	ft_freestrarr(char **arr)
{
	int i;

	i = -1;
	if (!arr)
		return ;
	if (*arr)
	{
		while (arr[++i])
			free(arr[i]);
	}
	free(arr);
	arr = NULL;
}

char	*ft_jump_space(char *str)
{
	int i;

	i = 0;
	while (str[i] == ' ')
		i++;
	return (&str[i]);
}
