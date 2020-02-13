/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rledrin <rledrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 12:15:53 by rledrin           #+#    #+#             */
/*   Updated: 2020/02/13 13:58:10 by rledrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int					ft_path(char *cmd, char **path)
{
	int				i;
	int				j;
	int				size;
	struct dirent	*pDirent;
	DIR				*pDir;
	char			*file;
	char			*tmp;

	i = 0;
	j = 0;
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
			return 1;
		}
		while ((pDirent = readdir(pDir)) != NULL)
		{
			if (ft_strncmp(pDirent->d_name, &cmd[i], size) == 0)
			{
				file = ft_strjoin(path[j], "/");
				tmp = file;
				file = ft_strjoin(file, pDirent->d_name);
				free(tmp);
				execve(file, ft_split(cmd, ' '), g_envv);
			}
		}
		closedir(pDir);
		j++;
	}
	return (0);
}
