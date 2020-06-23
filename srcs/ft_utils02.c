/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils02.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lacruype <lacruype@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 11:15:34 by lacruype          #+#    #+#             */
/*   Updated: 2020/06/23 16:55:37 by lacruype         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// char	*ft_escape_char(char *str)
// {
// 	int i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '\'')
// 		{
// 			while (str[++i] != '\'')
// 			{
// 				if (str[i] == '\0')
// 					return (0);
// 				if (ft_strchr("$\"\\;|<>", str[i]))
// 					str = ft_putstrstr(str, "\\", i++);
// 			}
// 		}
// 		else if (str[i] == '"')
// 		{
// 			while (str[++i] != '"')
// 			{
// 				if (str[i] == '\0')
// 					return (0);
// 				if (ft_strchr(";|<>", str[i]))
// 					str = ft_putstrstr(str, "\\", i++);
// 			}
// 		}
// 		i++;
// 	}
// 	printf("REND = [%s]\n", str);
// 	return (str);
// }

void    ft_cmd_to_lower(char **cmd)
{
    int i;

    i = 0;
    while ((*cmd)[i])
    {
        (*cmd)[i] = ft_tolower((*cmd)[i]);
        i++;
    }
}