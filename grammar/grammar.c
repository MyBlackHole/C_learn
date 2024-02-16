#include "grammar.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>

static demo_t demos[] = {
    DEMO_MAIN_ITEM(1),
    DEMO_MAIN_ITEM(2),
    DEMO_MAIN_ITEM(3),
    DEMO_MAIN_ITEM(4),
    DEMO_MAIN_ITEM(5),
    DEMO_MAIN_ITEM(6),
    DEMO_MAIN_ITEM(7),
    DEMO_MAIN_ITEM(8),
    DEMO_MAIN_ITEM(9),
    DEMO_MAIN_ITEM(10),
    DEMO_MAIN_ITEM(11),
    DEMO_MAIN_ITEM(argv_test),
    DEMO_MAIN_ITEM(do_while),
    DEMO_MAIN_ITEM(VA_ARGS),
    DEMO_MAIN_ITEM(sizeof),
    DEMO_MAIN_ITEM(int),
    DEMO_MAIN_ITEM(uint64),
    DEMO_MAIN_ITEM(arr),
    DEMO_MAIN_ITEM(continue),
    DEMO_MAIN_ITEM(wrs),
    DEMO_MAIN_ITEM(cleanup),
    DEMO_MAIN_ITEM(enum),
};
int main(int argc, char** argv)
{
    // find the main func from the first argument
    int ret_ok = 0;
    char const* name = NULL;
    size_t num = arrayn(demos);
    if (argc > 1 && argv[1])
    {
        size_t index = 0;
        for (index = 0; index < num; index++)
        {
            // find it?
            if (demos[index].name && !strcmp(demos[index].name, argv[1]))
            {
                // save name
                name = demos[index].name;

                // done main
                ret_ok = demos[index].main(argc - 1, argv + 1);
                break;
            }
        }
    }

    // no this demo? help it
    if (!name)
    {
        // walk name
        size_t index = 0;
        for (index = 0; index < num; index++)
        {
            printf("testname: %s\n", demos[index].name);
        }
    }

    // ok?
    return ret_ok;
}
