/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lacruype <lacruype@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 12:31:15 by lacruype          #+#    #+#             */
/*   Updated: 2020/07/06 16:39:00 by lacruype         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	char	*ft_double_op02(char *cmd, int *i)
{
	char *ret;

	while (cmd[++(*i)])
	{
		if (cmd[*i] == ' ')
			continue ;
		else if ((ret = ft_strchr("<>|;", cmd[*i])) != NULL)
			return (ft_substr(ret, 0, 1));
		else
			return (NULL);
	}
	return (NULL);
}

static	int		ft_double_op(char *cmd)
{
	int		i;
	char	*tmp1;

	i = -1;
	while (cmd[++i])
	{
		if ((i = ft_check_quotes_closed(cmd, i)) == -1)
			return (ft_error("Minishell", "", -4));
		else if (cmd[i] && cmd[i] == '>' && cmd[i + 1] == '>')
			continue ;
		else if (ft_strchr(";|<>", cmd[i]))
		{
			if ((tmp1 = ft_double_op02(cmd, &i)) != NULL)
			{
				ft_error("Minishell", tmp1, -10);
				free(tmp1);
				return (-1);
			}
		}
		if (cmd[i] == '\0')
			return (0);
	}
	return (0);
}

char			*ft_parsing(char *command_line)
{
	char *tmp;

	tmp = command_line;
	if (command_line && ft_double_op(command_line) == -1)
	{
		free(tmp);
		return (NULL);
	}
	if ((tmp = ft_cmd_env(command_line, -1)) == NULL)
	{
		free(tmp);
		return (NULL);
	}
	return (tmp);
}
