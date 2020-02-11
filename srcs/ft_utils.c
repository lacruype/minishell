/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lacruype <lacruype@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 12:33:14 by lacruype          #+#    #+#             */
/*   Updated: 2020/02/10 15:36:59 by lacruype         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	*ft_realloc(void *dst, size_t new_size)
{
	size_t	cur_size;
	char	*newdst;

	if (dst == 0)
		return (malloc(new_size));
	cur_size = sizeof(dst);
	if (new_size <= cur_size)
		return (dst);
	newdst = malloc(new_size);
	ft_memcpy(dst, newdst, (int)cur_size);
	free(dst);
	return (newdst);
}

void	ft_freestrarr(char **arr)
{
	int i;

	i = -1;
	if (!arr)
		return ;
	if (*arr)
	{
		while (arr[++i])
			free(arr[i]);
	}
	free(arr);
	arr = NULL;
}

char	*ft_jump_space(char *str)
{
	int i;

	i = 0;
	while (str[i] == ' ')
		i++;
	return (&str[i]);
}

int		create_file(char *filename, int app, int quote)
{
	int	fd;
	int	i;

	i = 0;
	if (!filename)
		return(1);
	if (ft_strlen(filename) > 255)
		return (-1);
	while (filename[i] && !quote)
	{
		if (ft_strchr("|", filename[i]))
			return (-1);
		i++;
	}
	if (ft_strncmp(filename, "..", 3) = 0 || ft_strncmp(filename, ".", 2) == 0)
		return (-1);
	if (app)
		fd = open(filename, O_CREAT | O_APPEND | O_WRONLY);
	else
		fd = open(filename, O_CREAT | O_WRONLY);
	return (fd);
}

char		*quote(char *cmd)
{
	int		i;
	int		quote;

	i = 0;
	if (cmd[i] == '\'')
	{
		quote = 1;
		while (quote)
		{
			if (!cmd[i++])
				return(0);
			if (cmd[i] == '\'')
				quotes = 0;
		}
	}
	if (cmd[i] == '\"')
	{
		quote = 1;
		while (quote)
		{
			if (!cmd[i++])
				return(0);
			if (cmd[i] == '\"')
				quotes = 0;
		}
	}
	if (i != 0)
		return(&cmd[i]);
	return(0);
}
