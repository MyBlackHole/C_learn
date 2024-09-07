/* unshare.c

   A simple implementation of the unshare(1) command: unshare
   namespaces and execute a command.
*/

#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* A simple error-handling function: print an error message based
   on the value in 'errno' and terminate the calling process. */

#define errExit(msg)                \
	do {                        \
		perror(msg);        \
		exit(EXIT_FAILURE); \
	} while (0)

static void usage(char *pname)
{
	fprintf(stderr, "Usage: %s [options] program [arg...]\n", pname);
	fprintf(stderr, "Options can be:\n");
	fprintf(stderr, "    -C   unshare cgroup namespace\n");
	fprintf(stderr, "    -i   unshare IPC namespace\n");
	fprintf(stderr, "    -m   unshare mount namespace\n");
	fprintf(stderr, "    -n   unshare network namespace\n");
	fprintf(stderr, "    -p   unshare PID namespace\n");
	fprintf(stderr, "    -t   unshare time namespace\n");
	fprintf(stderr, "    -u   unshare UTS namespace\n");
	fprintf(stderr, "    -U   unshare user namespace\n");
	exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
	int flags, opt;

	flags = 0;

	while ((opt = getopt(argc, argv, "CimnptuU")) != -1) {
		switch (opt) {
		case 'C':
			flags |= CLONE_NEWCGROUP;
			break;
		case 'i':
			flags |= CLONE_NEWIPC;
			break;
		case 'm':
			flags |= CLONE_NEWNS;
			break;
		case 'n':
			flags |= CLONE_NEWNET;
			break;
		case 'p':
			flags |= CLONE_NEWPID;
			break;
		// case 't':
		//     flags |= CLONE_NEWTIME;
		//     break;
		case 'u':
			flags |= CLONE_NEWUTS;
			break;
		case 'U':
			flags |= CLONE_NEWUSER;
			break;
		default:
			usage(argv[0]);
		}
	}

	if (optind >= argc) {
		usage(argv[0]);
	}

	// 脱离当前命名空间移动到其他上
	if (unshare(flags) == -1) {
		errExit("unshare");
	}

	execvp(argv[optind], &argv[optind]);
	errExit("execvp");
}
