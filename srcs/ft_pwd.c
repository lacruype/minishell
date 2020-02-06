
#include "../includes/minishell.h"


void	ft_pwd(char **env, char *file_name)
{
	int	fd;
	int	i;

	i = 0;
	while(env[i] && ft_strnstr(env[i], "PWD=", 4) == NULL)
		i++;
	if (file_name)
		fd = open(file_name, O_CREAT | O_WRONLY);
	else
		fd = 1;
	write(fd, &env[i][4], ft_strlen(&env[i][4]));
	write(fd, "\n", 1);
	if (file_name)
		close(fd);
}