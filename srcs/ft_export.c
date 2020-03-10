#include "../includes/minishell.h"

static int	*ft_check_var_name(char *arg)
{
	int i;

	i = 0;
	while (arg[i] && arg[i] != '=')
	{
		if (arg[i] == '\'' || arg[i] == '\\' || arg[i] == '"')		// ameliorer les tests
			return (-1);
		else if (ft_isdigit(arg[i]))
			return (-1);
		i++;
	}
	return (i);
}

void	ft_export(char **args)
{
	int	i;
	int	j;
	int	k;
	char	*value;

	i = 0;
	k = 1;
	if (ft_strncmp(args[0], "export", 7) != 0)
	{
		printf("ERROR\n");
		return ;
	}
	if (!args[1])
	{
		while(g_envv[i])
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(g_envv[i++], 1);
			write(1, "\n", 1);
		}
	}
	else
	{
		while (args[k])
		{
			j = 0;
			if ((j = ft_check_var_name(args[k])) == -1)
			{
					printf("ERROR\n");
					return ;
			}
			if (args[k][j] == '=')
			{
				value = ft_substr(args[k], ++j, ft_strlen(&args[k][j]));
				g_envv = ft_realloc(g_envv, sizeof(g_envv) + sizeof(char*));
				g_envv[sizeof(g_envv) / sizeof(char*) - 1] = ft_strdup(value);
				free(value);
			}
			k++;
		}
	}
}