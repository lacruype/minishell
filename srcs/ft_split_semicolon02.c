/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_semicolon02.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lacruype <lacruype@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 08:31:47 by lacruype          #+#    #+#             */
/*   Updated: 2020/07/06 16:23:04 by lacruype         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void		nb_words_se03(const char *str, char c, int *i, int *words)
{
	while (str[(*i)] == c && str[(*i)])
	{
		if ((str[(*i)] == '"' && str[*i - 1] != '\\') ||
			(str[(*i)] == '\'' && str[*i - 1] != '\\'))
			break ;
		(*i)++;
	}
	if (str[(*i)])
		(*words)++;
}

static int		nb_words_semicolon02(const char *str, int *i)
{
	if ((str[(*i)] == '"' && (*i) == 0) ||
		(str[(*i)] == '"' && str[(*i) - 1] != '\\'))
	{
		while (str[++(*i)])
			if (str[(*i)] == '"')
				if (str[(*i) - 1] != '\\')
					break ;
	}
	else if ((str[(*i)] == '\'' && (*i) == 0) ||
			(str[(*i)] == '\'' && str[(*i) - 1] != '\\'))
	{
		while (str[++(*i)])
			if (str[(*i)] == '\'')
				if (str[(*i) - 1] != '\\')
					break ;
	}
	else
		return (0);
	return (1);
}

int				nb_words_semicolon(char const *str, char c)
{
	int i;
	int words;

	i = 0;
	words = 1;
	while (str[i] == c)
		i++;
	while (str[i])
	{
		if ((nb_words_semicolon02(str, &i)) == 1)
			;
		else if (str[i] == c)
			nb_words_se03(str, c, &i, &words);
		else
			i++;
		if (((str[i] == '"' || str[i] == '\'') && str[i - 1] != '\\') ||
			(str[i] == '\\' && str[i - 1] != '\\'))
			i++;
	}
	return (words);
}

int				size_words06(char strc, char ***tab, int *words, int *t)
{
	if (strc)
	{
		if (!((*tab)[(*words)] = ft_calloc(((*t) + 1), sizeof(char))))
			return (-12);
		(*t) = 0;
		(*words)++;
	}
	return (0);
}

void			place06(int *taille, int *words, int *i)
{
	*i = 0;
	*taille = 0;
	*words = 0;
}
