/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils04.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rledrin <rledrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 13:16:06 by lacruype          #+#    #+#             */
/*   Updated: 2020/03/05 16:12:43 by rledrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_cmd_env04(char *cmd, int i, size_t *s, int *j)
{
	while (!ft_strchr(" ;\"$'", cmd[i + *s]) && cmd[i + *s])
		(*s)++;
	while (g_envv[*j])
	{
		if (ft_strncmp(g_envv[*j], &cmd[i + 1], *s - 1) == 0
			&& ft_strchr("=\0", g_envv[*j][*s - 1]) != NULL)
			break ;
		(*j)++;
	}
}

int		single_quote(char *cmd)
{
	int		i;

	i = 0;
	if (cmd[i] == '\'')
	{
		while (1)
		{
			if (!cmd[i++])
				return (0);
			if (cmd[i] == '\'')
				break ;
		}
	}
	return (((i != 0) ? (i - 1) : 0));
}

void	search_function02(char **split_cmd, int i, int *error)
{
	int		size;

	size = 0;
	if ((size = get_size_env(split_cmd)) > 1)
	{
		while (ft_isdigit(split_cmd[1][i]) && split_cmd[1][i])
			i++;
		if (!split_cmd[1][i])
			g_exit_status = ft_atoi(split_cmd[1]);
		else
			*error = -78;
		if (size > 2 && *error == 0)
			*error = -79;
	}
	write(1, "exit\n", 5);
	if (*error == -78 || *error == -79)
		ft_error("exit", split_cmd[1], *error);
}
