#include <stdbool.h>
#define ALPHABET_SIZE 26

/*--Node in the Trie--*/
typedef struct TrieNode {
	// 每个节点的所有子 a~z
	struct TrieNode *children[ALPHABET_SIZE];
	// 对应字符
	char character;
	// 是否可以是字符结束
	bool isEndOfWord;
} TrieNode;

// 创建
TrieNode *createTrieNode();

// 插入元素
void insert(TrieNode *root, char *word);

// 查询元素
TrieNode *search(TrieNode *root, char *word);
