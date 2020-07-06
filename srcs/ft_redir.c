/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lacruype <lacruype@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 14:14:59 by lacruype          #+#    #+#             */
/*   Updated: 2020/07/03 14:56:06 by lacruype         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char				**ft_split_redir(char *cmd)
{
	int		i;
	char	*stock;
	char	**stock2;

	i = 0;
	while (cmd[i])
	{
		if ((i = (ft_check_quotes_closed(cmd, i))) == -1)
			return (NULL);
		else if (ft_strchr("<>|", cmd[i]) && cmd[i - 1] != '\\')
		{
			stock = ft_substr_gnl(cmd, 0, i);
			stock2 = ft_split_spaces_quotes_gone(stock, ' ');
			free(stock);
			return (stock2);
		}
		else
			i++;
	}
	return (ft_split_spaces_quotes_gone(cmd, ' '));
}

static	char		*get_filename(char *cmd)
{
	char	*filename;
	int		i;
	int		j;
	char	*tmp;

	filename = ft_strdup("");
	i = 0;
	j = 0;
	while (cmd[i] == ' ')
		i++;
	while (cmd[i + j] && !(tmp = ft_strchr(" |<>", cmd[i + j])))
	{
		filename = ft_realloc(filename, (j + 2) * sizeof(char));
		filename[j] = cmd[i + j];
		j++;
	}
	if (tmp && (*tmp == '<' || *tmp == '>'))
	{
		printf("ERRORFILENAME\n");
		return (0);
	}
	filename[j] = '\0';
	return (filename);
}

static	int			redir02(int j, char *cmd, char *filename, int fd)
{
	char *tmp;

	tmp = ft_strchr("><", cmd[j]);
	if (*tmp == '>' && cmd[j + 1] == '>')
	{
		filename = get_filename(&cmd[j + 2]);
		fd = open(filename, O_WRONLY | O_APPEND | O_APPEND, 0666);
		dup2(fd, 1);
		j += 2;
	}
	else if (*tmp == '>' && (cmd[j + 1] == ' ' || ft_isalpha(cmd[j + 1])))
	{
		filename = get_filename(&cmd[j + 1]);
		fd = open(filename, O_CREAT | O_TRUNC | O_WRONLY, 0666);
		dup2(fd, 1);
		j++;
	}
	else if (*tmp == '<' && (cmd[j + 1] == ' ' || ft_isalpha(cmd[j + 1])))
	{
		filename = get_filename(&cmd[j + 1]);
		fd = open(filename, O_RDONLY);
		dup2(fd, 0);
		j++;
	}
	return ((fd != 0) ? 1 : 0);
}

int					redir(char *cmd)
{
	char	*filename;
	char	*tmp;
	int		fd;
	int		j;

	j = -1;
	fd = 0;
	filename = 0;
	while (cmd[++j] && cmd[j] != '|')
	{
		j = ft_check_quotes_closed(cmd, j);
		if ((tmp = ft_strchr("><", cmd[j])))
		{
			if (!redir02(j, cmd, filename, fd))
			{
				printf("ERRORREDIR\n");
				return (-1);
			}
		}
	}
	return (fd);
}
