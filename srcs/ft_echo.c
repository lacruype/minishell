/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rledrin <rledrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 11:25:16 by rledrin           #+#    #+#             */
/*   Updated: 2020/02/12 18:50:00 by rledrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		ft_echo(char *cmd)
{
	int		fd;
	int		i;
	int		option;
	int		app;
	char	*filename;
	int		strsize;
	char	*str;
	char	*tmp;
	int		filesize;
	int		quotes;
	int		j;
	
	option = 0;
	quotes = 0;
	app = 0;
	j = 0;
	i = 0;
	filename = ft_strdup("");
	str = ft_strdup("");
	fd = 1;
	i = ft_jump_space(&cmd[i]) - cmd;
	i = ft_jump_space(&cmd[i + 4]) - cmd;
	if (cmd[i] == '-' && cmd[i + 1] == 'n')
	{
		option = 1;
		i = ft_jump_space(&cmd[i + 2]) - cmd;
	}
	while (!ft_strchr("|<>", cmd[i]) && cmd[i])
	{
		if (cmd[i] == '"' || cmd[i] == '\'')
		{
			
			if ((strsize = quote(&cmd[i])) > 0)
			{
				tmp = str;
				i++;
				str = ft_strjoin(str, ft_substr(cmd, i, strsize));
				free(tmp);
				i += strsize + 1;
			}
			else if (strsize < 0)
				; //ERROR
		}
		else if (cmd[i] == ' ' && cmd[i + 1] == ' ')
			i++;
		else
		{
			j = ft_strlen(str);
			str = realloc(str, j + 2);
			str[j] = cmd[i];
			str[j + 1] = '\0';
			i++;
		}
	}
	j = 0;
	if (cmd[i] == '>')
	{
		if (cmd[i + 1] == '>')
		{
			app = 1;
			i = ft_jump_space(&cmd[i + 2]) - cmd;
		}
		else
			i = ft_jump_space(&cmd[i + 1]) - cmd;
		if (ft_strchr("|<>", cmd[i]))
			; //ERROR
		while (cmd[i] && cmd[i] != '|')
		{
			if (cmd[i] == '"' || cmd[i] == '\'')
			{
				if ((filesize = quote(&cmd[i])) > 0)
				{
					i++;
					tmp = filename;
					filename = ft_substr(cmd, i, filesize);		// +1 et -2 à cause des quotes
					free(tmp);
					quotes = 1;
					i += strsize;
				}
			}
			else if (filesize < 0)
				; //ERROR
			else
			{
				filename = ft_realloc(filename, sizeof(char) * (j + 2));
				filename[j] = cmd[i];
				filename[j + 1] = '\0';
			}

			i++;
			j++;
		}
	}
	fd = create_file(filename, app, quotes);
	i = 0;
	write(fd, str, ft_strlen(str));
	if (!option)
		write(fd, "\n", 1);
	if (filename[0])
		close(fd);
}


int main (int ac, char **av)
{
	ft_echo(av[1]);
	// int fd = open("file", O_CREAT | O_RDWR, 0666);
	// printf("FD = %d", fd);
	// close(fd);
}
