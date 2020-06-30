/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing01.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lacruype <lacruype@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 12:31:15 by lacruype          #+#    #+#             */
/*   Updated: 2020/06/30 15:17:02 by lacruype         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_find_env(char *cmd)
{
	int i;
	int j;

	i = 0;
	while (g_envv[i] != NULL)
	{
		j = 0;
		while (g_envv[i][j] != '=' && g_envv[i][j])
			j++;
		if (g_envv[i][j] == '=')
		{
			if (ft_strncmp(cmd, g_envv[i], j) == 0)
				return (g_envv[i]);
			else
				return (NULL);
		}
		i++;
	}
	return (NULL);
}

// char		*ft_cmd_env(char *cmd)
// {
// 	int i;
// 	char *env;

// 	i = 0;
// 	while (cmd[i])
// 	{

// 		if (i >= 1 && cmd[i] == '$' && cmd[i - 1] != '\\')
// 		{
// 			printf("SALUT\n");

// 			if ((env = ft_find_env(&cmd[i])) != NULL)
// 				cmd = ft_putstrstr(cmd, env, i);
// 		}
// 		i++;
// 	}
// 	return (cmd);
// }

char	*ft_strchr(const char *str, int c)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] != (char)c)
		i++;
	if (str[i] != (char)c)
		return (NULL);
	return ((char*)(str + i));
}

int		ft_double_op(char *cmd)
{
	int		i;
	char	*tmp1;
	char	*tmp2;
	char	*op;

	op = (char[3]){";|"};
	i = 0;
	while (cmd[i])
	{
		if ((i = ft_check_quotes_closed(cmd, i)) == -1)
			return (ft_error("Minishell", "", -4));
		if (cmd[i] != '\0' && (tmp1 = ft_strchr(op, cmd[i])) != NULL
			&& (tmp2 = ft_strchr(op, cmd[i + 1])) != NULL)
		{
			if (*tmp1 == *tmp2 && *tmp1 == ';')
				ft_error("Minishell", ";;", -10);
			else if (*tmp1 == *tmp2 && *tmp1 == '|')
				ft_error("Minishell", "||", -10);
			else if (*tmp1 == ';')
				ft_error("Minishell", ";", -10);
			else
				ft_error("Minishell", "|", -10);
			return (-1);
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
	if ((tmp = ft_cmd_env(command_line)) == NULL)
	{
		free(tmp);
		return (NULL);
	}
	return (tmp);
}
