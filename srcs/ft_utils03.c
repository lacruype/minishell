/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils03.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lacruype <lacruype@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 16:47:45 by lacruype          #+#    #+#             */
/*   Updated: 2020/07/06 16:43:39 by lacruype         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int				ft_check_quotes_closed(const char *s, int i)
{
	if ((s[i] == '"' && i == 0) || (s[i] == '"' && s[i - 1] != '\\'))
	{
		i++;
		while (s[i])
		{
			if (s[i] == '"')
				if (s[i - 1] != '\\')
					return (i);
			i++;
		}
		return (-1);
	}
	else if ((s[i] == '\'' && i == 0) || (s[i] == '\'' && s[i - 1] != '\\'))
	{
		i++;
		while (s[i])
		{
			if (s[i] == '\'')
				if (s[i - 1] != '\\')
					return (i);
			i++;
		}
		return (-1);
	}
	return (i);
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

static int		ft_search_builtin(char *cmd, char **split_cmd, int *ret)
{
	if (ft_strncmp(cmd, "echo", 5) == 0)
		ft_echo(split_cmd);
	else if (ft_strncmp(cmd, "export", 7) == 0)
		*ret = ft_export(split_cmd);
	else if (ft_strncmp(cmd, "unset", 6) == 0)
		ft_unset(split_cmd);
	else if (ft_strncmp(cmd, "cd", 3) == 0)
		*ret = ft_cd(split_cmd);
	else if (ft_strncmp(cmd, "pwd", 4) == 0)
		ft_pwd();
	else if (ft_strncmp(cmd, "env", 4) == 0)
		ft_env(split_cmd);
	else
		return (1);
	return (0);
}

static	void	exec_cmd02(char **split_cmd, char **path, int *ret)
{
	char		*cmd;

	cmd = ft_strdup(*split_cmd);
	ft_cmd_to_lower(cmd);
	if (ft_search_builtin(cmd, split_cmd, ret) == 0)
		;
	else if (ft_strncmp(split_cmd[0], "./", 2) == 0 ||
			ft_strncmp(split_cmd[0], "/", 1) == 0)
	{
		if (fork() == 0)
			if (execve(&(split_cmd[0][0]), split_cmd, g_envv) == -1)
			{
				ft_error("Minishell", split_cmd[0], 2);
				exit(0);
			}
		wait(0);
	}
	else if (ft_path(split_cmd, path) == -2)
	{
		free(cmd);
		return ((void)ft_error("Minishell", "", -100));
	}
	free(cmd);
}

int				exec_cmd(char *cmd_line, char **split_cmd, char **path)
{
	int	savefd[2];
	int	fd;
	int ret;

	savefd[0] = dup(0);
	savefd[1] = dup(1);
	if ((fd = redir(cmd_line)) == -1)
		return (-1);
	exec_cmd02(split_cmd, path, &ret);
	dup2(savefd[0], 0);
	dup2(savefd[1], 1);
	if (ret != -1)
		g_exit_status = 0;
	if (fd != 0)
		close(fd);
	return (0);
}
