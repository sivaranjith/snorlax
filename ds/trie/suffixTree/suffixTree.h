#include<stdio.h>
#include<stdlib.h>

#define boolean int
#define false 0;
#define true 1;

#define radix 26

struct suffixTree
{
	char *key;
	int length;
	struct suffixTree *next[radix + 1];
};

void insertIntoSuffixTree(struct suffixTree* head,int index,char *key)
{
	struct suffixTree *temp,*dollarNode = head->next[radix],*parent = head,*newNode = calloc(sizeof(struct suffixTree),1);
	int itr,start = index,insertPoint = *(key + index) - 'a',length = 0;
	char *keyPt = key;
	temp = head->next[insertPoint];
	while(temp != NULL)
	{
		for(itr = 0; itr < temp->length; ++itr,++index)
		{
			if(*(key + index) != temp->key[itr])
			{
				break;
			}
		}

		if(itr != temp->length)
		{
			--index;
			insertPoint = temp->key[itr] - 'a';
			keyPt = temp->key;
			start = itr;
			temp->length = start;
			parent = temp;
			break;
		}

		insertPoint = *(key + index) - 'a';
		parent = temp;
	}
	itr = start;
	while(*(keyPt + itr) != '\0')
	{
		++length;
		++itr;
	}
	newNode->key = calloc(sizeof(char),length);
	for(itr = 0;itr < length; ++start,++itr)
	{
		newNode->key[itr] = *(keyPt + start);
	}
	if(temp != NULL)
	{
		temp->key[temp->length] = '\0';
		temp = temp->next[insertPoint];
		for(itr = 0; itr <= radix; ++itr)
		{
			newNode->next[itr] = parent->next[itr];
		}
	}
	newNode->length = itr;
	parent->next[insertPoint] = newNode;
	newNode->next[radix] = dollarNode;
}

struct suffixTree* createSuffixTree(char *primaryStr)
{
	struct suffixTree *head = calloc(sizeof(struct suffixTree),1),*dollarNode = calloc(sizeof(struct suffixTree),1);
	int index,itr;
	
	dollarNode->key = calloc(sizeof(char),1);
	dollarNode->key[0] = '$';
	dollarNode->length = 1;
	head->next[radix] = dollarNode;
	
	for(index = 0; *(primaryStr + index) != '\0'; ++index)
	{
		insertIntoSuffixTree(head,index,primaryStr);
	}
	return head;
}

void suffixTreePrinter(struct suffixTree *suffixTreeObj,char *key,int index)
{
	int itr,itr1;
	if(*(key + index - 1) == '$')
	{
		printf("%s\n",key);
	}
	for(itr = 0; itr <= radix; ++itr)
	{
		if(suffixTreeObj->next[itr] != NULL)
		{
			for(itr1 = 0; suffixTreeObj->next[itr]->key[itr1] != '\0'; ++itr1)
			{
				*(key + index++) = suffixTreeObj->next[itr]->key[itr1];
			}
			suffixTreePrinter(suffixTreeObj->next[itr],key,index);
			for(itr1 = 0; suffixTreeObj->next[itr]->key[itr1] != '\0'; ++itr1)
			{
				*(key + index--) = '\0';
			}
		}
	}
}

void printSuffixTree(struct suffixTree *suffixTreeObj)
{
	char *a = calloc(sizeof(char),21);
	suffixTreePrinter(suffixTreeObj,a,0);
}

boolean suffixTreeSearcher(struct suffixTree *suffixTreeObj,struct suffixTree *dollarNode,char *ipStr,int index)
{
	int itr;
	if(suffixTreeObj == NULL)
	{
		return 0;
	}
	for(itr = 0; suffixTreeObj->key[itr] != '\0' && *(ipStr + index) != '\0'; ++itr,++index)
	{
		if(suffixTreeObj->key[itr] != *(ipStr + index))
		{
			return 0;
		}
	}
	if(*(ipStr + index) == '\0')
	{
		return 1;
	}
	return suffixTreeSearcher(suffixTreeObj->next[*(ipStr + index) - 'a'],dollarNode,ipStr,index);
}

boolean checkForSubString(struct suffixTree *suffixTreeObj,char *ipStr)
{
	return suffixTreeSearcher(suffixTreeObj->next[*ipStr - 'a'],suffixTreeObj->next[radix],ipStr,0);
}