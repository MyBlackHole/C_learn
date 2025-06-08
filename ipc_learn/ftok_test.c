#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int demo_ftok_main(int argc, char **argv)
{
	struct stat stat1;
	if (argc != 2) {
		printf("usage: ftok < pathname >");
		exit(EXIT_FAILURE);
	}
	stat(argv[1], &stat1);
	printf("st_dev:%lx, st_ino:%lx, key:%x\n", (unsigned long)stat1.st_dev,
	       (unsigned long)stat1.st_ino, ftok(argv[1], 0x579));
	printf("st_dev:%lx, st_ino:%lx, key:%x\n", (unsigned long)stat1.st_dev,
	       (unsigned long)stat1.st_ino, ftok(argv[1], 0x118));
	printf("st_dev:%lx, st_ino:%lx, key:%x\n", (unsigned long)stat1.st_dev,
	       (unsigned long)stat1.st_ino, ftok(argv[1], 0x22));
	printf("st_dev:%lx, st_ino:%lx, key:%x\n", (unsigned long)stat1.st_dev,
	       (unsigned long)stat1.st_ino, ftok(argv[1], 0x33));
	exit(EXIT_SUCCESS);
}

// st_dev:801, st_ino:1901adc, key:79011adc
// st_dev:801, st_ino:1901adc, key:18011adc
// st_dev:801, st_ino:1901adc, key:22011adc
// st_dev:801, st_ino:1901adc, key:33011adc
