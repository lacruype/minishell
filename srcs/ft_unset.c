/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lacruype <lacruype@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 13:52:16 by lacruype          #+#    #+#             */
/*   Updated: 2020/07/01 16:28:35 by lacruype         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char		**ft_delete_env(char **tab, int i)
{
	int		size;
	char	**ret;
	int		j;
	int		k;

	j = 0;
	k = 0;
	size = get_size_env(tab);
	if (!(ret = ft_calloc(size, sizeof(char*))))
		return (NULL);
	while (tab[j] != NULL)
	{
		if (j == i)
			j++;
		if (tab[j] != NULL)
			ret[k++] = tab[j++];
	}
	ret[k] = NULL;
	free(tab[i]);
	free(tab);
	return (ret);
}

void			ft_unset(char **args)
{
	int i;
	int j;
	int len;

	i = 1;
	while (args[i] != NULL)
	{
		j = 0;
		while (g_envv[j] != NULL)
		{
			len = ft_strlen(args[i]);
			if (ft_strncmp(args[i], g_envv[j],
				len - 1) == 0 && g_envv[j][len] == '=')
				g_envv = ft_delete_env(g_envv, j);
			if (g_envv[j] != NULL)
				j++;
		}
		i++;
	}
}
