#include <stdio.h>
#include <unistd.h>

int demo_symlink_main(int argc, char *argv[])
{
	// Symlink function
	int ret = symlink(argv[1], argv[2]);

	// argv[1] is existing file name
	// argv[2] is soft link file name
	if (ret == 0) {
		printf("Soft Link created succuessfuly\n");
	}

	return 0;
}
// xmake run unistd_learn symlink ~/1.txt ~/1.txt_lnk
