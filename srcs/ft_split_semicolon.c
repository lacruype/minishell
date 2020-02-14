/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_semicolon.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lacruype <lacruype@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 08:31:47 by lacruype          #+#    #+#             */
/*   Updated: 2020/02/14 11:05:13 by lacruype         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdlib.h>
#include <stdio.h>

static int		nb_words_semicolon(char const *str, char c)
{
	int i;
	int words;

	i = 0;
	words = 0;
	while (str[i])
	{
		if (str[i] == '"')
		{
			i++;
			while (str[i] != '"' && str[i])
				i++;
			if (str[i] == '\0')
				ft_error(2);
		}
		else if (str[i] == '\'')
		{
			i++;
			while (str[i] != '\'' && str[i])
				i++;
			if (str[i] == '\0')
				ft_error(2);
		}
		else if (str[i] == c)
		{
			words++;
			i++;
		}
		else
			i++;
	}
	words++;
	return (words);
}

static char		**size_words_semicolon(char const *str, char c, char **tab)
{
	int i;
	int words;
	int taille;

	i = 0;
	taille = 0;
	words = 0;
	while (1)
	{
		if (str[i] == '"')
		{
			taille++;
			i++;
			while (str[i] != '"' && str[i])
			{
				taille++;
				i++;
			}
		}
		else if (str[i] == '\'')
		{
			taille++;
			i++;
			while (str[i] != '\'' && str[i])
			{
				taille++;
				i++;
			}
		}
		else if (str[i] == c || str[i] == '\0')
		{
			if (!(tab[words] = malloc(sizeof(char) * taille + 1)))
				return (0);
			words++;
			taille = 0;
			if (str[i] == '\0')
				return (tab);
			i++;
		}
		else
		{
			i++;
			taille++;
		}
	}
	return (tab);
}

static char		**place_words_semicolon(char const *str, char c, char **tab)
{
	int i;
	int words;
	int taille;

	i = 0;
	taille = 0;
	words = 0;
	while (1)
	{
		if (str[i] == '"')
		{
			tab[words][taille] = str[i];
			taille++;
			i++;
			while (str[i] != '"' && str[i])
			{
				tab[words][taille] = str[i];
				taille++;
				i++;
			}
		}
		else if (str[i] == '\'')
		{
			tab[words][taille] = str[i];
			taille++;
			i++;
			while (str[i] != '\'' && str[i])
			{
				tab[words][taille] = str[i];
				taille++;
				i++;
			}
		}
		else if (str[i] == c || str[i] == '\0')
		{
			tab[words][taille] = '\0';
			words++;
			taille = 0;
			if (str[i] == '\0')
				return (tab);
			i++;
		}
		else
		{
			tab[words][taille] = str[i];
			i++;
			taille++;
		}
	}
	return (tab);
}

char		**ft_split_semicolon(char const *s, char c)
{
	int		i;
	int		nb_words;
	char	**tab;

	i = 0;
	nb_words = nb_words_semicolon(s, c);
	if (!(tab = malloc(sizeof(char*) * (nb_words + 1))))
		return (0);
	tab[nb_words] = NULL;
	size_words_semicolon(s, c, tab);
	place_words_semicolon(s, c, tab);
	if (tab[nb_words] && tab[nb_words][0] == '\0')
		free(tab[nb_words]);
	tab[nb_words] = NULL;
	return (tab);
}
