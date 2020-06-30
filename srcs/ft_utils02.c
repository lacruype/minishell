/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils02.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lacruype <lacruype@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 11:15:34 by lacruype          #+#    #+#             */
/*   Updated: 2020/06/30 14:33:03 by lacruype         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// char	*ft_escape_char(char *str)
// {
// 	int i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '\'')
// 		{
// 			while (str[++i] != '\'')
// 			{
// 				if (str[i] == '\0')
// 					return (0);
// 				if (ft_strchr("$\"\\;|<>", str[i]))
// 					str = ft_putstrstr(str, "\\", i++);
// 			}
// 		}
// 		else if (str[i] == '"')
// 		{
// 			while (str[++i] != '"')
// 			{
// 				if (str[i] == '\0')
// 					return (0);
// 				if (ft_strchr(";|<>", str[i]))
// 					str = ft_putstrstr(str, "\\", i++);
// 			}
// 		}
// 		i++;
// 	}
// 	printf("REND = [%s]\n", str);
// 	return (str);
// }

char        *ft_fake_env(char *cmd, int pos)
{
    int len;
    char *ret;

    len = 0;
    while (!ft_strchr(" ;\"'", cmd[len + pos])&& cmd[len + pos])
        len++;
    ret = calloc(ft_strlen(cmd) - len + 1, sizeof(char));
    ft_memcpy(ret, cmd, pos);
    ft_memcpy(&ret[pos], &cmd[pos + len], ft_strlen(cmd) - (pos + len));
    free(cmd);
    return (ret);
}

char		*ft_cmd_env(char *cmd)
{
	int i;
	int j;
	size_t size;
	size_t len;
	char *new_ptr;
	char *itoa;

	i = 0;
	len = 0;
	while (cmd[i] != '\0')
	{
		
		if (cmd[i] == '$' && cmd[i + 1] != '\0' && cmd[i + 1] != ' ' && cmd[i + 1] != ';')
		{
			size = 0;
			j = 0;
			while (!ft_strchr(" ;\"'", cmd[i + size]) && cmd[i + size])
				size++;
			while (g_envv[j] && ft_strncmp(g_envv[j], &cmd[i + 1], size - 1) != 0)
				j++;
			if (!g_envv[j])
			{

				if (cmd[i + 1] == '?')
				{
					itoa = ft_itoa(exit_status);
					len = ft_strlen(cmd) + ft_strlen(itoa);
					if (!(new_ptr = calloc(len + 1, sizeof(char))))
						return (cmd);
					len = ft_strlen(itoa);
					ft_memcpy(new_ptr, cmd, (size_t)i);
					ft_memcpy(&new_ptr[i], itoa, len + 1);
					ft_memcpy(&new_ptr[i + len], &cmd[i + size], ft_strlen(&cmd[i + size]));
					free(cmd);
					free(itoa);
					cmd = new_ptr;
					// i++;
					continue ;
				}
                cmd = ft_fake_env(cmd, i);
                continue ;
            }
			len = ft_strlen(cmd) + ft_strlen(g_envv[j]) - (size * 2);
			if (!(new_ptr = calloc(len + 1, sizeof(char))))
				return (cmd);
			len = ft_strlen(g_envv[j]) - (size + 1);
			ft_memcpy(new_ptr, cmd, (size_t)i);
			ft_memcpy(&new_ptr[i], &g_envv[j][size], len + 1);
			ft_memcpy(&new_ptr[i + len + 1], &cmd[i + size], ft_strlen(&cmd[i + size]));
			free(cmd);
			cmd = new_ptr;
		}
		i++;
	}
	return (cmd);
}

void    ft_cmd_to_lower(char **cmd)
{
    int i;

    i = 0;
    while ((*cmd)[i])
    {
        (*cmd)[i] = ft_tolower((*cmd)[i]);
        i++;
    }
}