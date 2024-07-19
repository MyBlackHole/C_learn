#include <mqueue.h>
#include <unistd.h>

int demo_mq_unlink_main(int argc, char *argv[])
{
	mq_unlink("/mq_test");
	return 0;
}
