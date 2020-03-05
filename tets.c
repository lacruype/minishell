#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

// int main() {
// 	int pip[2];
// 	int ret;
// 	char buf[101];
// 	char buf2[101];

// 	pipe(pip);
// 	write (pip[1], "HAHAHA", 6);
// 	ret = read(pip[0], buf, 100);
// 	buf[ret] = '\0';
// 	printf("BUF = [%s]\n", buf);
// 	write (pip[1], "\0", 1);
// 	ret = read(pip[0], buf2, 100);
// 	buf[ret] = '\0';
// 	printf("BUF 2 = [%s]\n", buf2);

// 	return (0);
// }


int main(int ac, char **av)
{
	int pipe_fd[2];
	int save_fd[2];
	int i;
	pid_t pid;

	i = 0;
	// save_fd[0] = dup(0);
	// save_fd[1] = dup(1);
	// pipe(pipe_fd);
	// dup2(pipe_fd[1], 1);
	// close(pipe_fd[0]);
	// if (fork() == 0)
	// {
	// 	execve("/bin/ls", av, NULL);

	// }
	// wait(0);
	// dup2(pipe_fd[0], 0);
	// dup2(save_fd[1], 1);

	// if (fork() == 0)
	// {
	// 	execve("/bin/wc", av, NULL);

	// }
	// wait(0);

	if (pipe(pipe_fd) == -1)
		printf("Errr pipe\n");
		
	if ((pid = fork()) == 0)
	{
		dup2(pipe_fd[1], 1);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		execve("/bin/ls", av, NULL);
		printf("Error ls\n");
	}
	else if (pid == -1)
		printf("Error fork\n");
	close(pipe_fd[1]);
	wait(NULL);

	if ((pid = fork()) == 0)
	{
		dup2(pipe_fd[0], 0);
		close(pipe_fd[1]);
		close(pipe_fd[0]);
		printf("exec = %d\n", execve("/bin/cat", av, NULL));
		printf("Error cat\n");
	}
	else if (pid == -1)
		printf("Error fork2\n");
	close(pipe_fd[0]);
	wait(NULL);

}