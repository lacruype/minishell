/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing01.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lacruype <lacruype@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 12:31:15 by lacruype          #+#    #+#             */
/*   Updated: 2020/02/06 12:38:56 by lacruype         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_parsing(char *command_line)
{
	int i;
	int j;
	char *str;

	i = 0;
	j = 0;
	str = ft_strdup("");
	while (command_line[i])
	{
		i = ft_jump_space(command_line, i);
		while (ft_isalpha(command_line[i]) == 1)
		{
			ft_realloc(str, (ft_strlen(str) + 1));
			str[j] = ft_tolower(command_line[i]);
			i++;
			j++;
		}
		//ft_find_function();
		
	}
}
