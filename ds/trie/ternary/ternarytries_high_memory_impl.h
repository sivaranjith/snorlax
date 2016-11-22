#include<stdio.h>
#include<stdlib.h>

#define boolean int
#define true 1
#define false 0

#define radix 26

struct ternaryTrieNode
{
	char *key;
	int value,length;
	struct ternaryTrieNode *next[3];
};

struct ternaryTrieNode* createTernaryTrie()
{
	struct ternaryTrieNode *ternaryTrieObj = calloc(sizeof(struct ternaryTrieNode),1);
	ternaryTrieObj->key = calloc(sizeof(char),1);
	return ternaryTrieObj;
}

struct ternaryTrieNode* ternaryTrieInsertor(struct ternaryTrieNode *ternaryTrieObj,char *key,int value,int index)
{
	struct ternaryTrieNode **trieObjRef;
	int inc = 0;
	if(ternaryTrieObj == NULL)
	{
		ternaryTrieObj = createTernaryTrie();
	}
	if(ternaryTrieObj->length == 0)
	{
		if(*(key + index) != '\0')
		{
			inc = 1;
			ternaryTrieObj->key[0] = *(key + index);
			++(ternaryTrieObj->length);
		}
		else
		{
			free(ternaryTrieObj);
			return NULL;
		}
	}
	if(*(key + index + 1) == '\0')
	{
		ternaryTrieObj->value = value;
		return ternaryTrieObj;
	}

	if(*(key + index) < ternaryTrieObj->key[0])
	{
		trieObjRef = &(ternaryTrieObj->next[0]);
	}
	else if(*(key + index) == ternaryTrieObj->key[0])
	{
		inc = 1;
		trieObjRef = &(ternaryTrieObj->next[1]);
	}
	else
	{
		trieObjRef = &(ternaryTrieObj->next[2]);
	}

	*trieObjRef = ternaryTrieInsertor(*trieObjRef,key,value,index + inc);

	if(*trieObjRef == NULL)
	{
		ternaryTrieObj->value = value;
	}
	return ternaryTrieObj;
}

struct ternaryTrieNode* insertTernaryTrie(struct ternaryTrieNode *ternaryTrieObj,char *key,int value)
{
	if(*key == '\0')
	{
		return false;
	}
	return ternaryTrieInsertor(ternaryTrieObj,key,value,0);
}

void ternaryTriePrinter(struct ternaryTrieNode* ternaryTrieObj,char *container,int index)
{
	if(ternaryTrieObj == NULL)
	{
		return;
	}
	*(container + index++) = ternaryTrieObj->key[0];

	printf("%s %d\n",container,ternaryTrieObj->value);

	ternaryTriePrinter(ternaryTrieObj->next[1],container,index);

	*(container + --index) = '\0';

	ternaryTriePrinter(ternaryTrieObj->next[0],container,index);
	ternaryTriePrinter(ternaryTrieObj->next[2],container,index);

}

void printTernaryTrie(struct ternaryTrieNode *ternaryTrieObj)
{
	char *container = calloc(sizeof(char),21);
	ternaryTriePrinter(ternaryTrieObj,container,0);
	free(container);
}

int ternaryTrieSearcher(struct ternaryTrieNode *ternaryTrieObj,char *key,int index)
{
	char c = *(key + index);
	if(ternaryTrieObj == NULL)
	{
		return 0;
	}

	if(c < ternaryTrieObj->key[0])
	{
		return ternaryTrieSearcher(ternaryTrieObj->next[0],key,index);
	}
	else if(c > ternaryTrieObj->key[0])
	{
		return ternaryTrieSearcher(ternaryTrieObj->next[2],key,index);
	}
	else if(*(key + index + 1) == '\0')
	{
		return ternaryTrieObj->value;
	}
	else
	{
		return ternaryTrieSearcher(ternaryTrieObj->next[1],key,index+1);
	}
}

int searchTernaryTrie(struct ternaryTrieNode *ternaryTrieObj,char *key)
{
	if(*key == '\0')
	{
		return 0;
	}
	return ternaryTrieSearcher(ternaryTrieObj,key,0);
}

boolean ternaryTrieRemover(struct ternaryTrieNode *ternaryTrieObj,char *key,int index)
{
	struct ternaryTrieNode **temp,*freePt;
	char c = *(key + index);
	int inc = 0;

	if(ternaryTrieObj == NULL || *key == '\0')
	{
		return false;
	}

	if(c < ternaryTrieObj->key[0])
	{
		temp = &(ternaryTrieObj->next[0]);
	}
	else if(c > ternaryTrieObj->key[0])
	{
		temp = &(ternaryTrieObj->next[2]);
	}
	else if(*(key + index + 1) == '\0' && ternaryTrieObj->value != 0)
	{
		if(ternaryTrieObj->next[1] != NULL)
		{
			ternaryTrieObj->value = 0;
		}
		else
		{
			ternaryTrieObj->value = -1;
		}
		return true;
	}
	else
	{
		inc = 1;
		temp = &(ternaryTrieObj->next[1]);
	}
	
	if(ternaryTrieRemover(*temp,key,index + inc))
	{
		if((*temp)->value == -1)
		{
			freePt = *temp;
			*temp = NULL;
			free(freePt);
			if(ternaryTrieObj->value == 0 && ternaryTrieObj->next[0] == NULL && ternaryTrieObj->next[1] == NULL && ternaryTrieObj->next[2] == NULL)
			{
				ternaryTrieObj->value = -1;
			}
		}
		return true;
	}
	return false;
}

boolean deletingTernaryTrie(struct ternaryTrieNode *ternaryTrieObj,char *key)
{
	return ternaryTrieRemover(ternaryTrieObj,key,0);
}