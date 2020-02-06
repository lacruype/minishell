/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lacruype <lacruype@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 11:14:32 by rledrin           #+#    #+#             */
/*   Updated: 2020/02/06 14:56:35 by lacruype         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		start_minishell()
{
	int i;
	int ret;
	int check_exit;
	char *cmd_line;
	char **cmd_line_split;

	ret = 1;
	check_exit = 0;
	while (ret == 1 && check_exit == 0)
	{
		i = 0;
		cmd_line = NULL;
		ft_putstr_fd("Minishell ➡ ", 0);
		ret = get_next_line(0, &cmd_line);
		cmd_line_split = ft_split(cmd_line, ' ');
		while (cmd_line_split[i] != NULL)
		{
			if (ft_strncmp((const char*)cmd_line_split[i], "exit",
				ft_strlen((const char*)cmd_line_split[i])) == 0)
				check_exit = 1;
			free(cmd_line_split[i]);
			i++;
		}
		free(cmd_line_split);
		free(cmd_line);
	}
	return (0);
}

int		main(int ac, char **av, char **env)
{
	(void)av;
	int i = 0;
	while (env[i] != NULL)
	{
		printf("ENV[%d] = [%s]\n", i, env[i]);
		i++;
	}
	if (ac != 1)
		return (0);
	if (start_minishell() == 0)
		return (0);
	return (-1);
}
