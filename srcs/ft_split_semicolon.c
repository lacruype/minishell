/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_semicolon.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rledrin <rledrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 08:31:47 by lacruype          #+#    #+#             */
/*   Updated: 2020/03/10 13:17:13 by rledrin          ###   ########.fr       */
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
		if ((str[i] == '"' && i == 0) || (str[i] == '"' && str[i - 1] != '\\'))
		{
			i++;
			while (str[i] && str[i] != '"' && str[i - 1] != '\\')
				i++;
		}
		else if ((str[i] == '\'' && i == 0) || (str[i] == '\'' && str[i - 1] != '\\'))
		{
			i++;
			while (str[i] && str[i] != '\'' && str[i - 1] != '\\')
				i++;
		}
		else if (str[i] == c || !str[i])
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
	while (str[i])
	{
		if ((str[i] == '"' && i == 0) || (str[i] == '"' && str[i - 1] != '\\'))
		{
			taille++;
			i++;
			while (str[i] && str[i] != '"' && str[i - 1] != '\\')
			{
				taille++;
				i++;
			}
		}
		else if ((str[i] == '\'' && i == 0) || (str[i] == '\'' && str[i - 1] != '\\'))
		{
			taille++;
			i++;
			while (str[i] && str[i] != '\'' && str[i - 1] != '\\')
			{
				taille++;
				i++;
			}
		}
		else if (str[i] == c || !str[i])
		{
			if (!(tab[words] = ft_calloc((taille + 1), sizeof(char))))
				return (0);
			printf("HIHI WORDS = %d Taille = %d I = %d\n", words, taille, i);
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
	while (str[i])
	{
		if ((str[i] == '"' && i == 0) || (str[i] == '"' && str[i - 1] != '\\'))
		{
			tab[words][taille] = str[i];
			taille++;
			i++;
			while (str[i] && str[i] != '"' && str[i - 1] != '\\')
			{
				tab[words][taille] = str[i];
				taille++;
				i++;
			}
		}
		else if ((str[i] == '\'' && i == 0) || (str[i] == '\'' && str[i - 1] != '\\'))
		{
			tab[words][taille] = str[i];
			taille++;
			i++;
			while (str[i] && str[i] != '\'' && str[i - 1] != '\\')
			{
				tab[words][taille] = str[i];
				taille++;
				i++;
			}
		}
		else if (str[i] == c || str[i] == '\0')
		{
			//printf("WORDS = %d Taille = %d I = %d\n", words, taille, i);
			tab[words][taille] = '\0';
			words++;
			taille = 0;
			if (str[i] == '\0')
				return (tab);
			i++;
		}
		else
		{
			printf("HQHQ WORDS = %d Taille = %d I = %d\n", words, taille, i);
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
	if (!(tab = ft_calloc((nb_words + 1), sizeof(char*))))
		return (0);
	tab[nb_words] = NULL;
	printf("NB_WORDS = %d\n", nb_words);
	size_words_semicolon(s, c, tab);
	place_words_semicolon(s, c, tab);
	if (tab[nb_words] && tab[nb_words][0] == '\0')
		free(tab[nb_words]);
	tab[nb_words] = NULL;
	return (tab);
}

int main ()
{
	char **t = ft_split_semicolon("HAHAHA ; je suis la ; SALUT", ';');
	int i = 0;
	while (t[i])
	{
		printf("%s\n",t[i]);
		i++;
	}


}
