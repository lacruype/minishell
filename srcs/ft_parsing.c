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

static	int	ft_check_double_semi(char *cmd, int i)
{
	i++;
	while (cmd[i])
	{
		if (cmd[i] == ' ')
			i++;
		else if (cmd[i] == ';' || cmd[i] == '|')
			return (-1);
		else
			return (0);
	}
	return (0);
}

static int	ft_double_op(char *cmd)
{
	int		i;
	char	*tmp1;
	char	*tmp2;

	i = -1;
	while (cmd[++i])
	{
		if ((i = ft_check_quotes_closed(cmd, i)) == -1)
			return (ft_error("Minishell", "", -4));
		if (ft_strchr(";|", cmd[i]) && ft_check_double_semi(cmd, i) == -1)
			return (ft_error("Minishell", ";", -10));
		if (cmd[i] != '\0' && (tmp1 = ft_strchr(";|", cmd[i])) != NULL
			&& (tmp2 = ft_strchr(";|", cmd[i + 1])) != NULL)
		{
			if (*tmp1 == *tmp2 && *tmp1 == ';')
				return (ft_error("Minishell", ";;", -10));
			else if (*tmp1 == *tmp2 && *tmp1 == '|')
				return (ft_error("Minishell", "||", -10));
			else if (*tmp1 == ';')
				return (ft_error("Minishell", ";", -10));
			else
				return (ft_error("Minishell", "|", -10));
		}
	}
	return (0);
}

char		*ft_parsing(char *command_line)
{
	char *tmp;

	tmp = command_line;
	if (command_line && ft_double_op(command_line) == -1)
		return (NULL);
	if ((tmp = ft_cmd_env(command_line, -1)) == NULL)
	{
		free(tmp);
		return (NULL);
	}
	return (tmp);
}
