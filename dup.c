# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <signal.h>

# include <stdio.h>
# include <limits.h>
# include <dirent.h>
#include <stdio.h>

int main ()
{
	int pip[2];

	pipe(pip);
	// int file_desc = open("tricky.txt", O_CREAT | O_WRONLY | O_APPEND, 0666); 
	char buf[500];
	//int fdsave;
	// here the newfd is the file descriptor of stdout (i.e. 1) 
	//fdsave = dup(1);
	if (fork())
	{
		close(pip[0]);
		dup2(pip[1], 1);
		close(pip[1]);
		printf("JE SUIS UN TEST\n");
		exit (0);
	}
	wait (0);
	
	// All the printf statements will be written in the file 
	// "tricky.txt" 
	//printf("I will be printed in the file tricky.txt\n"); 
	//dup2(file_desc, 0); 
	close(pip[1]);

	int ret = read (pip[0], buf, 400);
	close(pip[0]);

	//dup2(1, fdsave);  
	buf[ret] = '\0';
	printf("TEST = [%s]", buf); 


	return (0);
}
