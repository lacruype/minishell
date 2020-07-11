/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lacruype <lacruype@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 13:16:52 by rledrin           #+#    #+#             */
/*   Updated: 2020/07/06 16:45:33 by lacruype         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			search_function(char *cmd_line, char **path)
{
	char	**split_cmd;

	split_cmd = ft_split_redir(cmd_line);
	if (ft_strncmp(split_cmd[0], "exit", 4) == 0 && cmpt_pipe(cmd_line) == 0)
	{
		write(1, "exit\n", 5);
		ft_freestrarr(split_cmd);
		exit(0);
	}
	exec_cmd(cmd_line, split_cmd, path);
	ft_freestrarr(split_cmd);
	return (0);
}

void		exec_com(char *cmd, int in, int out, char **path)
{
	// int i;

	// i = 0;
	// while (cmd[i] && !ft_strchr("<>", cmd[i]))
	// 	i++;
	// if (cmd[i])
	// 	search_function(cmd, path);
	if (in != 0)
	{
		dup2(in, 0);
		close(in);
	}
	if (out != 1)
	{
		dup2(out, 1);
		close(out);
	}
	search_function(cmd, path);
}

void		handle_sigint(int sig)
{
	g_flag_prompt = 0;
	if (sig == SIGINT)
	{
		ft_putstr_fd("\b\b  \n", 1);
		signal(SIGINT, handle_sigint);
		display_prompt();
	}
}

void		handle_sigquit(int sig)
{
	if (sig == SIGQUIT && g_ctrl_backslash != 0)
	{
		g_flag_prompt = 0;
		signal(SIGQUIT, handle_sigquit);
		ft_putstr_fd("Quit: 3\n", 1);
		display_prompt();
	}
	else
		ft_putstr_fd("\b\b  \b\b", 1);
}

int			main(int ac, char **av, char **env)
{
	t_var_minishell t;

	(void)av;
	g_flag_prompt = 0;
	if (ac != 1)
		return (0);
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
	if (init_g_envv(env) == -1)
		return (-1);
	start_minishell(&t);
	ft_freestrarr(g_envv);
	if (g_var)
		ft_freestrarr(g_var);
	return (0);
}
