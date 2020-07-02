/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils03.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lacruype <lacruype@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 16:47:45 by lacruype          #+#    #+#             */
/*   Updated: 2020/07/02 16:55:43 by lacruype         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void			f(char c)
{
	write(1, &c, 1);
}

int				ft_check_var_name(char *arg)
{
	int i;

	i = 0;
	if (ft_isdigit(arg[0]))
		return (-1);
	while (arg[i] && arg[i] != '=')
	{
		if (arg[i] == '\'' || arg[i] == '\\' || arg[i] == '"' || arg[i] == '-')
			return (-1);
		i++;
	}
	return (0);
}

static	void	exec_cmd02(char **split_cmd, char **path, int *ret)
{
	if (ft_strncmp(split_cmd[0], "echo", 5) == 0)
		ft_echo(split_cmd);
	else if (ft_strncmp(split_cmd[0], "export", 7) == 0)
		*ret = ft_export(split_cmd);
	else if (ft_strncmp(split_cmd[0], "unset", 6) == 0)
		ft_unset(split_cmd);
	else if (ft_strncmp(split_cmd[0], "cd", 3) == 0)
		*ret = ft_cd(split_cmd);
	else if (ft_strncmp(split_cmd[0], "./", 2) == 0)
	{
		if (fork() == 0)
			if (execve(&(split_cmd[0][2]), split_cmd, g_envv) == -1)
			{
				ft_error("Minishell", split_cmd[0], 2);
				exit(0);
			}
		wait(0);
	}
	else if (ft_path(split_cmd, path) == -2)
		return ((void)ft_error("Minishell", "", -100));
}

int				exec_cmd(char *cmd_line, char **split_cmd, char **path)
{
	int	savefd[2];
	int	fd;
	int ret;

	savefd[0] = dup(0);
	savefd[1] = dup(1);
	fd = redir(cmd_line);
	exec_cmd02(split_cmd, path, &ret);
	dup2(savefd[0], 0);
	dup2(savefd[1], 1);
	if (ret != -1)
		exit_status = 0;
	if (fd != 0)
		close(fd);
	return (0);
}
