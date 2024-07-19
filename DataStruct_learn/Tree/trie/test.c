#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "trie.h"

/*---Print a word in the array--*/
void printArray(char chars[], int len)
{
	int i;
	for (i = 0; i < len; i++) {
		printf("%c", chars[i]);
	}
	printf("\n");
}

/*---Return all the related words------*/
void printPathsRecur(TrieNode *node, char prefix[], int filledLen)
{
	if (node == NULL) {
		return;
	}

	prefix[filledLen] = node->character;
	filledLen++;

	if (node->isEndOfWord) {
		printArray(prefix, filledLen);
	}

	int i;
	for (i = 0; i < ALPHABET_SIZE; i++) {
		printPathsRecur(node->children[i], prefix, filledLen);
	}
}

/*--Travel through the Trie and return words from it--*/
// 遍历
void traverse(char prefix[], TrieNode *root)
{
	TrieNode *temp = NULL;
	temp = search(root, prefix);
	int j = 0;
	while (prefix[j] != '\0') {
		j++;
	}
	printPathsRecur(temp, prefix, j - 1);
}

/*------Demonstrate purposes uses text file called dictionary -------*/

enum {
	NUMBER_OF_WORDS = 354935,
	INPUT_WORD_SIZE = 100,
};

/*----Get input from the user------*/
char *receiveInput(char *s)
{
	// 只取 99 个字符
	scanf("%99s", s);
	return s;
}

int main(int argc, char **argv)
{
	if (argc < 2) {
		fprintf(stderr, "%s\n initfile", argv[0]);
		exit(1);
	}
	// Read the file dictionary
	int word_count = 0;
	char *words[NUMBER_OF_WORDS];
	FILE *fp = fopen(argv[1], "r");

	if (fp == 0) {
		fprintf(stderr, "Error while opening dictionary file");
		exit(1);
	}

	words[word_count] = malloc(INPUT_WORD_SIZE);

	while (fgets(words[word_count], INPUT_WORD_SIZE, fp)) {
		word_count++;
		words[word_count] = malloc(INPUT_WORD_SIZE);
	}

	// Push the words in to Trie
	TrieNode *root = NULL;
	root = createTrieNode();
	int i;
	for (i = 0; i < NUMBER_OF_WORDS; i++) {
		insert(root, words[i]);
	}

	while (1) {
		printf("Enter keyword: ");
		char str[100];
		receiveInput(str);
		if (strcmp(str, "exit") == 0) {
			printf("\n退出\n");
			break;
		}
		printf("\n==========================================================\n");
		printf("\n********************* Possible Words ********************\n");

		// Find the word through the Trie
		traverse(str, root);

		printf("\n==========================================================\n");
	}

	// 释放内存
	for (; word_count > 0; word_count--) {
		free(words[word_count - 1]);
	}

	exit(0);
}
