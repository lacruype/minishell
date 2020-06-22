#include "../includes/minishell.h"

// static int	ft_check_var_name(char *arg)
// {
// 	int i;

// 	i = 0;
// 	while (arg[i] && arg[i] != '=')
// 	{
// 		if (arg[i] == '\'' || arg[i] == '\\' || arg[i] == '"')		// ameliorer les tests
// 			return (-1);
// 		else if (ft_isdigit(arg[i]))
// 			return (-1);
// 		i++;
// 	}
// 	return (i);
// }

static void	ft_print_env(void)
{
	int i;
	int j;

	i = 0;
	while(g_envv[i])
	{
		j = 0;
		ft_putstr_fd("declare -x ", 1);
		while (g_envv[i][j])
		{
			if (j > 0 && g_envv[i][j - 1] == '=')
				ft_putchar_fd('"', 1);
			ft_putchar_fd(g_envv[i][j], 1);
			j++;
		}
		ft_putchar_fd('"', 1);
		write(1, "\n", 1);
		i++;
	}
	i = 0;
	while (g_var[i])
	{
		j = 0;
		ft_putstr_fd("declare -x ", 1);
		while (g_var[i][j] != '\0')
		{
			ft_putchar_fd(g_var[i][j], 1);
			j++;
		}
		write(1, "\n", 1);
		i++;
	}
}

void	ft_export(char **args)
{
	int	i;
	int	k;
	int j;
	int equal;
	int tmp;

	i = 0;
	k = 1;
	if (!args[1])
		ft_print_env();
	else
	{
		while (args[k])
		{
			write(1, "pASSE", 5);
			equal = 0;
			j = 0;
			while (args[k][j])
			{
				if (args[k][j] == '=')
					equal = 1;
				j++;
			}
			
			if (equal)
			{
				tmp = get_size_env(g_envv);
				printf("tmp = %d\n", tmp);
				g_envv = ft_realloc(g_envv, (tmp + 2) * sizeof(char*));
				g_envv[tmp + 1] = NULL;
				g_envv[tmp] = ft_strdup(args[k]);
			}
			else
			{
				tmp = get_size_env(g_var);
				if (tmp == 0)
				{
					g_var = ft_realloc(g_var, (tmp + 2) * sizeof(char*));
					g_var[1] = NULL;
					g_var[0] = ft_strdup(args[k]);
				}
				else
				{
					g_var = ft_realloc(g_var, (tmp + 1) * sizeof(char*));
					g_var[tmp] = NULL;
					g_var[tmp - 1] = ft_strdup(args[k]);
				}
			}
			k++;
		}
	}
}