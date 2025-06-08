#include <stdint.h>
#include <stdio.h>
#include <strings.h>

int demo_uint16_t_main(int argc, char *argv[])
{
	int port = 99999;
	uint16_t port_16 = port;
	printf("port: %d, port_16: %u\n", port, port_16);
	return 0;
}

// Output:
// ❯ xmake run grammar uint16_t
// port: 99999, port_16: 34463
