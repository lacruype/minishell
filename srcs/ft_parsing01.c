/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing01.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 12:31:15 by lacruype          #+#    #+#             */
/*   Updated: 2020/02/13 12:15:16 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char		*ft_cmd_env(char *cmd)
{
	int i;
	int j;
	int k;
	size_t size;
	size_t len;
	char *new_ptr;

	i = 0;
	j = 0;
	k = 0;
	size = 0;
	len = 0;
	while (cmd[i])
	{	
		while (1)
		{
			if (cmd[i] == '$' && cmd[i + 1] != '\0' && cmd[i + 1] != ' ' && cmd[i + 1] != ';')
			{
				while (!ft_strchr(" ;\"'", cmd[i + size])&& cmd[i + size])
					size++;
				printf("SIZE = [%zu]\n", size);
				while (g_envv[j] && ft_strncmp(g_envv[j], &cmd[i + 1], size - 1) != 0)
					j++;
				if (!g_envv[j])
					return (cmd);
				printf("HAHA = [%s]\nHEHE = [%s]\n", cmd, g_envv[j]);
				len = ft_strlen(cmd) + ft_strlen(g_envv[j]) - ((size + 1) * 2);
				if (!(new_ptr = calloc(len + 1, sizeof(char))))
					return (cmd);
				len = ft_strlen(g_envv[j]) - (size + 1);
				ft_memcpy(new_ptr, cmd, (size_t)i);
				//ft_putstr(cmd);
				printf("CMD1 = [%s]\n", new_ptr);
				ft_memcpy(&new_ptr[i], &g_envv[j][size], len + 1);
				printf("CMD2 = [%s]\n", new_ptr);
				ft_memcpy(&new_ptr[i + len + 1], &cmd[i + size], strlen(&cmd[i +size]));
				free(cmd);
				cmd = new_ptr;
			}
			i++;
			if (cmd[i] == '\0')
				break ;
		}
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
	// else if (str[i] == '"')
	// {
	// 	while (str[++i] != '"')
	// 	{
	// 		if (str[i] == '\0')
	// 			return (-1);
	// 	}
	// }
	return (i);
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
		if (cmd[i + 1] != '\0' && ft_strchr(op, cmd[i]) != NULL && ft_strchr(op, cmd[i + 1]) != NULL)
			return (-1);
		i++;
	}
	return (0);
}


int		ft_parsing(char **command_line)
{
	if (ft_double_op(*command_line) == -1)
		ft_error(1);
	*command_line = ft_cmd_env(*command_line);
	if (*command_line)
		printf("CMD3 = [%s]\n", *command_line);
	return (0);
}
