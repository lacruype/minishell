/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_escape_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lacruype <lacruype@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 14:24:07 by lacruype          #+#    #+#             */
/*   Updated: 2020/02/17 16:32:25 by lacruype         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_putstr_in_str(char *s1, char *s2, int pos)
{
	int		i;
	int		j;
	int		k;
	size_t	len;
	char	*dest;

	i = 0;
	j = 0;
	k = 0;
	len = ft_strlen(s1) + ft_strlen(s2);
	if (!(dest = malloc(sizeof(char) * (len + 1))) || pos > (int)len)
		return (0);
	while (s1[i])
	{
		if (i == pos)
			while (s2[j])
				dest[k++] = s2[j++];
		dest[k++] = s1[i++];
	}
	dest[k] = '\0';
	free(s1);
	return (dest);
}

int		jump_quotes(const char *str, int i)
{
	if (str[i] == '\'')
	{
		while (str[++i] != '\'')
		{
			if (str[i] == '\0')
				return (-1);
		}
	}
	else if (str[i] == '"')
	{
		while (str[++i] != '"')
		{
			if (str[i] == '\0')
				return (-1);
		}
	}
	return (i);
}

char	*ft_escape_char(char *str)
{
	int i;
	int q;
	int d_q;
	
	i = 0;
	q = 0;
	d_q = 0;
	// while (str[i])
	// {
	// 	if (str[i] == '"' && d_q == 1)
	// 		d_q = 0;
	// 	else if (str[i] == '"')
	// 		d_q = 1;
	// 	else if (str[i] == '\'' && q == 1)
	// 		q = 0;
	// 	else if (str[i] == '\'')
	// 		q = 1;
	// 	else if (ft_strchr("$\"\\;|<>", str[i]) && q == 1)
	// 		str = ft_putstrstr(str, "\\", i++);
	// 	else if (ft_strchr(";|<>", str[i]) && d_q == 1)
	// 		str = ft_putstrstr(str, "\\", i++);
	// 	i++;
	// }

	while (str[i])
	{
		if (str[i] == '\'')
		{
			while (str[++i] != '\'')
			{
				if (str[i] == '\0')
					return (0);
				if (ft_strchr("$\"\\;|<>", str[i]))
					str = ft_putstrstr(str, "\\", i++);
			}
		}
		else if (str[i] == '"')
		{
			while (str[++i] != '"')
			{
				if (str[i] == '\0')
					return (0);
				if (ft_strchr(";|<>", str[i]))
					str = ft_putstrstr(str, "\\", i++);
			}
		}
		i++;
	}




















	return (str);
}

int main(int ac, char **av)
{
	// if (ac != 2)
	// {
	// 	printf("Arguments !\n");
	// 	return (0);
	// }
	char *str = ft_strdup("\' $ ; | < > \\ \'");
	char *ret;

	ret = ft_escape_char(str);
	printf("RET = [%s]\n", ret);
}