
#include "../includes/minishell.h"


void		ft_pwd(char *cmd)
{
	int		fd;
	int		i;
	char	*filename;
	int		app;
	int		quotes;
	int		filesize; 

	app = 0;
	quotes = 0;
	filename = 0;
	i = 0;
	i =ft_jump_space(&cmd[i]) - cmd;
	i = ft_jump_space(&cmd[i + 3]) - cmd;
	if (cmd[i] == '>')
	{
		if (cmd[i + 1] == '>')
		{
			app = 1;
			i =ft_jump_space(&cmd[i + 2]) - cmd;;
		}
		else
			i = cmd - ft_jump_space(&cmd[i + 1]);
		if (ft_strchr("|<>", cmd[i]))
			; //ERROR
		if ((filesize = (cmd - quote(&cmd[i]))) > 0)
		{
			filename = ft_substr(cmd, i + 1, filesize - 2);		// +1 et -2 à cause des quotes
			quotes = 1;
		}
		else
			; //ERROR
	}
	while(g_envv[i] && ft_strncmp(g_envv[i], "PWD=", 4) != 0)
		i++;
	fd = create_file(filename, app, quotes);
	write(fd, &g_envv[i][4], ft_strlen(&g_envv[i][4]));
	write(fd, "\n", 1);
	if (filename)
		close(fd);
}