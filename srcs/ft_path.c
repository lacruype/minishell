/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lacruype <lacruype@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 12:15:53 by rledrin           #+#    #+#             */
/*   Updated: 2020/07/02 16:28:15 by lacruype         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	size_t	ft_path03(char **cmd)
{
	size_t size;

	size = 0;
	while (!ft_strchr(" ;\"'", cmd[0][size]) && cmd[0][size])
		size++;
	return (size);
}

static	void	ft_path02(struct dirent *p_dirent,
	char **path, char **cmd, int j)
{
	char *file;

	file = ft_strjoin(path[j], "/");
	file = ft_strjoin_gnl(file, p_dirent->d_name);
	ctrl_backslash = 1;
	if (ft_strncmp("..", cmd[0], 3)
		&& ft_strncmp(".", cmd[0], 2) && fork() == 0)
		execve(file, cmd, g_envv);
	wait(0);
	free(file);
}

int				ft_path(char **cmd, char **path)
{
	int				j;
	size_t			size;
	struct dirent	*p_dirent;
	DIR				*p_dir;

	j = -1;
	size = ft_path03(cmd);
	if (path == NULL || **path == '\0')
		return (ft_error("Minishell", cmd[0], 2));
	while (path[++j])
	{
		p_dir = opendir(path[j]);
		if (p_dir == NULL)
			return (ft_error("Minishell", cmd[0], -100));
		while ((p_dirent = readdir(p_dir)) != NULL)
			if (size == ft_strlen(p_dirent->d_name))
				if (ft_strncmp(p_dirent->d_name, cmd[0], size) == 0)
				{
					ft_path02(p_dirent, path, cmd, j);
					closedir(p_dir);
					return (0);
				}
		closedir(p_dir);
	}
	return (-2);
}
