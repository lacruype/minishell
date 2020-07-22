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
		if (ft_strchr("<>|", cmd[i]) && i > 0 && cmd[i - 1] != '\\')
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

static	int			get_filename02(char *cmd, int i, int *j, char **filename)
{
	int		ret;
	char	*tmp;
	char	*tmp2;

	ret = 0;
	tmp = 0;
	if ((ret = quote(&(cmd[i + *j]))) != 0)
	{
		tmp = ft_substr(cmd, i + *j + 1, ret);
		tmp2 = *filename;
		*filename = ft_strjoin(*filename, tmp);
		free(tmp);
		free(tmp2);
		*j = *j + ret + 1;
		return (1);
	}
	return (0);
}

char				*get_filename(char *cmd)
{
	char	*filename;
	int		i;
	int		j;

	filename = ft_strdup("");
	i = 0;
	j = 0;
	while (cmd[i] == ' ')
		i++;
	while (cmd[i + j] && (!(ft_strchr(" |<>", cmd[i + j]))))
	{
		if (get_filename02(cmd, i, &j, &filename) == 1)
			continue ;
		filename = ft_realloc(filename, (j + 2) * sizeof(char));
		filename[j] = cmd[i + j];
		j++;
	}
	if (!(*filename))
		free(filename);
	if (!(*filename))
		return (0);
	filename[j] = '\0';
	return (filename);
}

static	int			redir02(int *j, char *c, char *filename, int *fd)
{
	if (c[*j] == '>' && c[(*j) + 1] == '>')
	{
		filename = get_filename(&c[(*j) + 2]);
		*fd = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0666);
		dup2(*fd, 1);
		(*j)++;
	}
	else if (c[*j] == '>')
	{
		filename = get_filename(&c[(*j)++ + 1]);
		*fd = open(filename, O_CREAT | O_TRUNC | O_WRONLY, 0666);
		dup2(*fd, 1);
	}
	else if (c[*j] == '<' &&
		!ft_strchr("@$%&\\/:*?\"'<>|~`#^+={}[];", c[(*j) + 1]))
	{
		filename = get_filename(&c[(*j)++ + 1]);
		*fd = open(filename, O_RDONLY);
		dup2(*fd, 0);
	}
	if (filename)
		free(filename);
	return ((*fd != 0 || filename) ? 1 : 0);
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
			if (!redir02(&j, cmd, filename, &fd))
				return (ft_error("Minishell", "newline", -10));
		}
	}
	return (fd);
}
