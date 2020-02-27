#include <stdio.h>
#include <unistd.h>

int main() {
	int pip[2];
	int ret;
	char buf[101];
	char buf2[101];

	pipe(pip);
	write (pip[1], "HAHAHA", 6);
	ret = read(pip[0], buf, 100);
	buf[ret] = '\0';
	printf("BUF = [%s]\n", buf);
	write (pip[1], "\0", 1);
	ret = read(pip[0], buf2, 100);
	buf[ret] = '\0';
	printf("BUF 2 = [%s]\n", buf2);

	return (0);
}