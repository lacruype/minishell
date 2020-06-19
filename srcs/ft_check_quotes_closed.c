/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_quotes_closed.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lacruype <lacruype@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 14:24:07 by lacruype          #+#    #+#             */
/*   Updated: 2020/06/19 13:57:48 by lacruype         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_check_quotes_closed(const char *str, int i)
{
	if ((str[i] == '"' && i == 0) || (str[i] == '"' && str[i - 1] != '\\'))
	{
		while (str[i] != '"' && str[i] != '\\')
		{
			if (str[i] == '\0')
				return (-1);
			i++;
		}
	}
	else if ((str[i] == '\'' && i == 0) || (str[i] == '\'' && str[i - 1] != '\\'))
	{
		while (str[i] != '\'' && str[i] != '\\')
		{
			if (str[i] == '\0')
				return (-1);
			i++;
		}
	}
	return (i);
}
