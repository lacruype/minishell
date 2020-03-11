/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rledrin <rledrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 14:51:52 by rledrin           #+#    #+#             */
/*   Updated: 2020/03/11 12:03:21 by rledrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			ft_nb_word(char *cmd)
{
	int		i;
	int		word;

	i = 0;
	word = 0;

	while (cmd[i] && !ft_strchr("<>|", cmd[i]))
	{
		while (cmd[i] == ' ' && cmd[i])
			i++;
		if (!ft_strchr("<>|", cmd[i]) && cmd[i])
			word++;
		while (cmd[i] != ' ' && cmd[i] && !ft_strchr("<>|", cmd[i]))
			i++;
	}
	return (word);
}

char		**ft_fill(char **cmd_split, char *cmd)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	j = -1;
	while (cmd[i] && !ft_strchr("<>|", cmd[i]))
	{
		k = 0;
		while (cmd[i] == ' ')
			i++;
		if (!ft_strchr("<>|", cmd[i]) && cmd[i])
			j++;
		while (cmd[i] != ' ' && cmd[i] && !ft_strchr("<>|", cmd[i]))
		{
			i++;
			k++;
		}
		if (!cmd_split[j])
		{
			cmd_split[j] = ft_calloc(k + 1, sizeof(char));
			ft_memcpy(cmd_split[j], &cmd[i - k], k);
			cmd_split[j][k] = '\0';
		}
	}
	return (cmd_split);
}

char		**ft_split_cmd(char *cmd)
{
	char	**cmd_split;
	int		size;
	
	cmd_split = 0;
	size = ft_nb_word(cmd);
	cmd_split = ft_calloc(size + 2 , sizeof(char*));
	cmd_split = ft_fill(cmd_split, cmd);
	cmd_split[size] = 0;
	return (cmd_split);
}
