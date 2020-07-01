/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_quotes_closed.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lacruype <lacruype@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 14:24:07 by lacruype          #+#    #+#             */
/*   Updated: 2020/06/30 16:36:14 by lacruype         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_check_quotes_closed(const char *s, int i)
{
	if ((s[i] == '"' && i == 0) || (s[i] == '"' && s[i - 1] != '\\'))
	{
		i++;
		while (s[i])
		{
			if (s[i] == '"')
				if (s[i - 1] != '\\')
					return (i);
			i++;
		}
		return (-1);
	}
	else if ((s[i] == '\'' && i == 0) || (s[i] == '\'' && s[i - 1] != '\\'))
	{
		i++;
		while (s[i])
		{
			if (s[i] == '\'')
				if (s[i - 1] != '\\')
					return (i);
			i++;
		}
		return (-1);
	}
	return (i);
}
