#include <mqueue.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    mq_unlink("/mq_test");
    return 0;
}
