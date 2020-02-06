/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lacruype <lacruype@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 11:20:30 by lacruype          #+#    #+#             */
/*   Updated: 2020/02/06 12:52:34 by lacruype         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <string.h>
# include <stdlib.h>
# include <unistd.h>

void	ft_strdel(char **as);
char	*ft_substr_gnl(char *s, unsigned int start, int len);
char	*ft_strdup_gnl(char *s);
char	*ft_strchr_gnl(char *s, int c);
char	*ft_strjoin_gnl(char *s1, char *s2);
int		ft_strlen_gnl(char *s);
int		ft_new_line(char **gnl, char **line, int fd, ssize_t ret);
int		get_next_line(int fd, char **line);
char	*ft_strnew(int size);
void	ft_swapfree(char **gnl, char *tmp, int fd);

#endif
