#include <stdio.h>
#include <unistd.h>
#include "LIBFT/libft.h"

int		get_cmd(char **line)
{
	int i;
	ssize_t ret;
	char *tmp;
	char buf[2];

	i = 0;
	buf[1] = '\0';
	if (!*line)
		*line = ft_strdup("");
	while ((ret = read(0, buf, 1)) == 1)
	{
		tmp = *line;
		*line = ft_strjoin(*line, buf);
		free(tmp);
		if (buf[0] == '\n')
			return (0);
	}
	return (-1);
}

int main()
{
	int i;
	int ret;
	char *line;

	i = 0;
	ret = 1;
	while (ret == 0)
	{
		ret = get_cmd(&line);
		printf("Cmd = [%s]\n", line);
		free(line);
	}
	if (ret != 0)
		printf("Getcmd error\n");
}