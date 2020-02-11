
#include "../includes/minishell.h"


void		ft_pwd(char *cmd)
{
	int		fd;
	int		i;
	char	*filename;
	int		app;
	int		quote;
	int		filesize; 

	app = 0;
	quote = 0;
	filename = 0;
	i = ft_jump_space(&cmd[i]) - cmd;
	i = ft_jump_space(&cmd[i + 3]) - cmd;
	if (cmd[i] == '>')
	{
		if (cmd[i + 1] == '>')
		{
			app = 1;
			i = ft_jump_space(&cmd[i + 2]) - cmd;;
		}
		else
			i = ft_jump_space(&cmd[i + 1]) - cmd;
		if (cmd[i] == '|')
			; //ERROR
		if ((filesize = quote(&cmd[i]) - cmd) > 0)
		{
			filename = ft_substr(cmd, i + 1, filesize - 2)		// +1 et -2 à cause des quotes
			quote = 1;
		}
		else
			; //ERROR
	}
	while(g_envv[i] && ft_strncmp(g_envv[i], "PWD=", 4) != 0)
		i++;
	fd = create_file(filename, app, quote);
	write(fd, &g_envv[i][4], ft_strlen(&env[i][5]));
	write(fd, "\n", 1);
	if (filename)
		close(fd);
}