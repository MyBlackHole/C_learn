#include <stdlib.h>
#include <stdio.h>
#include "foo.pb-c.h"

int main(int argc, char **argv)
{
	unsigned char simple_pad[8];
	ProtobufCBufferSimple bs = PROTOBUF_C_BUFFER_SIMPLE_INIT (simple_pad);
	(void)bs;
	return EXIT_SUCCESS;
}
