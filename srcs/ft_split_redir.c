/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lacruype <lacruype@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 14:51:52 by rledrin           #+#    #+#             */
/*   Updated: 2020/06/18 16:42:38 by lacruype         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// int			ft_nb_word(char *cmd)
// {
// 	int		i;
// 	int		word;

// 	i = 0;
// 	word = 0;

// 	while (((ft_strchr("<>|", cmd[i]) && cmd[i - 1] == '\\') || (!ft_strchr("<>|", cmd[i]))) && cmd[i])
// 	{
// 		if (cmd[i] == ' ')
// 			i++;
// 		else if (((ft_strchr("<>|", cmd[i]) && cmd[i - 1] == '\\') || (!ft_strchr("<>|", cmd[i]))) && cmd[i])
// 			word++;
// 		while (cmd[i] != ' ' && cmd[i] && !ft_strchr("<>|", cmd[i]))
// 			i++;
// 	}
// 	return (word);
// }

// char		**ft_fill(char **cmd_split, char *cmd)
// {
// 	int		i;
// 	int		j;
// 	int		k;

// 	i = 0;
// 	j = -1;
// 	while (((ft_strchr("<>|", cmd[i]) && cmd[i - 1] == '\\') || (!ft_strchr("<>|", cmd[i]))) && cmd[i])
// 	{
// 		k = 0;
// 		while (cmd[i] == ' ')
// 			i++;
// 		if (((ft_strchr("<>|", cmd[i]) && cmd[i - 1] == '\\') || (!ft_strchr("<>|", cmd[i]))) && cmd[i])
// 			j++;
// 		while (cmd[i] != ' ' && (((ft_strchr("<>|", cmd[i]) && cmd[i - 1] == '\\') || (!ft_strchr("<>|", cmd[i]))) && cmd[i]))
// 		{
// 			i++;
// 			k++;
// 		}
// 		if (!cmd_split[j])
// 		{
// 			cmd_split[j] = ft_calloc(k + 1, sizeof(char));
// 			ft_memcpy(cmd_split[j], &cmd[i - k], k);
// 			cmd_split[j][k] = '\0';
// 		}
// 	}
// 	return (cmd_split);
// }

char		**ft_split_redir(char *cmd)
{
	int i;

	i = 0;
	while (cmd[i])
	{
		if ((cmd[i] == '"' && i == 0) || (cmd[i] == '"' && cmd[i - 1] != '\\'))
		{
			i++;
			while (cmd[i])
			{
				if (cmd[i] == '"')
					if (cmd[i - 1] != '\\')
						break ;
				i++;
			}
		}
		else if ((cmd[i] == '\'' && i == 0) || (cmd[i] == '\'' && cmd[i - 1] != '\\'))
		{
			i++;
			while (cmd[i])
			{
				if (cmd[i] == '\'')
					if (cmd[i - 1] != '\\')
						break ;
				i++;
			}
		}
		else if (ft_strchr("<>|", cmd[i]) && cmd[i - 1] != '\\')
			return (ft_split_semicolon(ft_substr_gnl(cmd, 0, i), ' '));
		else
			i++;	
	}
	return (ft_split_semicolon(cmd, ' '));
}

// char		**ft_split_redir(char *cmd)
// {
// 	char	**cmd_split;
// 	int		size;
	
// 	cmd_split = 0;
// 	printf("AVANT SPLIT REDIR = [%s]\n", cmd);
// 	size = ft_nb_word(cmd);
// 	cmd_split = ft_calloc(size + 2 , sizeof(char*));
// 	cmd_split = ft_fill(cmd_split, cmd);
// 	cmd_split[size] = 0;
// 	printf("RENDU DE SPLIT REDIR\n");
// 	for (int j = 0; cmd_split[j] != NULL; j++)
// 		printf("TRUC[%d] = [%s]\n", j, cmd_split[j]);
// 	return (cmd_split);
// }



// char		**ft_split_redir(char const *str)
// {
// 	int i;
// 	char *ret;
// 	char **ret_ft;

// 	i = 0;
// 	printf("STRRRRR = [%s]\n", str);
// 	while (str[i])
// 	{
// 		if ((str[i] == '"' && i == 0) || (str[i] == '"' && str[i - 1] != '\\'))
// 		{
// 			i++;
// 			while (str[i] && str[i] != '"' && str[i - 1] != '\\')
// 				i++;
// 			i++;
// 		}
// 		else if ((str[i] == '\'' && i == 0) || (str[i] == '\'' && str[i - 1] != '\\'))
// 		{
// 			i++;
// 			while (str[i] && str[i] != '\'' && str[i - 1] != '\\')
// 				i++;
// 			i++;
// 		}
// 		else if (ft_strchr("<>|", str[i]) != NULL)
// 		{
// 			write(1, "GOUGOU", 6);
// 			ret = ft_substr_gnl((char*)str, 0, (i - 1));
// 			ret_ft = ft_split_semicolon(ret, ' ');
// 			free(ret);
// 			for (int j = 0; ret_ft[j] != NULL; j++)
// 				printf("HAHA = [%s]\n", ret_ft[j]);
// 			return (ret_ft);
// 		}
// 		else
// 	   		i++;
// 	}
// 	ret_ft = ft_split_semicolon(str, ' ');
// 	return (ret_ft);
// }