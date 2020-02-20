/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_escape_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lacruype <lacruype@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 14:24:07 by lacruype          #+#    #+#             */
/*   Updated: 2020/02/18 10:21:08 by lacruype         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		jump_quotes(const char *str, int i)
{
	if (str[i] == '\'')
	{
		while (str[++i] != '\'')
		{
			if (str[i] == '\0')
				return (-1);
		}
	}
	else if (str[i] == '"')
	{
		while (str[++i] != '"')
		{
			if (str[i] == '\0')
				return (-1);
		}
	}
	return (i);
}
