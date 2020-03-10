#include "../includes/minishell.h"

void	ft_env(char **args)
{
	int	i;

	i = 0;
	if (ft_strncmp(args[0], "env", 4) != 0)
	{
		printf("ERROR\n");
		return ;
	}
	if (args[1])
	{
		printf("ERROR\n");
		return ;
	}
	while(g_envv[i])
	{
		ft_putstr_fd(g_envv[i++], 1);
		write(1, "\n", 1);
	}
}