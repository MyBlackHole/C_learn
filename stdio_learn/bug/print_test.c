#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 65536

int main(int argc, char *argv[])
{
	char buffer[BUFFER_SIZE];
	memset(buffer, 'a', BUFFER_SIZE-1);
	write(STDOUT_FILENO, buffer, BUFFER_SIZE);
	/*sleep(1);*/
	write(STDOUT_FILENO, "Hello, world!", 13);
	return EXIT_SUCCESS;
}
