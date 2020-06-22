/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_quotes_closed.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lacruype <lacruype@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 14:24:07 by lacruype          #+#    #+#             */
/*   Updated: 2020/06/22 13:29:02 by lacruype         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_check_quotes_closed(const char *str, int i)
{
	if ((str[i] == '"' && i == 0) || (str[i] == '"' && str[i - 1] != '\\'))
	{
		i++;
		while (str[i])
		{
			if (str[i] == '"')
				if (str[i - 1] != '\\')
					return (i);
			i++;
		}
		return (-1);
	}
	else if ((str[i] == '\'' && i == 0) || (str[i] == '\'' && str[i - 1] != '\\'))
	{
		i++;
		while (str[i])
		{
			if (str[i] == '\'')
				if (str[i - 1] != '\\')
					return (i);
			i++;
		}
		return (-1);
	}
	return (i);
}
