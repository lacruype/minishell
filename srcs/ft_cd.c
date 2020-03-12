#include "../includes/minishell.h"

char **g_envv;

static int	ft_find_env(int *i, char *elem)
{
	ssize_t	len;

	*i = 0;
	len = ft_strlen(elem);
	while (g_envv[(*i)])
	{
		if (!ft_strncmp(g_envv[*i], elem, len))
			return (1);
		(*i)++;
	}
	return (0);
}

static void	ft_get_dir(char **dir, char *args)
{
	int		i;

	i = 0;
	free(*dir);
	*dir = ft_strdup("");
	while (args[i])
	{
		*dir = ft_realloc(*dir, sizeof(char) * (i + 1));
		(*dir)[i] = args[i];
		i++;
		if (args[i] == '/')
			break;
	}
	*dir = ft_realloc(*dir, sizeof(char) * (i + 1));
	(*dir)[i] = '\0';
}

static void	ft_set_pwd(char **path, int pwd_indc, int oldpwd_indc)
{
	char	*tmp;
	int		i;
	int		j;

	j = 0;
	i = ft_strlen(g_envv[pwd_indc]);
	tmp = ft_substr(g_envv[pwd_indc], 4, ft_strlen(g_envv[pwd_indc]) - 4);
	// free(g_envv[oldpwd_indc]);
	g_envv[oldpwd_indc] = ft_strjoin("OLDPWD=", tmp);
	// free(tmp);
	while ((*path)[j])
	{
		if (!ft_strncmp(&(*path)[j], ".", 2))
			return ;
		else if (!ft_strncmp(&(*path)[j], "./", 2))
			j += 2;
		else if (!ft_strncmp(*path, "..", 2))
		{
			while (--i > 3 && g_envv[pwd_indc][i] != '/')
				;
			tmp = ft_substr(g_envv[pwd_indc], 0, i);
			// free(g_envv[pwd_indc]);
			g_envv[pwd_indc] = tmp;
			j += 2;
		}
		else if (!(*path)[j + 1])
			break ;
		else
			j++;
	}
	if (!j)
		g_envv[pwd_indc] = ft_strjoin("PWD=", *path);
	// free(g_envv[pwd_indc]);
	// free(*path);
}

void		ft_cd(char **args)
{
	int		i;
	int		env[3];
	char	*dir;
	char	*path;
	char	*tmp;
	DIR		*d;

	tmp = 0;
	dir = ft_strdup("");
	path = ft_strdup("");
	i = ft_jump_space(args[1]) - args[1];
	if (ft_strncmp(args[0], "cd", 3) != 0)
	{
		printf("ERROR\n");
		return ;
	}
	if (!ft_find_env(&env[1], "PWD=") || !ft_find_env(&env[2], "OLDPWD="))
	{
		printf("ERROR\n");
		return ;
	}
	while (args[1][i])
	{
		ft_get_dir(&dir, &args[1][i]);
		if (*dir)
		{
			if ((d = opendir((tmp = ft_strjoin(path, dir)))))
			{
				free(d);
				free(path);
				path = tmp;
				tmp = 0;
			}
			else
			{
				free(tmp);
				free(path);
				free(dir);
				tmp = 0;
				printf ("ERROR\n");
				return ;
			}
		}
		if (args[1][i] == '/')
			i++;
		while (args[1][i] && args[1][i] != '/')
			i++;
	}
	if (*path)
		ft_set_pwd(&path, env[1], env[2]);
}

int main(int ac, char **av, char **env)
{
	g_envv = env;
	char *args[] = {"cd", "../../"};
	int i, j;

	ft_find_env(&i, "PWD=");
	ft_find_env(&j, "OLDPWD=");

	printf ("1pwd =\t\t%s\n",g_envv[i]);
	printf ("1oldpwd =\t%s\n",g_envv[j]);

	ft_cd(args);

	printf ("2pwd =\t\t%s\n",g_envv[i]);
	printf ("2oldpwd =\t%s\n",g_envv[j]);

}
