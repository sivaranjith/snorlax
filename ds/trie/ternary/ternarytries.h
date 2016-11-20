#include<stdio.h>
#include<stdlib.h>

#define boolean int
#define true 1
#define false 0

#define radix 26

struct ternaryTrieNode
{
	int key;
	struct ternaryTrieNode *next[3];
};

struct ternaryTrieNode* createTernaryTrie()
{
	return calloc(sizeof(ternaryTrieNode),1);
}