/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lacruype <lacruype@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 12:15:53 by rledrin           #+#    #+#             */
/*   Updated: 2020/06/16 13:53:31 by lacruype         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int					ft_path(char **cmd, char **path)
{
	int				j;
	size_t			size;
	struct dirent	*pDirent;
	DIR				*pDir;
	char			*file;
	char			*tmp;

	j = 0;
	size = 0;
	while (!ft_strchr(" ;\"'", cmd[0][size]) && cmd[0][size])
		size++;
	while (path[j])
	{
		pDir = opendir(path[j]);
		if (pDir == NULL)
			return (-1);
		while ((pDirent = readdir(pDir)) != NULL)
		{
			if (size == ft_strlen(pDirent->d_name))
			{
				if (ft_strncmp(pDirent->d_name, cmd[0], size) == 0)
				{
					file = ft_strjoin(path[j], "/");
					tmp = file;
					file = ft_strjoin(file, pDirent->d_name);
					free(tmp);
					printf("CMD = %s\n", cmd[1]);
					if (fork() == 0)
						execve(file, cmd, g_envv);
					wait(0);
				}
			}
		}
		closedir(pDir);
		j++;
	}
	return (0);
}
