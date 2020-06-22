/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lacruype <lacruype@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 14:51:52 by rledrin           #+#    #+#             */
/*   Updated: 2020/06/22 13:42:05 by lacruype         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char		**ft_split_redir(char *cmd)
{
	int i;
	char	*stock;
	char	**stock2;

	i = 0;
	while (cmd[i])
	{
		if ((i = (ft_check_quotes_closed(cmd, i))) == -1)
			return (NULL);
		else if (ft_strchr("<>|", cmd[i]) && cmd[i - 1] != '\\')
		{
			stock = ft_substr_gnl(cmd, 0, i);
			stock2 = ft_split_spaces_quotes_gone(stock, ' ');
			free(stock);
			return (stock2);
		}
		else
			i++;
	}
	return (ft_split_spaces_quotes_gone(cmd, ' '));
}