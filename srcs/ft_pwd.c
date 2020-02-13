/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rledrin <rledrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 10:38:04 by rledrin           #+#    #+#             */
/*   Updated: 2020/02/13 11:18:37 by rledrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


void		ft_pwd(char *cmd)
{
	int		fd;
	int		i;
	char	*filename;
	int		app;
	int		quotes;
	int		filesize;
	int		j;

	app = 0;
	j = 0;
	quotes = 0;
	filename = ft_strdup("");
	i = 0;
	fd = 1;
	i = ft_jump_space(&cmd[i]) - cmd;
	i = ft_jump_space(&cmd[i + 3]) - cmd;
	if (cmd[i] == '>')
	{
		if (cmd[i + 1] == '>')
		{
			app = 1;
			i = ft_jump_space(&cmd[i + 2]) - cmd;;
		}
		else
			i = ft_jump_space(&cmd[i + 1]) - cmd;
		if (ft_strchr("|<>", cmd[i]))
			; //ERROR
		if ((filesize = quote(&cmd[i])) > 0)
		{
			filename = ft_substr(cmd, i + 1, filesize - 2);		// +1 et -2 à cause des quotes
			quotes = 1;
		}
		else if (filesize < 0)
			; //ERROR
		else
		{
			while(cmd[i] && !ft_strchr("|<>", cmd[i]))
			{
				filename = ft_realloc(filename, sizeof(char) * (j + 2));
				filename[j] = cmd[i];
				filename[j + 1] = '\0';
				j++;
				i++;
			}
			if (cmd[i] != '|' && cmd[i])
				; //ERROR
		}
	}
	while(g_envv[i] && ft_strncmp(g_envv[i], "PWD=", 4) != 0)
		i++;
	fd = create_file(filename, app, quotes);
	write(fd, &g_envv[i][4], ft_strlen(&g_envv[i][4]));
	write(fd, "\n", 1);
	if (filename)
		close(fd);
	free(filename);
}
