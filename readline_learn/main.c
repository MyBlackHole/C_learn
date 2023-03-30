#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    using_history();
    char *s;

    while (1)
    {
        s = readline("输入:");
        if (strcmp(s, "q") == 0)
        {
            break;
        }

        add_history(s);
    }
    return EXIT_SUCCESS;
}
