/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_semicolon03.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lacruype <lacruype@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 08:31:47 by lacruype          #+#    #+#             */
/*   Updated: 2020/07/06 16:40:51 by lacruype         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void		size_words03(int *words, int *taille, int *i)
{
	*i = 0;
	*taille = 0;
	*words = 0;
}

static int		size_words02(char const *str, int *t, int *i)
{
	if ((str[*i] == '"' && *i == 0) ||
		(str[*i] == '"' && str[*i - 1] != '\\'))
	{
		while (str[++(*i)] && ++(*t) > -1)
			if (str[*i] == '"')
				if (str[*i - 1] != '\\' && (*i)++ > -1)
				{
					(*t)++;
					break ;
				}
	}
	else if ((str[*i] == '\'' && *i == 0) ||
			(str[*i] == '\'' && str[*i - 1] != '\\'))
	{
		while (str[++(*i)])
		{
			if (str[*i] == '"')
				if (str[*i - 1] != '\\')
					break ;
			(*t)++;
		}
	}
	else
		return (0);
	return (1);
}

static int		size_words04(char const *str, char c, int *i)
{
	while (str[*i] == c && str[*i])
	{
		if ((str[*i] == '"' && str[*i - 1] != '\\') ||
			(str[*i] == '\'' && str[*i - 1] != '\\'))
			break ;
		(*i)++;
	}
	return (0);
}

static void		size_words05(int *i, int *taille)
{
	(*i)++;
	(*taille)++;
}

char			**size_words_semicolon(char const *str, char c, char **tab)
{
	int i;
	int words;
	int taille;

	size_words03(&words, &taille, &i);
	while (str[i] == c)
		i++;
	while (str[i])
	{
		if ((size_words02(str, &taille, &i)) == 1)
			continue ;
		else if (str[i] == c)
		{
			if (size_words04(str, c, &i) == 3)
				break ;
			if (size_words06(str[i], &tab, &words, &taille) == -12)
				return (0);
		}
		else
			size_words05(&i, &taille);
	}
	if (!(tab[words] = ft_calloc((taille + 1), sizeof(char))))
		return (0);
	return (tab);
}
