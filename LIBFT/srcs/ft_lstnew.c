/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lacruype <lacruype@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 14:29:38 by lacruype          #+#    #+#             */
/*   Updated: 2019/10/16 13:52:52 by lacruype         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list *p;

	if (!(p = malloc(sizeof(t_list))))
		return (0);
	p->content = content;
	p->next = NULL;
	return (p);
}
