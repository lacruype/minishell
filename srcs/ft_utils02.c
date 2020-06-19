/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils02.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lacruype <lacruype@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 11:15:34 by lacruype          #+#    #+#             */
/*   Updated: 2020/06/19 13:47:08 by lacruype         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_escape_char(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			while (str[++i] != '\'')
			{
				if (str[i] == '\0')
					return (0);
				if (ft_strchr("$\"\\;|<>", str[i]))
					str = ft_putstrstr(str, "\\", i++);
			}
		}
		else if (str[i] == '"')
		{
			while (str[++i] != '"')
			{
				if (str[i] == '\0')
					return (0);
				if (ft_strchr(";|<>", str[i]))
					str = ft_putstrstr(str, "\\", i++);
			}
		}
		i++;
	}
	return (str);
}
