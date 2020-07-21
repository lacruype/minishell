/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lacruype <lacruype@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 12:15:53 by rledrin           #+#    #+#             */
/*   Updated: 2020/07/06 16:43:52 by lacruype         ###   ########.fr       */
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

static	int		ft_path02(struct dirent *p_dirent,
	char **path, char **cmd, int j)
{
	char	*file;
	char	*tmp;
	pid_t	pid;
	int		status;

	file = ft_strjoin(path[j], "/");
	tmp = file;
	file = ft_strjoin_gnl(file, p_dirent->d_name);
	free(tmp);
	g_ctrl_backslash = 1;
	if (ft_strncmp("..", cmd[0], 3)
		&& ft_strncmp(".", cmd[0], 2) && (pid = fork()) == 0)
		if (execve(file, cmd, g_envv) == -1)
			exit(1);
	waitpid(pid, &status, 0);
	free(file);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (0);
}

int				ft_path(char **cmd, char **path, int *status)
{
	int				j;
	size_t			size;
	struct dirent	*p_dirent;
	DIR				*p_dir;

	j = -1;
	size = ft_path03(cmd);
	if (path == NULL || **path == '\0')
		return (2);
	while (path[++j])
	{
		p_dir = opendir(path[j]);
		if (p_dir == NULL)
			return (-100);
		while ((p_dirent = readdir(p_dir)) != NULL)
			if (size == ft_strlen(p_dirent->d_name))
				if (ft_strncmp(p_dirent->d_name, cmd[0], size) == 0)
				{
					*status = ft_path02(p_dirent, path, cmd, j);
					closedir(p_dir);
					return (12);
				}
		closedir(p_dir);
	}
	return (-2);
}
