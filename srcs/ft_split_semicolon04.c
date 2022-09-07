/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_semicolon04.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lacruype <lacruype@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 08:31:47 by lacruype          #+#    #+#             */
/*   Updated: 2020/07/06 16:40:08 by lacruype         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int		place_words02(char const *str, int *i, char **tab, int *taille)
{
	if ((str[(*i)] == '"' && (*i) == 0) ||
		(str[(*i)] == '"' && str[(*i) - 1] != '\\'))
	{
		(*tab)[(*taille)++] = str[(*i)++];
		while (str[(*i)])
		{
			if (str[(*i)] == '"')
				if (str[(*i) - 1] != '\\')
				{
					(*tab)[(*taille)++] = str[(*i)++];
					break ;
				}
			(*tab)[(*taille)++] = str[(*i)++];
		}
	}
	else
		return (0);
	return (1);
}

static int		place03(char const *str, int *i, char **tab, int *taille)
{
	if (((str[(*i)] == '\'' && (*i) == 0) ||
			(str[(*i)] == '\'' && str[(*i) - 1] != '\\')))
	{
		while (str[++(*i)])
		{
			if (str[(*i)] == '\'')
				if (str[(*i) - 1] != '\\')
					break ;
			(*tab)[(*taille)++] = str[(*i)];
		}
		return (1);
	}
	return (0);
}

static int		place04(char const *str, int *i, char c)
{
	while (str[(*i)] == c && str[(*i)])
	{
		if ((str[(*i)] == '"' && str[(*i) - 1] != '\\') ||
			(str[(*i)] == '\'' && str[(*i) - 1] != '\\'))
			return (3);
		(*i)++;
	}
	return (0);
}

static void		place05(char str, int *taille, char ***tab, int *words)
{
	if (str)
	{
		(*tab)[(*words)++][(*taille)] = '\0';
		(*taille) = 0;
	}
}

char			**place_words_semicolon(char const *str, char c, char **tab)
{
	int	i;
	int	words;
	int	taille;

	place06(&taille, &words, &i);
	while (str[i] == c)
		i++;
	while (str[i])
	{
		if ((place_words02(str, &i, &tab[words], &taille)) == 1)
			continue ;
		if ((place03(str, &i, &tab[words], &taille)) == 1)
			continue ;
		if (str[i] == c)
		{
			if (place04(str, &i, c) == 3)
				break ;
			place05(str[i], &taille, &tab, &words);
		}
		else
			tab[words][taille++] = str[i++];
	}
	tab[words][taille] = '\0';
	return (tab);
}
