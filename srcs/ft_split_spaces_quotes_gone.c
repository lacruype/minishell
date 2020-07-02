/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_spaces_quotes_gone.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lacruype <lacruype@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/19 14:32:07 by lacruype          #+#    #+#             */
/*   Updated: 2020/07/02 16:40:10 by lacruype         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	int		nb_word_ssqg(char const *str, char c)
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
		{
			i++;
			while (str[i])
			{
				if (str[i] == '\\' && str[i - 1] != '\\')
					i++;
				if (str[i] == '"')
					if (str[i - 1] != '\\')
						break ;
				i++;
			}
		}
		else if ((str[i] == '\'' && i == 0)
			|| (str[i] == '\'' && str[i - 1] != '\\'))
		{
			i++;
			while (str[i])
			{
				if (str[i] == '\'')
					if (str[i - 1] != '\\')
						break ;
				i++;
			}
		}
		else if (str[i] == c)
		{
			while (str[i] == c && str[i])
				i++;
			if (str[i])
			{
				words++;
				continue ;
			}
		}
		else
			i++;
		if (((str[i] == '"' || str[i] == '\'') && str[i - 1] != '\\')
			|| (str[i] == '\\' && str[i - 1] != '\\'))
			i++;
	}
	return (words);
}

static	char	**size_ssqg(char const *str, char c, char **tab)
{
	int i;
	int words;
	int taille;
	int len;

	i = 0;
	taille = 0;
	words = 0;
	len = ft_strlen_gnl((char*)str);
	while (str[i] == c)
		i++;
	while (str[i] && i <= len)
	{
		if ((str[i] == '"' && i == 0) || (str[i] == '"' && str[i - 1] != '\\'))
		{
			i++;
			while (str[i])
			{
				if (str[i] == '\\' && str[i - 1] != '\\')
					i++;
				if (str[i] == '"')
					if (str[i - 1] != '\\')
						break ;
				taille++;
				i++;
			}
		}
		else if ((str[i] == '\'' && i == 0)
			|| (str[i] == '\'' && str[i - 1] != '\\'))
		{
			i++;
			while (str[i])
			{
				if (str[i] == '\\' && str[i - 1] != '\\')
					i++;
				if (str[i] == '\'')
					if (str[i - 1] != '\\')
						break ;
				taille++;
				i++;
			}
		}
		else if (str[i] == c)
		{
			while (str[i] == c && str[i])
				i++;
			if (str[i])
			{
				if (!(tab[words] = ft_calloc((taille + 1), sizeof(char))))
					return (0);
				words++;
				taille = 0;
				continue ;
			}
		}
		else if (((str[i] == '"' || str[i] == '\'') && str[i - 1] != '\\')
			|| (str[i] == '\\' && str[i - 1] != '\\'))
			i++;
		else
		{
			i++;
			taille++;
		}
	}
	if (!(tab[words] = ft_calloc((taille + 1), sizeof(char))))
		return (0);
	return (tab);
}

static	char	**place_ssqg(char const *str, char c, char **tab)
{
	int i;
	int words;
	int taille;

	i = 0;
	taille = 0;
	words = 0;
	while (str[i] == c)
		i++;
	while (str[i])
	{
		if ((str[i] == '"' && i == 0) || (str[i] == '"' && str[i - 1] != '\\'))
		{
			i++;
			while (str[i])
			{
				if (str[i] == '\\' && str[i - 1] != '\\')
					i++;
				if (str[i] == '"')
					if (str[i - 1] != '\\')
						break ;
				tab[words][taille] = str[i];
				taille++;
				i++;
			}
		}
		else if ((str[i] == '\'' && i == 0)
			|| (str[i] == '\'' && str[i - 1] != '\\'))
		{
			i++;
			while (str[i])
			{
				if (str[i] == '\\' && str[i - 1] != '\\')
					i++;
				if (str[i] == '\'')
					if (str[i - 1] != '\\')
						break ;
				tab[words][taille] = str[i];
				taille++;
				i++;
			}
		}
		else if (str[i] == c)
		{
			while (str[i] == c && str[i])
				i++;
			if (str[i])
			{
				tab[words][taille] = '\0';
				words++;
				taille = 0;
				continue ;
			}
		}
		else if (((str[i] == '"' || str[i] == '\'') && str[i - 1] != '\\')
			|| (str[i] == '\\' && str[i - 1] != '\\'))
			i++;
		else
		{
			tab[words][taille] = str[i];
			i++;
			taille++;
		}
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
