#include <string.h>
#include <pwd.h>
#include <stdlib.h>
#include <stdio.h>
#include <grp.h>

static void group2str(unsigned gid, char *out)
{
	struct group *gr = getgrgid(gid);
	if (gr) {
		strcpy(out, gr->gr_name);
	} else {
		sprintf(out, "%d", gid);
	}
}

int main(int argc, char *argv[])
{
	int uid = 1000;
	int gid = 1000;

	char buff[1000] = { 0 };
	group2str(1000, buff);

	printf("info: group2str: %s\n", buff);

	struct passwd *pw = getpwuid(uid);
	if (pw) {
		printf("%s\n", pw->pw_name);
	} else {
		printf("%d\n", uid);
	}

	struct group *gr = getgrgid(gid);
	if (gr) {
		printf("%s\n", gr->gr_name);

	} else {
		printf("%d\n", gid);
	}
	return EXIT_SUCCESS;
}
