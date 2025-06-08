#include <stdlib.h>
#include <stdio.h>
#include <uuid/uuid.h>

int demo_uud_generate_main(int argc, char **argv)
{
	uuid_t uuid;
	char str[36];

	uuid_generate(uuid);
	uuid_unparse(uuid, str);

	printf("%s\n", str);

	return EXIT_SUCCESS;
}
// output:
// ❯ xmake run uuid_learn uud_generate
// 7fd90ce0-77d7-4f33-ba9f-7072e5bfc70e
