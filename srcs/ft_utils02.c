/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils02.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rledrin <rledrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 11:15:34 by lacruype          #+#    #+#             */
/*   Updated: 2020/02/12 14:30:31 by rledrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char		*quote(char *cmd)
{
	int		i;

	i = 0;
	if (cmd[i] == '\'')
	{
		while (1)
		{
			if (!cmd[i++])
				return (NULL);
			if (cmd[i] == '\'')
				break ;
		}
	}
	if (cmd[i] == '"')
	{
		while (1)
		{
			if (!cmd[i++])
				return (NULL);
			if (cmd[i] == '"')
				break;
		}
	}
	if (i != 0)
		return(&cmd[i]);
	return (NULL);
}

static int		nombre_mots(char const *str, char c)
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
		{
			i++;
		}
	}
	printf("NB_MOTS = [%d]\n", mots);
	return (mots);
}

static char	**taille_mots(char const *str, char c, char **tab)
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

static char	**place_mots(char const *str, char c, char **tab)
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

char	**ft_split_semicolon(char const *s, char c)
{
	int		i;
	int		nb_mots;
	char	**tab;

	i = 0;
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

int main(int ac, char **av)
{
	char **tab;
	int i;

	i = 0;
	if (ac != 2)
	{
		printf("Il me faut 2 arguments !\n");
		return (0);
	}
	tab = ft_split_semicolon(av[1], ';');
	while (tab[i])
	{
		printf("tab[%d] = [%s]\n", i, tab[i]);
		free(tab[i]);
		i++;
	}
	free(tab);
	return (0);
}