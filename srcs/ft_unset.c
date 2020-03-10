#include "../includes/minishell.h"

void		ft_unset(char **args)
{
	int		i;
	int		k;
	char	**fenv;

	k = 0;
	if (ft_strncmp(args[0], "unset", 6) != 0)
	{
		printf("ERROR\n");
		return ;
	}
	while (args[k])
	{
		i = 0;
		while(g_envv[i])
		{
			if (ft_strncmp(g_envv[i], args[k], (ft_strlen(args[k]) - 1)) == 0)
			{
				fenv = ft_calloc(i + 1, sizeof(char *));
				ft_memcpy(fenv, g_envv, i);
				free(g_envv[i++]);
				while (g_envv[i])
				{
					fenv = ft_realloc(fenv, i);
					fenv[i - 1] = g_envv[i];
					i++;
				}
				fenv[i] = 0;
				free(g_envv);
				g_envv = fenv;
			}
		}
		k++;
	}
}
