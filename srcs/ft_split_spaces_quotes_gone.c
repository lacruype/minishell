/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_spaces_quotes_gone.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lacruype <lacruype@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/19 14:32:07 by lacruype          #+#    #+#             */
/*   Updated: 2020/07/06 14:58:22 by lacruype         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	int		place_ssqg02(const char *str, int *i, char quote)
{
	if (str[*i] == '\\' && str[*i - 1] != '\\')
		(*i)++;
	if (str[*i] == quote)
		if (str[*i - 1] != '\\')
			return (1);
	return (0);
}

static	int		place_ssqg03(char const *str, char **tab, int *taille, int *i)
{
	if ((str[*i] == '"' && *i == 0) || (str[*i] == '"' && str[*i - 1] != '\\'))
	{
		while (str[++(*i)])
		{
			if (place_ssqg02(str, i, '"') == 1)
				break ;
			(*tab)[(*taille)++] = str[*i];
		}
		return (1);
	}
	else if ((str[*i] == '\'' && *i == 0)
		|| (str[*i] == '\'' && str[*i - 1] != '\\'))
	{
		while (str[++(*i)])
		{
			if (place_ssqg02(str, i, '\'') == 1)
				break ;
			(*tab)[(*taille)++] = str[*i];
		}
		return (1);
	}
	return (0);
}

static	int		place_ssqg04(char const *str, char *tab, int *i, int *words)
{
	if (str[*i] == ' ')
	{
		while (str[*i] == ' ' && str[*i])
			(*i)++;
		if (str[*i])
		{
			*tab = '\0';
			(*words)++;
			return (2);
		}
	}
	else if (((str[*i] == '"' || str[*i] == '\'') && str[*i - 1] != '\\')
		|| (str[*i] == '\\' && str[*i - 1] != '\\'))
		(*i)++;
	else
		return (0);
	return (1);
}

static	char	**place_ssqg(char const *str, char c, char **tab)
{
	int i;
	int words;
	int taille;
	int ret;

	i = 0;
	taille = 0;
	words = 0;
	while (str[i] == c)
		i++;
	while (str[i])
	{
		if (place_ssqg03(str, &tab[words], &taille, &i) == 1)
			continue ;
		else if ((ret = place_ssqg04(str,
			&tab[words][taille], &i, &words)) == 2)
			taille = 0;
		if (ret != 0)
			continue ;
		else
			tab[words][taille++] = str[i++];
	}
	tab[words][taille] = '\0';
	return (tab);
}

char			**ft_split_spaces_quotes_gone(char const *s, char c)
{
	int		i;
	int		nb_words;
	char	**tab;

	i = 0;
	nb_words = nb_word_ssqg(s, c);
	if (!(tab = ft_calloc((nb_words + 1), sizeof(char*))))
		return (0);
	tab[nb_words] = NULL;
	size_ssqg(s, c, tab);
	place_ssqg(s, c, tab);
	if (tab[nb_words] && tab[nb_words][0] == '\0')
		free(tab[nb_words]);
	tab[nb_words] = NULL;
	return (tab);
}
