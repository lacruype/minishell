/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start_minishell.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lacruype <lacruype@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 14:10:32 by lacruype          #+#    #+#             */
/*   Updated: 2020/07/03 14:58:42 by lacruype         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	char	**init_path(char **path)
{
	int i;

	i = 0;
	if (path != NULL)
		ft_freestrarr(path);
	path = NULL;
	while (g_envv[i] != NULL)
	{
		if (ft_strncmp((const char*)g_envv[i], "PATH", 4) == 0)
			path = ft_split((const char*)&g_envv[i][5], ':');
		i++;
	}
	return (path);
}

void			display_prompt(void)
{
	int		i;
	char	buf[255];

	i = 0;
	while (g_envv[i] && ft_strncmp(g_envv[i], "PWD=", 4) != 0)
		i++;
	if (g_envv[i] == NULL)
	{
		ft_putstr_fd(getcwd(buf, 255), 1);
		ft_putstr_fd(" ➡ ", 1);
		return ;
	}
	ft_putstr_fd(&g_envv[i][4], 1);
	ft_putstr_fd(" ➡ ", 1);
	flag_prompt = 0;
}

static	int		start_minishell2(var_minishell *t)
{
	flag_prompt = 1;
	if (t->cmd_line[0] == '\0')
		return (8);
	if (t->cmd_line != NULL && (t->cmd_line = ft_parsing(t->cmd_line)) != NULL)
	{
		if ((t->tab_cmd_line = ft_split_semicolon(t->cmd_line, ';')) != NULL)
		{
			t->i = 0;
			while (t->tab_cmd_line[t->i] != NULL)
			{
				t->nb_pipe = cmpt_pipe(t->tab_cmd_line[t->i]);
				t->j = 0;
				if (t->nb_pipe == 0)
					search_function(&t->tab_cmd_line[t->i][t->j], t->path);
				else
					exec_pipe(t, t->tab_cmd_line[t->i]);
				t->i++;
			}
			ft_freestrarr(t->tab_cmd_line);
		}
		free(t->cmd_line);
	}
	return (0);
}

int				start_minishell(var_minishell *t)
{
	t->ret_gnl = 1;
	t->check_exit = 0;
	t->nb_pipe = 0;
	flag_prompt = 1;
	t->path = NULL;
	while (t->ret_gnl == 1 && t->check_exit == 0)
	{
		ctrl_backslash = 0;
		t->path = init_path(t->path);
		if (flag_prompt == 1)
			display_prompt();
		if (!get_next_line(0, &t->cmd_line))
			return (write(1, "exit\n", 5));
		if ((t->ret = start_minishell2(t)) == 8)
			continue;
	}
	ft_freestrarr(t->path);
	return (0);
}
