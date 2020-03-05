/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lacruype <lacruype@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 15:01:24 by lacruype          #+#    #+#             */
/*   Updated: 2019/10/16 13:52:31 by lacruype         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_listdelone(t_list *lst, void (*del)(void*))
{
	if (lst == NULL)
		return ;
	(*del)(lst->content);
	free(lst);
}
