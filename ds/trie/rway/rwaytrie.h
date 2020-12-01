#include<stdio.h>
#include<stdlib.h>

#define boolean int
#define true 1
#define false 0

#define radix 26

//only for small letters it is done
struct trieNode
{
	int value;
	struct trieNode* next[radix];
};

struct trieNode* createTrie()
{
	struct trieNode* head = calloc(sizeof(struct trieNode),1);
	head->value = -1;
	return head;
}

boolean rWayTrieInsertor(struct trieNode* trieObj,char *key,int value,int index)
{
	char c = *(key + index) - 97;
	if(*(key + index) == '\0')
	{
		trieObj->value = value;
		return true;
	}

	if(trieObj->next[c] == NULL)
	{
		struct trieNode *temp = calloc(sizeof(struct trieNode),1);
		trieObj->next[c] = temp;	
	}

	return rWayTrieInsertor(trieObj->next[c],key,value,index + 1);
}

boolean insertRWayTrie(struct trieNode* trieObj,char *key,int value)
{
	if(*key == '\0')
	{
		return false;
	}
	return rWayTrieInsertor(trieObj,key,value,0);
}

int rWayTrieSearcher(struct trieNode* trieObj,char *key,int index)
{
	if(*(key + index) == '\0')
	{
		return trieObj->value;
	}
	else if(trieObj->next[*(key + index) - 97] == NULL)
	{
		return 0;
	}
	else
	{
		return rWayTrieSearcher(trieObj->next[*(key + index) - 97],key,index + 1);
	}

}

int searchRWayTrie(struct trieNode* trieObj,char *key)
{
	if(*key == '\0')
	{
		return 0;
	}
	return rWayTrieSearcher(trieObj,key,0);
}

void rWayTriePrinter(struct trieNode* trieObj,char *container,int index)
{
	int itr;
	if(index != 0)
	{
		printf("%s %d\n",container,trieObj->value);
	}
	for(itr = 0; itr < radix; ++itr)
	{
		if(trieObj->next[itr] != NULL)
		{
			container[index++] = itr + 97;
			container[index] = '\0';
			rWayTriePrinter(trieObj->next[itr],container,index);
			--index;
		}
	}
}

void printRWayTrie(struct trieNode* trieObj)
{
	char container[21];
	rWayTriePrinter(trieObj,container,0);
}

/*boolean rWayTrieRemover(struct trieNode* trieObj,char *key,int index)
{
	int itr;
	char c = *(key + index) - 97;

	boolean returnVal = false,lastCharacter = *(key + index) == '\0' && trieObj->value != 0;

	if(lastCharacter || trieObj->next[c] != NULL && rWayTrieRemover(trieObj->next[c],key,index + 1))
	{
		returnVal = !lastCharacter;
		if(lastCharacter || trieObj->next[c]->value == -1)
		{
			if(!lastCharacter)
			{
				struct trieNode *temp = trieObj->next[c];
				trieObj->next[c] = NULL;
				free(temp);
			}

			for(itr = 0; itr < radix; ++itr)
			{
				if(trieObj->next[itr] != NULL)
				{
					if(lastCharacter)
					{
						trieObj->value = 0;
					}
					return true;
				}
			}
			trieObj->value = -1;
			returnVal = true;

		}
	}
	return returnVal;
}*/

boolean rWayTrieRemover(struct trieNode* trieObj,char *key,int index)
{
	int itr;
	char c = *(key + index) - 97;
	boolean returnVal = false;
	if(*(key + index) == '\0')
	{
		if(trieObj->value != 0)
		{
			for(itr = 0; itr < radix; ++itr)
			{
				if(trieObj->next[itr] != NULL)
				{
					trieObj->value = 0;
					return true;
				}
			}
			trieObj->value = -1;
			returnVal = true;
		}
	}
	else if(trieObj->next[c] != NULL && rWayTrieRemover(trieObj->next[c],key,index + 1))
	{
		if(trieObj->next[c]->value == -1)
		{
			struct trieNode *temp = trieObj->next[c];
			trieObj->next[c] = NULL;
			free(temp);

			if(trieObj->value == 0)
			{
				for(itr = 0; itr < radix; ++itr)
				{
					if(trieObj->next[itr] != NULL)
					{
						return true;
					}
				}
				trieObj->value = -1;
			}
		}
		returnVal = true;
	}
	return returnVal;
}

boolean deletingRWayTrie(struct trieNode* trieObj,char *key)
{
	if(*key == '\0')
	{
		return false;
	}
	return rWayTrieRemover(trieObj,key,0);
}