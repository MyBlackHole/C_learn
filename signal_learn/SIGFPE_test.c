#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

static void handler(int s)
{
	printf("触发了\n");
	sigset_t bset;
	sigemptyset(&bset);
	for (int i = 0; i < _SIGSET_NWORDS; i++) {
		printf("%ld\n", bset.__val[i]);
	}
	exit(EXIT_SUCCESS);
}

int demo_SIGFPE_main()
{
	/* signal(SIGFPE, SIG_IGN); */
	signal(SIGFPE, handler);
	int i = 0;
	int j = 0;
	i = i / j;
	printf("正常结束了");
	return EXIT_SUCCESS;
}

// output:
// 
// ❯ xmake run signal_learn SIGFPE
// 触发了
// 0
// 140725129839224
// 140725129839220
// 0
// 0
// 126688089128243
// 0
// 126688089084376
// 126688089319616
// 126684355362816
// 6
// 126688088888808
// 140725129839448
// 126688089129216
// 140725129839456
// 140725129839220
