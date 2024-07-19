#include <pwd.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

struct passwd *getpwnam(const char *name)
{
	struct passwd *ptr;
	setpwent();
	while ((ptr = getpwent()) != NULL) {
		if (strcmp(name, ptr->pw_name) == 0) {
			printf("%s\n", ptr->pw_name);
			break;
		}

		printf("#### %s\n", ptr->pw_name);
	}
	endpwent();
	return (0);
}

int main()
{
	getpwnam("black");
}
