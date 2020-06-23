/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tot.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lacruype <lacruype@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 08:31:47 by lacruype          #+#    #+#             */
/*   Updated: 2020/06/17 17:13:58 by lacruype         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static int		nb_words_semicolon(char const *str, char c)
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
			while (str[i] && str[i] != '"' && str[i - 1] != '\\')
				i++;
			i++;
		}
		else if ((str[i] == '\'' && i == 0) || (str[i] == '\'' && str[i - 1] != '\\'))
		{
			i++;
			while (str[i] && str[i] != '\'' && str[i - 1] != '\\')
				i++;
			i++;
		}
		else if (str[i] == c)
		{
			while (str[i] == c && str[i])
            {
                if ((str[i] == '"' && str[i - 1] != '\\') || (str[i] == '\'' && str[i - 1] != '\\'))
                    break ;
                i++;
            }
			if (str[i])
				words++;
		}
		else
	   		i++;
	}
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
    while (str[i] == c)
        i++;
	while (str[i])
	{
		if ((str[i] == '"' && i == 0) || (str[i] == '"' && str[i - 1] != '\\'))
		{
			i++;
			while (str[i] && str[i] != '"' && str[i - 1] != '\\')
			{
				taille++;
				i++;
			}
			i++;
		}
		else if ((str[i] == '\'' && i == 0) || (str[i] == '\'' && str[i - 1] != '\\'))
		{
			i++;
			while (str[i] && str[i] != '\'' && str[i - 1] != '\\')
			{
				taille++;
				i++;
			}
			i++;
		}
		else if (str[i] == c)
		{
			while (str[i] == c && str[i])
            {
                if ((str[i] == '"' && str[i - 1] != '\\') || (str[i] == '\'' && str[i - 1] != '\\'))
                    break ;
                i++;
            }
			if (str[i])
			{
            	if (!(tab[words] = ft_calloc((taille + 1), sizeof(char))))
					return (0);
				words++;
				taille = 0;
			}
		}
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

static char		**place_words_semicolon(char const *str, char c, char **tab)
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
			while (str[i] && str[i] != '"' && str[i - 1] != '\\')
			{
				tab[words][taille] = str[i];
				taille++;
				i++;
			}
			i++;
		}
		else if ((str[i] == '\'' && i == 0) || (str[i] == '\'' && str[i - 1] != '\\'))
		{
			i++;
			while (str[i] && str[i] != '\'' && str[i - 1] != '\\')
			{
				tab[words][taille] = str[i];
				taille++;
				i++;
			}
			i++;
		}
		else if (str[i] == c)
		{
			while (str[i] == c && str[i])
            {
                if ((str[i] == '"' && str[i - 1] != '\\') || (str[i] == '\'' && str[i - 1] != '\\'))
                    break ;
                i++;
            }
			if (str[i])
			{
				tab[words][taille] = '\0';
				words++;
				taille = 0;
			}
		}
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

char		**ft_split_semicolon(char const *s, char c)
{
	int		i;
	int		nb_words;
	char	**tab;

	i = 0;
	printf("LE TRUC = [%s]\n", s);
	nb_words = nb_words_semicolon(s, c);
	if (!(tab = ft_calloc((nb_words + 1), sizeof(char*))))
		return (0);
	tab[nb_words] = NULL;
	size_words_semicolon(s, c, tab);
	place_words_semicolon(s, c, tab);
	if (tab[nb_words] && tab[nb_words][0] == '\0')
		free(tab[nb_words]);
	tab[nb_words] = NULL;
	return (tab);
}

int main(int ac, char **av)
{
    char **ret;

    ret = ft_split_semicolon(av[1], ' ');
    for(int j = 0; ret[j] != NULL; j++)
    printf("[%s]\n", ret[j]);
    return (0);
}