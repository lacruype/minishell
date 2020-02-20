/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lacruype <lacruype@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 12:15:53 by rledrin           #+#    #+#             */
/*   Updated: 2020/02/20 15:18:54 by lacruype         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int					ft_path(char *cmd, char **path, int *pip)
{
	int				i;
	int				j;
	size_t			size;
	struct dirent	*pDirent;
	DIR				*pDir;
	char			*file;
	char			*tmp;
	int				flag;
	int				pipe_a;
	int				pipe_b;

	i = 0;
	j = 0;
	flag = 0;
	size = 0;
	pipe_a = 0;
	pipe_b = 0;
	i = ft_jump_space(&cmd[i]) - cmd;
	while (!ft_strchr(" ;\"'", cmd[i + size])&& cmd[i + size])
		size++;
	while (path[j])
	{
		pDir = opendir (path[j]);
		if (pDir == NULL)
			return (-1);
		while ((pDirent = readdir(pDir)) != NULL)
		{
			if (size == ft_strlen(pDirent->d_name))
			{
				if (ft_strncmp(pDirent->d_name, &cmd[i], size) == 0)
				{
					file = ft_strjoin(path[j], "/");
					tmp = file;
					file = ft_strjoin(file, pDirent->d_name);
					free(tmp);
					if (pipe_a)
						dup2(pip[0], 1);
					if (pipe_b)
						dup2(pip[1], 0);
					execve(file, ft_split(cmd, ' '), g_envv);
					flag = 1;
				}
			}
		}
		closedir(pDir);
		j++;
	}
	if (!flag)
		exit(5);
	return (0);
}
