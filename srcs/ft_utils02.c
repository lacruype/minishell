/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils02.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lacruype <lacruype@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 11:15:34 by lacruype          #+#    #+#             */
/*   Updated: 2020/07/06 16:43:39 by lacruype         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char		*ft_fake_env(char *cmd, int pos)
{
	int		len;
	char	*ret;

	len = 1;
	while (!ft_strchr(" ;\"$'", cmd[len + pos]) && cmd[len + pos])
		len++;
	ret = calloc(ft_strlen(cmd) - len + 1, sizeof(char));
	ft_memcpy(ret, cmd, pos);
	ft_memcpy(&ret[pos], &cmd[pos + len], ft_strlen(cmd) - (pos + len));
	free(cmd);
	return (ret);
}

char			*ft_cmd_to_lower(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		cmd[i] = ft_tolower(cmd[i]);
		i++;
	}
	return (cmd);
}

/*
**	If the envVar is not found in g_envv and it's the g_exit_status's one ⬇
*/

static	void	ft_cmd_env02(char **cmd, char **new_ptr, int cmd_index)
{
	char	*itoa;
	size_t	len;

	itoa = ft_itoa(g_exit_status);
	len = ft_strlen(*cmd) + ft_strlen(itoa);
	if (!(*new_ptr = calloc(len + 1, sizeof(char))))
		return ;
	len = ft_strlen(itoa);
	ft_memcpy(*new_ptr, *cmd, (size_t)cmd_index);
	ft_memcpy(&(*new_ptr)[cmd_index], itoa, len + 1);
	ft_memcpy(&(*new_ptr)[cmd_index + len],
		&(*cmd)[cmd_index + 2], ft_strlen(&(*cmd)[cmd_index + 1]));
	free(*cmd);
	free(itoa);
	*cmd = *new_ptr;
}

/*
**	If the envVar is found in g_envv ⬇
*/

static	void	ft_cmd_env03(char **cmd,
	char **new_ptr, int c_ind, size_t size)
{
	size_t	len;
	int		env_indx;

	env_indx = 0;
	while (g_envv[env_indx])
	{
		if (ft_strncmp(g_envv[env_indx], &(*cmd)[c_ind + 1], size - 1) == 0
			&& ft_strchr("=\0", g_envv[env_indx][size - 1]) != NULL)
			break ;
		env_indx++;
	}
	len = ft_strlen(*cmd) + ft_strlen(g_envv[env_indx]) - (size * 2);
	if (!(*new_ptr = calloc(len + 1, sizeof(char))))
		return ;
	len = ft_strlen(g_envv[env_indx]) - (size + 1);
	ft_memcpy(*new_ptr, *cmd, (size_t)c_ind);
	ft_memcpy(&(*new_ptr)[c_ind], &g_envv[env_indx][size], len + 1);
	ft_memcpy(&(*new_ptr)[c_ind + len + 1],
		&(*cmd)[c_ind + size], ft_strlen(&(*cmd)[c_ind + size]));
	free(*cmd);
	*cmd = *new_ptr;
}

char			*ft_cmd_env(char *c, int i)
{
	int		j;
	size_t	s;
	char	*new_ptr;

	while (c[++i] != '\0')
	{
		i = (single_quote(&c[i]) != 0 ? (i + single_quote(&c[i])) : i);
		if (c[i] == '$' && c[i + 1] != '\0'
			&& c[i + 1] != ' ' && c[i + 1] != ';')
		{
			s = 1;
			j = 0;
			ft_cmd_env04(c, i, &s, &j);
			if (!g_envv[j])
			{
				if (c[i + 1] == '?')
					ft_cmd_env02(&c, &new_ptr, i);
				else
					c = ft_fake_env(c, i--);
				continue ;
			}
			ft_cmd_env03(&c, &new_ptr, i, s);
		}
	}
	return (c);
}
