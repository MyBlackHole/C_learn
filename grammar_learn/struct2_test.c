#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

typedef int (*func_test)();

int test_func1(int a, int b) { return 1; }
int test_func2(int a) { return 1; }
int test_func3() { return 1; }

struct Func
{
    uint32_t length;
    func_test func;
};

int main()
{
    struct Func func_list[] = {
        {
            10,
            test_func3,
        },
        {
            10,
            (func_test)test_func2,
        },
        {
            10,
            (func_test)test_func1,
        },
    };
    (void)func_list;
    return 0;
}
