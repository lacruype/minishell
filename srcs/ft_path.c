/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lacruype <lacruype@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 12:15:53 by rledrin           #+#    #+#             */
/*   Updated: 2020/02/14 15:18:45 by lacruype         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int					ft_path(char *cmd, char **path)
{
	int				i;
	int				j;
	size_t			size;
	struct dirent	*pDirent;
	DIR				*pDir;
	char			*file;
	char			*tmp;
	int				flag;

	i = 0;
	j = 0;
	flag = 0;
	size = 0;
	i = ft_jump_space(&cmd[i]) - cmd;
	while (!ft_strchr(" ;\"'", cmd[i + size])&& cmd[i + size])
		size++;
	while (path[j])
	{
		pDir = opendir (path[j]);
		if (pDir == NULL)
		{
			printf ("Cannot open directory ''\n");
			return (-1);
		}
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
