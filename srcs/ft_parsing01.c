/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing01.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lacruype <lacruype@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 12:31:15 by lacruype          #+#    #+#             */
/*   Updated: 2020/02/20 14:52:23 by lacruype         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// static char		*ft_cmd_env(char *cmd)
// {
// 	int i;
// 	int j;
// 	int k;
// 	size_t size;
// 	size_t len;
// 	char *new_ptr;

// 	i = 0;
// 	j = 0;
// 	k = 0;
// 	size = 0;
// 	len = 0;
// 	while (cmd[i])
// 	{	
// 		while (1)
// 		{
// 			if (cmd[i] == '$' && cmd[i + 1] != '\0' && cmd[i + 1] != ' ' && cmd[i + 1] != ';')
// 			{
// 				while (!ft_strchr(" ;\"'", cmd[i + size])&& cmd[i + size])
// 					size++;
// 				while (g_envv[j] && ft_strncmp(g_envv[j], &cmd[i + 1], size - 1) != 0)
// 					j++;
// 				if (!g_envv[j])
// 					return (cmd);
// 				len = ft_strlen(cmd) + ft_strlen(g_envv[j]) - ((size + 1) * 2);
// 				if (!(new_ptr = calloc(len + 1, sizeof(char))))
// 					return (cmd);
// 				len = ft_strlen(g_envv[j]) - (size + 1);
// 				ft_memcpy(new_ptr, cmd, (size_t)i);
// 				ft_memcpy(&new_ptr[i], &g_envv[j][size], len + 1);
// 				ft_memcpy(&new_ptr[i + len + 1], &cmd[i + size], strlen(&cmd[i +size]));
// 				free(cmd);
// 				cmd = new_ptr;
// 			}
// 			i++;
// 			if (cmd[i] == '\0')
// 				break ;
// 		}
// 	}
// 	return (cmd);
// }

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

static char		*ft_cmd_env(char *cmd)
{
	int i;
	char *env;

	i = 0;
	while (cmd[i])
	{
		if (i >= 1 && cmd[i] == '$' && cmd[i - 1] != '\\')
		{
			if ((env = ft_find_env(&cmd[i])) != NULL)
				cmd = ft_putstrstr(cmd, env, i);
		}
		i++;
	}
	return (cmd);
}

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

int 	ft_double_op(char *cmd)
{
	int i;
	char *op;

	op = (char[3]){";|"};
	i = 0;
	while (cmd[i])
	{
		if ((i = jump_quotes(cmd, i)) == -1)
			return (-1);
		if (cmd[i] != '\0' && ft_strchr(op, cmd[i]) != NULL && ft_strchr(op, cmd[i + 1]) != NULL)
			return (-1);
		i++;
	}
	return (0);
}

char		*ft_parsing(char *command_line)
{
	char *tmp;

	tmp = command_line;
	if (ft_double_op(command_line) == -1)
		return (NULL);
	if ((command_line = ft_escape_char(command_line)) == NULL)
	{
		free(tmp);
		return (NULL);
	}
	if ((tmp = ft_cmd_env(command_line)) == NULL)
	{
		free(tmp);
		return (NULL);
	}
	return (tmp);
}
