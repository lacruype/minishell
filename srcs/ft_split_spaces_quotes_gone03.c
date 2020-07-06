/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_spaces_quotes_gone03.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lacruype <lacruype@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 13:12:23 by lacruype          #+#    #+#             */
/*   Updated: 2020/07/06 16:39:30 by lacruype         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	int		size_ssqg04(char **tab, int *taille, int *words, char comp)
{
	if (comp != '\0')
	{
		if (!(tab[*words] = ft_calloc((*taille + 1), sizeof(char))))
			return (0);
		(*words)++;
		(*taille) = 0;
		return (1);
	}
	return (0);
}

static	void	size_ssqg03(char const *str, int *i, int *taille)
{
	if (((str[*i] == '"' || str[*i] == '\'') && str[*i - 1] != '\\')
		|| (str[*i] == '\\' && str[*i - 1] != '\\'))
		(*i)++;
	else
	{
		(*i)++;
		(*taille)++;
	}
}

static	int		size_ssqg02(char const *str, int *i, int *taille)
{
	if ((str[*i] == '"' && *i == 0) || (str[*i] == '"' && str[*i - 1] != '\\'))
		while (str[++(*i)])
		{
			if (str[*i] == '\\' && str[*i - 1] != '\\')
				(*i)++;
			if (str[*i] == '"')
				if (str[*i - 1] != '\\')
					break ;
			(*taille)++;
		}
	else if ((str[*i] == '\'' && *i == 0)
		|| (str[*i] == '\'' && str[*i - 1] != '\\'))
		while (str[++(*i)])
		{
			if (str[*i] == '\\' && str[*i - 1] != '\\')
				(*i)++;
			if (str[*i] == '\'')
				if (str[*i - 1] != '\\')
					break ;
			(*taille)++;
		}
	else
		return (0);
	return (1);
}

char			**size_ssqg(char const *str, char c, char **tab)
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
		if (size_ssqg02(str, &i, &taille) == 1)
			continue ;
		else if (str[i] == c)
		{
			while (str[i] == c && str[i])
				i++;
			if (size_ssqg04(tab, &taille, &words, str[i]) == 1)
				continue ;
		}
		else
			size_ssqg03(str, &i, &taille);
	}
	return ((tab[words] = (ft_calloc((taille + 1), sizeof(char)))) ? tab : 0);
}
