#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void prefix_function(char *s, int num, int *pi)
{
	pi[0] = 0;
	for (int i = 1; i < num; i++) {
		for (int j = i; j >= 0; j--) {
			if (strncmp(s, s + (i - j + 1), j) == 0) {
				pi[i] = j;
				break;
			}
		}
	}
	return;
}

void prefix_function_(char *s, int num, int *pi)
{
	pi[0] = 0;
	for (int i = 1; i < num; i++) {
		for (int j = pi[i - 1] + 1; j >= 0; j--) {
			if (strncmp(s, s + (i - j + 1), j) == 0) {
				pi[i] = j;
				break;
			}
		}
	}
	return;
}

void prefix_function__(char *s, int num, int *pi)
{
	int j;
	pi[0] = 0;
	for (int i = 1; i < num; i++) {
		j = pi[i - 1];
		while (j > 0 && s[i] != s[j]) {
			j = pi[j - 1];
		}
		if (s[i] == s[j]) {
			j++;
		}
		pi[i] = j;
	}
	return;
}

int main(int argc, char *argv[])
{
	char *s = "abcabcd";
	int num = strlen(s);
	int *pi = malloc(num * sizeof(int));
	if (pi == NULL) {
		perror(strerror(errno));
		exit(EXIT_FAILURE);
	}
	// prefix_function(s, num, pi);
	// prefix_function_(s, num, pi);
	prefix_function__(s, num, pi);

	for (int i = 0; i < num; i++) {
		printf("%d", pi[i]);
		if (i != num - 1) {
			printf(" ");
		} else {
			printf("\n");
		}
	}

	free(pi);
	return EXIT_SUCCESS;
}
