/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lacruype <lacruype@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 12:31:15 by lacruype          #+#    #+#             */
/*   Updated: 2020/07/01 14:52:28 by lacruype         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_double_op(char *cmd)
{
	int		i;
	char	*tmp1;
	char	*tmp2;

	i = 0;
	while (cmd[i])
	{
		if ((i = ft_check_quotes_closed(cmd, i)) == -1)
			return (ft_error("Minishell", "", -4));
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
		i++;
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