#include<stdio.h>
#include<stdlib.h>

#define boolean int
#define true 1
#define false 0

struct huffmanTrieNode
{
	char c;
	int frequency;
	struct huffmanTrieNode *left,*right;
};

struct huffmanQueueNode
{
	struct huffmanTrieNode *key;
	struct huffmanQueueNode *next;
};

void insertInIncreasingOrder(struct huffmanQueueNode **head, struct huffmanTrieNode *priVal)
{
	struct huffmanQueueNode *temp = calloc(sizeof(struct huffmanQueueNode),1);
	temp->key = priVal;
	
	if(*head == NULL || (*head)->key->frequency > priVal->frequency)
	{
		temp->next = *head;
		*head = temp;
	}
	else
	{
		struct huffmanQueueNode *itr = *head;
		while(itr->next != NULL && itr->next->key->frequency < priVal->frequency)
		{
			itr = itr->next;
		}
		temp->next = itr->next;
		itr->next = temp;
	}
}

struct huffmanTrieNode* deleteFirstVal(struct huffmanQueueNode **head)
{
	struct huffmanTrieNode *freePt = NULL;
	if(*head != NULL)
	{
		freePt = (*head)->key;
		*head = (*head)->next;
	}
	return freePt;
}

struct huffmanTrieNode* createHuffmanTrie()
{
	struct huffmanQueueNode* queue = NULL;
	struct huffmanTrieNode *temp = NULL,*tempHolder1,*tempHolder2;
	FILE *filePt;
	char inputLine[10],c;

	filePt = fopen("frequency.txt","r");
	if(!filePt)
	{
		return NULL;
	}

	while(fgets(inputLine,10,filePt) != NULL)
	{
		temp = calloc(sizeof(struct huffmanTrieNode),1);
		temp->c = inputLine[0];
		temp->frequency = inputLine[2] - '0';
		if(inputLine[3] >= '0' && inputLine[3] <= '9')
		{
			temp->frequency = temp->frequency*10 + inputLine[3] - '0';
		}

		insertInIncreasingOrder(&queue,temp);
	}

	while(true)
	{
		tempHolder1 = deleteFirstVal(&queue);
		tempHolder2 = deleteFirstVal(&queue);
		if(tempHolder2 == NULL)
		{
			return tempHolder1;
		}

		temp = calloc(sizeof(struct huffmanTrieNode),1);
		temp->c = '\0';
		temp->frequency = tempHolder1->frequency + tempHolder2->frequency;
		temp->left = tempHolder1;
		temp->right = tempHolder2;
		insertInIncreasingOrder(&queue,temp);
	}
	return NULL;
}

void printHuffmanTrie(struct huffmanTrieNode *head)
{
	if(head == NULL)
	{
		return;
	}

	if(head->c == '\0')
	{
		printf("Internal node");
	}
	else
	{
		printf("%c",head->c);
	}
	
	printf(" %d\n",head->frequency);
	printHuffmanTrie(head->left);
	printHuffmanTrie(head->right);
}

void getEncoder(struct huffmanTrieNode *head,char **encoder,char *queue,int index)
{
	if(head == NULL)
	{
		return;
	}
	
	if(head->c >= 'a' && head->c <= 'z')
	{
		int itr = 0;
		while(*(queue + itr) != '\0')
		{
			encoder[head->c - 'a'][itr] = queue[itr];
			++itr;
		}
	}

	queue[index] = '0';
	getEncoder(head->left,encoder,queue,index+1);
	queue[index] = '1';
	getEncoder(head->right,encoder,queue,index+1);
	queue[index] = '\0';

}

char* encodeString(char **encoder,char *source)
{
	int itr1 = 0,itr2 = 0,index = 0;
	char *returnVal = calloc(sizeof(char),200),c;
	while( *(source + itr1) != '\0' )
	{
		c = *(source + itr1) - 'a';
		for(itr2 = 0; encoder[c][itr2] != '\0';++itr2)
		{
			returnVal[index++] = encoder[c][itr2];
		}
		++itr1;
	}

	returnVal[index] = '\0';
	return returnVal;
}

char* decodeString(struct huffmanTrieNode *head,char *source)
{
	struct huffmanTrieNode *temp;
	char *returnVal = calloc(sizeof(char),25);
	int itr1 = 0,index = 0;
	while(*(source + itr1) != '\0')
	{
		temp = head;
		while(temp->left != NULL && temp->right != NULL)
		{
			if(*(source + itr1) == '0')
			{
				temp = temp->left;
			}
			else if(*(source + itr1) == '1')
			{
				temp = temp->right;
			}
			++itr1;
		}
		returnVal[index++] = temp->c;
	}
	returnVal[index] = '\0';
	return returnVal;
}

void getWriteableTrie(struct huffmanTrieNode *head,char *encodedTrie,int* index)
{
	if(head == NULL)
	{
		return;
	}

	if(head->c != '\0')
	{
		int itr = 7,c = head->c;
		encodedTrie[(*index)++] = '1';
		while(itr >= 0)
		{
			encodedTrie[(*index)+itr] = c%2 + '0';
			c = c/2; 
			--itr;
		}
		*index += 8;
		return;
	}

	encodedTrie[(*index)++] = '0';
	getWriteableTrie(head->left,encodedTrie,index);
	getWriteableTrie(head->right,encodedTrie,index);
}

void writeTrieToFile(struct huffmanTrieNode *head,char *fileName)
{
	char *encodedTrie = calloc(sizeof(char),500);
	int index = 0;
	FILE *filePt;
	filePt = fopen(fileName,"w");

	if(!filePt)
	{
		return;
	}

	getWriteableTrie(head,encodedTrie,&index);

	fprintf(filePt,"%s\n",encodedTrie);
	fclose(filePt);
	free(encodedTrie);
}

struct huffmanTrieNode* constructTrie(char *encodedTrie,int *index)
{
	if(*(encodedTrie + (*index)++) == '1')
	{
		int itr = 0, c;
		while(itr++ <= 7)
		{
			c = *(encodedTrie + (*index)++) - '0' +  c* 2;
		}
		struct huffmanTrieNode *temp = calloc(sizeof(struct huffmanTrieNode),1);
		temp->c = c;
		return temp;
	}

	struct huffmanTrieNode *tempHolder1 = constructTrie(encodedTrie,index);
	struct huffmanTrieNode *tempHolder2 = constructTrie(encodedTrie,index);

	struct huffmanTrieNode *temp = calloc(sizeof(struct huffmanTrieNode),1);
	temp->c = '\0';
	temp->left = tempHolder1;
	temp->right = tempHolder2;
	return temp;
}

void readTrieFromFile(char *fileName)
{
	char *encodedTrie = calloc(sizeof(char),500);
	int index = 0;
	FILE *filePt;
	filePt = fopen(fileName,"r");

	if(!filePt)
	{
		return;
	}

	fgets(encodedTrie,500,filePt);
	printHuffmanTrie(constructTrie(encodedTrie,&index));

	fclose(filePt);
	free(encodedTrie);
}