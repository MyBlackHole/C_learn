#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char **argv)
{
	int status;
	if ((status = system("date")) < 0) {
		perror("system() error");
		exit(1);
	}
	if ((status = system("nosuchcommand")) < 0) {
		perror("system() error");
		exit(1);
	}
	if ((status = system("who ;exit 44")) < 0) {
		perror("system() error");
		exit(1);
	}
	exit(0);
}
