/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rledrin <rledrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 17:30:31 by lacruype          #+#    #+#             */
/*   Updated: 2020/03/05 16:12:43 by rledrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int		nombre_mots(char const *str, char c)
{
	int i;
	int mots;

	i = 0;
	mots = 0;
	while (str[i])
	{
		while (str[i] == c)
			i++;
		if (str[i] != c && str[i] != '\0')
			mots++;
		while (str[i] != c && str[i] != '\0')
			i++;
	}
	return (mots);
}

char	**taille_mots(char const *str, char c, char **tab)
{
	int i;
	int mots;
	int taille;

	i = 0;
	taille = 0;
	mots = 0;
	while (str[i])
	{
		while (str[i] == c)
			i++;
		taille = 0;
		while (str[i] != c && str[i] != '\0')
		{
			taille++;
			i++;
		}
		if (!(tab[mots] = malloc(sizeof(char) * taille + 1)))
			return (0);
		mots++;
	}
	return (tab);
}

char	**place_mots(char const *str, char c, char **tab)
{
	int i;
	int mots;
	int taille;

	i = 0;
	taille = 0;
	mots = 0;
	while (str[i])
	{
		while (str[i] == c)
			i++;
		taille = 0;
		while (str[i] != c && str[i] != '\0')
		{
			tab[mots][taille] = str[i];
			taille++;
			i++;
		}
		tab[mots][taille] = '\0';
		mots++;
	}
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	int		nb_mots;
	char	**tab;

	nb_mots = nombre_mots(s, c);
	if (!(tab = malloc(sizeof(char*) * (nb_mots + 1))))
		return (0);
	tab[nb_mots] = NULL;
	taille_mots(s, c, tab);
	place_mots(s, c, tab);
	if (tab[nb_mots] && tab[nb_mots][0] == '\0')
		free(tab[nb_mots]);
	tab[nb_mots] = NULL;
	return (tab);
}
