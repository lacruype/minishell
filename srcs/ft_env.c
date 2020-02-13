/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rledrin <rledrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 10:37:54 by rledrin           #+#    #+#             */
/*   Updated: 2020/02/13 11:18:08 by rledrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		ft_env(char *cmd)
{
	int		i;
	int		app;
	char	*filename;
	int		filesize;
	int		quotes;
	int		j;
	int		fd;

	filename = ft_strdup("");
	fd = 1;
	j = 0;
	i = 0;
	app = 0;
	quotes = 0;
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
	fd = create_file(filename, app, quotes);
	while (g_envv[i])
	{
		write(fd, g_envv[i], ft_strlen(g_envv[i]));
		write(fd, "\n", 1);
		i++;
	}
	if (filename)
		close(fd);
	free(filename);
}
