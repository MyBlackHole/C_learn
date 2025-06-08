#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>

#define TOK_ADD 5
#define MAXLINE 4096 /* max line length */

void do_line(char *);
void cmd_add(void);
int get_token(void);
jmp_buf jmpbuffer;

int demo_setjmp_main(void)
{
	char line[MAXLINE];
	if (setjmp(jmpbuffer) != 0) {
		printf("退出");
	} else {
		printf("ok\n");
		while (fgets(line, MAXLINE, stdin) != NULL) {
			do_line(line);
		}
	}

	exit(EXIT_SUCCESS);
}

char *tok_ptr;
void do_line(char *ptr)
{
	int cmd;
	tok_ptr = ptr;
	while ((cmd = get_token()) > 0) {
		switch (cmd) {
		case TOK_ADD:
			cmd_add();
			break;
		}
	}
}

void cmd_add(void)
{
	/*int token;*/
	longjmp(jmpbuffer, 1);
	// reset the processing for this command
}
int get_token(void)
{
	// fetch next token from line pointed to by tok_ptr
	return 5;
}
