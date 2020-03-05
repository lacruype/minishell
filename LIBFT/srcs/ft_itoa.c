/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rledrin <rledrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 13:43:13 by lacruype          #+#    #+#             */
/*   Updated: 2020/03/05 16:12:43 by rledrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int		ft_strl(int n)
{
	int i;

	i = 0;
	while (n > 9)
	{
		n /= 10;
		i++;
	}
	return (i + 1);
}

void	ft_reverse(char *str, int n)
{
	int		i;
	char	c;

	i = 0;
	while (i < n)
	{
		c = str[i];
		str[i] = str[n];
		str[n] = c;
		i++;
		n--;
	}
}

int		ft_boucle(int n, int taille, char *str)
{
	int i;

	i = 0;
	while (i != taille)
	{
		str[i++] = (n % 10) + '0';
		n /= 10;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int		i;
	int		is_neg;
	char	*str;
	int		taille;

	i = 0;
	is_neg = 0;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	else if (n < 0)
	{
		is_neg = 1;
		n = -n;
	}
	taille = ft_strl(n);
	if (!(str = malloc(sizeof(char) * taille + 1 + is_neg)))
		return (0);
	i = ft_boucle(n, taille, str);
	if (is_neg == 1)
		str[i++] = '-';
	str[i] = '\0';
	ft_reverse(str, taille + is_neg - 1);
	return (str);
}
