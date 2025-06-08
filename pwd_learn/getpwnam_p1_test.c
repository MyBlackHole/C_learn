#include <pwd.h>
#include <stdio.h>
#include <sys/types.h>

int main()
{
	struct passwd *user;
	user = getpwnam("black");
	printf("name = %s, uid = %d, home = %s\n", user->pw_name, user->pw_uid,
	       user->pw_dir);
	return 0;
}
