#include <stdio.h>
#include <stdlib.h>

#define NUM 3

// 数组 与 指针
void test1()
{
    int A[10];
    int B[5][10];
    printf("sizeof A=%ld\n", sizeof(A));
    printf("sizeof B=%ld\n", sizeof(B));

    int(*pA) = A;
    int(*pB)[10] = B;
    (void)pA;
    (void)pB;
}

// 指针数组空间分配
void test2()
{
    int(*pipes)[2];

    pipes = malloc(NUM * sizeof(*pipes));
    if (pipes == NULL)
    {
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < NUM; i++)
    {
        pipes[i][0] = -1;
        pipes[i][1] = -1;
    }

    free(pipes);
}

// void test3() {
//   int (*pipes_bat)[2];
//   pipes_bat = malloc(sizeof(*pipes_bat));
//   if (pipes_bat[0] == NULL) {
//     exit(EXIT_FAILURE);
//   }
//   pipes_bat[1] = malloc(sizeof(int));
//   if (pipes_bat[1] == NULL) {
//     exit(EXIT_FAILURE);
//   }
// }

int main(int argc, char *argv[])
{
    test1();
    test2();

    exit(EXIT_SUCCESS);
}
