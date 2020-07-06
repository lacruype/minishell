/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_spaces_quotes_gone02.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lacruype <lacruype@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 13:05:48 by lacruype          #+#    #+#             */
/*   Updated: 2020/07/06 16:39:47 by lacruype         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	int		nb_word_ssqg02(char const *str, char c, int *i, int *words)
{
	if ((str[*i] == '\'' && *i == 0)
		|| (str[*i] == '\'' && str[*i - 1] != '\\'))
	{
		(*i)++;
		while (str[*i])
		{
			if (str[*i] == '\'')
				if (str[*i - 1] != '\\')
					break ;
			(*i)++;
		}
	}
	else if (str[*i] == c)
	{
		while (str[*i] == c && str[*i])
			(*i)++;
		if (str[*i])
			return ((*words)++);
	}
	else
		(*i)++;
	return (0);
}

int				nb_word_ssqg(char const *str, char c)
{
	int i;
	int words;

	i = 0;
	words = 1;
	while (str[i] == c)
		i++;
	while (str[i])
	{
		if ((str[i] == '"' && i == 0) || (str[i] == '"' && str[i - 1] != '\\'))
			while (str[++i])
			{
				if (str[i] == '\\' && str[i - 1] != '\\')
					i++;
				if (str[i] == '"')
					if (str[i - 1] != '\\')
						break ;
			}
		else if (nb_word_ssqg02(str, c, &i, &words) != 0)
			continue ;
		if (((str[i] == '"' || str[i] == '\'') && str[i - 1] != '\\')
			|| (str[i] == '\\' && str[i - 1] != '\\'))
			i++;
	}
	return (words);
}
