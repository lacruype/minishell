#include "../includes/minishell.h"

void	ft_echo(char **args)
{
	int	i;
	int	option;

	i = 0;
	option = 0;
	if (ft_strncmp(args[i], "echo", 5) != 0)
	{
		printf("ERROR\n");
		return ;
	}
	if (ft_strncmp(args[++i], "-n", 3) == 0)
	{
		printf("ERROR\n");
		return ;
	}
	while (args[i++])
	{
		ft_putstr_fd(args[i], 1);
		write(1, " ", 1);
	}
	if (!option)
		write(1, "\n", 1);
}
