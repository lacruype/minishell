#include <unistd.h>         // dup2(), pipe(), fork(), execvp()
#include <sys/wait.h>       // waitpid()

int main(int ac, char **av) 
{
    int pipe1[2], pipe2[2];
    int pid0, pid1, pid2;
    char *argp0[] = {"/bin/ls", NULL};
    char *argp1[] = {"/bin/cat", "-e", NULL};
    char *argp2[] = {"/usr/bin/wc", NULL};


    pipe(pipe1);
    pid0 = fork(); 
    if (pid0 == 0) {
        // close the read end of pipe1:
        close(pipe1[0]);
        // redirect stdout to the write end of pipe1:
        dup2(pipe1[1], 1);

        execvp("/bin/ls", argp0);
    }

    pipe(pipe2);
    pid1 = fork();
    if (pid1 == 0) {
        // close the write end of pipe1:
        close(pipe1[1]);
        // close the read end of pipe2:
        close(pipe2[0]);            
        // redirect stdin to the read end of pipe1:
        dup2(pipe1[0], 0);
        // redirect stdout to the write end of pipe2:
        dup2(pipe2[1], 1);

        execvp("/bin/cat", argp1);
    }

    pid2 = fork();
    if (pid2 == 0) { 
        // close unused pipe1:
        close(pipe1[0]);
        close(pipe1[1]);
        // close the write end of pipe2:
        close(pipe2[1]);
        // redirect stdin to the read end of pipe2:
        dup2(pipe2[0], 0);

        execvp("/usr/bin/wc", argp2);
    }

    waitpid(pid0, NULL, 0);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
}