/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lacruype <lacruype@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 12:33:14 by lacruype          #+#    #+#             */
/*   Updated: 2020/07/02 16:33:08 by lacruype         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	*ft_realloc(void *ptr, size_t size)
{
	char	*newptr;

	if (!size && ptr)
	{
		if (!(newptr = (char *)malloc(1)))
			return (0);
		free(ptr);
		return (newptr);
	}
	if (!(newptr = (char *)malloc(size)))
		return (0);
	if (ptr)
	{
		ft_memcpy(newptr, ptr, size);
		free(ptr);
	}
	return (newptr);
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
	arr = 0;
}

char	*ft_jump_space(char *str)
{
	int i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == 'v'
		|| str[i] == '\n' || str[i] == 'r' || str[i] == '\f')
		i++;
	return (&str[i]);
}

int		create_file(char *filename, int app, int quote)
{
	int	fd;
	int	i;

	i = 0;
	if (!filename[0])
		return (1);
	if (ft_strlen(filename) > 255)
		return (-1);
	while (filename[i] && !quote)
	{
		if (ft_strchr("|", filename[i]))
			return (-1);
		i++;
	}
	if (ft_strncmp(filename, "..", 3) == 0 || ft_strncmp(filename, ".", 2) == 0)
		return (-1);
	if (app)
		fd = open(filename, O_CREAT | O_APPEND | O_WRONLY, 0666);
	else
		fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	return (fd);
}

int		quote(char *cmd)
{
	int		i;

	i = 0;
	if (cmd[i] == '\'')
	{
		while (1)
		{
			if (!cmd[i++])
				return (0);
			if (cmd[i] == '\'')
				break ;
		}
	}
	if (cmd[i] == '"')
	{
		while (1)
		{
			if (!cmd[i++])
				return (0);
			if (cmd[i] == '"')
				break ;
		}
	}
	return (((i != 0) ? (i - 1) : 0));
}
