#include "includes/minishell.h"


int main ()
{

	int file_desc = open("test.txt", O_CREAT | O_WRONLY | O_APPEND, 0666);
	if (fork() == 0)
	{
		dup2(file_desc, 1);
		printf("je suis un test file\n");
		exit(0);
	}
	wait(0);
	printf("je suis un test stdout\n");
	close (file_desc);
	return (0);
}