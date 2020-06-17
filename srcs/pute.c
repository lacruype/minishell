/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lacruype <lacruype@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 14:51:52 by rledrin           #+#    #+#             */
/*   Updated: 2020/03/11 16:52:36 by lacruype         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <limits.h>
#include <dirent.h>
#include "../libft/includes/libft.h"

int	ft_are_quotes_closed(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if ((i > 0 && str[i] == '"' && str[i - 1] != '\\') || (str[i] == '"' && i == 0))
		{
			i++;
			while ((str[i] != '"' && str[i] != '\0') || str[i - 1] == '\\')
				i++;
			if (str[i] == '\0')
				return (-1);
			i++;
		}
		else if ((i > 0 && str[i] == '\'' && str[i - 1] != '\\') || (str[i] == '\'' && i == 0))
		{
			i++;
			while ((str[i] != '\'' && str[i] != '\0') || str[i - 1] == '\\')
				i++;
			if (str[i] == '\0')
				return (-1);
			i++;
		}
		else
			i++;
	}
	return (i);
}

static int	ft_is_quotes(char *str,int i)
{
	while (str[i])
	{
		if ((i > 0 && str[i] == '"' && str[i - 1] != '\\') || (str[i] == '"' && i == 0))
		{
			i++;
			while ((str[i] != '"' && str[i] != '\0') || str[i - 1] == '\\')
				i++;
			i++;
		}
		else if ((i > 0 && str[i] == '\'' && str[i - 1] != '\\') || (str[i] == '\'' && i == 0))
		{
			i++;
			while ((str[i] != '\'' && str[i] != '\0') || str[i - 1] == '\\')
				i++;
			i++;
		}
		else
			i++;
	}
	return (i);
}

static int	ft_is_quotes_with_size(char *str,int i, int *size)
{
	if ((i > 0 && str[i] == '"' && str[i - 1] != '\\') || (str[i] == '"' && i == 0))
	{
		i++;
		(*size)++;
		while ((str[i] != '"' && str[i] != '\0') || str[i - 1] == '\\')
		{
			(*size)++;
			i++;
		}
		i++;
		printf("size d'un mot in quotes = %d\n", *size);
	}
	else if ((i > 0 && str[i] == '\'' && str[i - 1] != '\\') || (str[i] == '\'' && i == 0))
	{
		i++;
		(*size)++;
		while ((str[i] != '\'' && str[i] != '\0') || str[i - 1] == '\\')
		{
			(*size)++;
			i++;
		}
		i++;
		printf("size d'un mot in quotes = %d\n", *size);
	}
	return (i);
}

static int	ft_is_quotes_with_place(char *str,int i, int *size, char *tab)
{
	if ((i > 0 && str[i] == '"' && str[i - 1] != '\\') || (str[i] == '"' && i == 0))
	{
		i++;
		while ((str[i] != '"' && str[i] != '\0') || str[i - 1] == '\\')
		{
			tab[(*size)] = str[i];
			(*size)++;
			i++;
		}
		i++;
	}
	else if ((i > 0 && str[i] == '\'' && str[i - 1] != '\\') || (str[i] == '\'' && i == 0))
	{
		i++;
		while ((str[i] != '\'' && str[i] != '\0') || str[i - 1] == '\\')
		{
			tab[(*size)] = str[i];
			(*size)++;
			i++;
		}
		i++;
	}
	return (i);
}

char	**ft_place_words_cmd(char *str, char **tab)
{
	int i;
	int tmp;
	int size;
	int words;

	i = 0;
	words = 0;
	while (str[i])
	{
		size = 0;
		tmp = i;
		if (str[i] == ' ')
			i++;
		else if (tmp < (i = ft_is_quotes_with_place(str, i, &size, tab[words])))
			words++;
		else if (str[i])
		{
			while (str[i] && str[i] != ' ' && str[i] != '"' && str[i] != '\'')
			{
				tab[words][size] = str[i];
				size++;
				i++;
			}
			words++;
		}
	}
	return (tab);
}

char	**ft_size_words_cmd(char *str, char **tab)
{
	int i;
	int tmp;
	int size;
	int words;

	i = 0;
	words = 0;
	while (str[i])
	{
		size = 0;
		tmp = i;
		if (str[i] == ' ')
			i++;
		else if (((i > 0 && str[i] == '"' && str[i - 1] != '\\') || (str[i] == '"' && i == 0))
				|| ((i > 0 && str[i] == '\'' && str[i - 1] != '\\') || (str[i] == '\'' && i == 0)))
		{
			i = ft_is_quotes_with_size(str, i, &size);
			if (!(tab[words] = ft_calloc(sizeof(char), (size + 1))))
				return (NULL);
			words++;
		}
		else if (str[i])
		{
			while (str[i] && str[i] != ' ' && (str[i] != '"' || str[i] != '\'') && str[i - 1] == '\\')
			{
				size++;
				i++;
			}
			printf("i = %d\nsize d'un mot hors quotes = %d\n", i, size);
			if (!(tab[words] = ft_calloc(sizeof(char), (size + 1))))
				return (NULL);
			words++;
		}
	}
	return (tab);
}

static int	ft_nb_words_cmd(char *str)
{
	int i;
	int tmp;
	int words;

	i = 0;
	words = 0;
	while (str[i])
	{
		tmp = i;
		if (str[i] == ' ')
			i++;
		else if (tmp < (i = ft_is_quotes(str, i)))
			words++;
		else if (str[i])
		{
			words++;
			while (str[i] && str[i] != ' ' && str[i] != '"' && str[i] != '\'')
				i++;
		}
	}
	return (words);
}

char		**ft_split_cmd(char *str)
{
	int		i;
	int		nb_words;
	char	**tab;

	i = 0;
	if (ft_are_quotes_closed(str) == -1)
	{
		ft_error(2);
		return(NULL);
	}
	nb_words = ft_nb_words_cmd(str);
	if (!(tab = malloc(sizeof(char*) * (nb_words + 1))))
		return (0);
	tab[nb_words] = NULL;
	tab = ft_size_words_cmd(str, tab);
	tab = ft_place_words_cmd(str, tab);
	// if (tab[nb_words] && tab[nb_words][0] == '\0')
	// 	free(tab[nb_words]);
	// tab[nb_words] = NULL;
	// for (int j = 0; tab[j] != NULL; j++)
	// 	printf("[%s]\n", tab[j]);
	return (tab);
}

int		ft_error(int error)
{
	ft_putstr_fd("Minishell : ", 1);
	if (error == 0)
		ft_putstr_fd("Quotes not closed !\n", 1);
	else if (error == 1)
		ft_putstr_fd("syntax error near unexpected token\n", 1);
	else if (error == 2)
		ft_putstr_fd("Quote is not closed !\n", 1);
	else if (error == 3)
		ft_putstr_fd("Didn't find the $? !\n", 1);
	else if (error == 4)
		ft_putstr_fd("Escaping chars has failed !\n", 1);
	else if (error == 5)
		ft_putstr_fd("Command doesn't exit !\n", 1);
	return (-1);
}

int main(int ac, char **av)
{
	char **tab;
	char *str;
	if (ac < 0 || ac > 2)
		return (0);
	str = ft_strdup(av[1]);
	if (ft_are_quotes_closed(str) == -1)
	{
		printf("QUOTES ARE NOT CLOSED\n");
		return (-1);
	}
	printf("QUOTES ARE CLOSED\n");
	tab = ft_split_cmd(str);
	// tab = ft_split_char(str, ' ');
	for(int i = 0; tab[i] != NULL; i++)
		printf("tab[%d] = [%s]\n", i, tab[i]);
	// free(str);
	return (0);
}
