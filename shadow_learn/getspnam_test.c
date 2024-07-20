#include <shadow.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	struct spwd *ptr;
	if ((ptr = getspnam("black")) == NULL) {
		perror("getspnam error");
	}
	printf("sp_pwdp=%s\n", ptr->sp_pwdp == NULL || ptr->sp_pwdp[0] == 0 ?
					"(null)" :
					ptr->sp_pwdp);
	exit(0);
}
