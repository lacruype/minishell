/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lacruype <lacruype@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 14:34:27 by lacruype          #+#    #+#             */
/*   Updated: 2020/07/06 16:45:33 by lacruype         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int					cmpt_pipe(char *cmd)
{
	int		i;
	int		nb_pipe;

	i = 0;
	nb_pipe = 0;
	while (cmd[i])
	{
		i = ft_check_quotes_closed(cmd, i);
		if (cmd[i] == '|')
			nb_pipe++;
		i++;
	}
	return (nb_pipe);
}

static	void		exec_pipe3(t_var_minishell *t, char *cmd)
{
	(t->pi % 2 == 0) ? pipe(t->pipe_fd) : pipe(t->pi_fd2);
	if ((t->pid = fork()) == 0)
	{
		if (t->pi % 2 == 0)
			exec_com(&cmd[t->l], t->pi_fd2[0], t->pipe_fd[1], t->path);
		else
			exec_com(&cmd[t->l], t->pipe_fd[0], t->pi_fd2[1], t->path);
		exit(0);
	}
	if (t->pi % 2 == 0 && !close(t->pi_fd2[0]) && !close(t->pipe_fd[1]))
		write(1, "", 0);
	else if (!t->pi % 2 == 0 && !close(t->pi_fd2[1]) && !close(t->pipe_fd[0]))
		write(1, "", 0);
	waitpid(t->pid, &t->child_status, 0);
}

static	void		exec_pipe2(t_var_minishell *t, char *cmd)
{
	ft_freestrarr(t->split_cmd);
	if (t->pi == 0)
	{
		if ((t->pid = fork()) == 0)
		{
			close(t->pipe_fd[0]);
			exec_com(&cmd[t->l], 0, t->pipe_fd[1], t->path);
			exit(0);
		}
		close(t->pipe_fd[1]);
		wait(NULL);
	}
	else if (t->pi == t->nb_pipe)
	{
		if ((t->pid = fork()) == 0)
		{
			(t->pi % 2 == 0) ? exec_com(&cmd[t->l], t->pi_fd2[0], 1, t->path) :
				exec_com(&cmd[t->l], t->pipe_fd[0], 1, t->path);
			exit(0);
		}
		(t->pi % 2 == 0) ? close(t->pi_fd2[0]) : close(t->pipe_fd[0]);
		wait(NULL);
	}
	else
		exec_pipe3(t, cmd);
}

void				exec_pipe(t_var_minishell *t, char *cmd)
{
	t->k = 0;
	t->l = 0;
	t->pi = 0;
	if (pipe(t->pipe_fd) == -1 || pipe(t->pi_fd2) == -1)
		write(1, "ERROR: PIPE\n", 13);
	if (pipe(t->pipe_fd) == -1 || pipe(t->pi_fd2) == -1)
		exit(EXIT_FAILURE);
	while (cmd[t->l])
	{
		t->k = t->l;
		if (cmd[t->l] == '|' && cmd[t->l++])
			t->pi++;
		t->split_cmd = ft_split_redir(&cmd[t->l]);
		if (ft_strncmp(t->split_cmd[0], "exit", 5) == 0)
		{
			while (cmd[t->l] != '|' && cmd[t->l] != '\0')
				t->l++;
			ft_freestrarr(t->split_cmd);
			continue ;
		}
		exec_pipe2(t, cmd);
		while (cmd[t->l] != '|' && cmd[t->l] != '\0')
			t->l++;
	}
}
