#include<stdio.h>
#include<stdlib.h>
#define boolean int
#define true 1
#define false 0

struct graph
{
	int vertexCount;
	struct graphNode
	{
		int graphNodeVal;
		struct graphNode *next;
	}**graphList;
};

struct node
{
	int key,val;
	struct node *next;
};

void insertAtBegining(struct node **head, int priVal,int secVal)
{
	struct node *temp = (struct node*)malloc(sizeof(struct node));
	temp->key = priVal;
	temp->val = secVal;
	temp->next = *head;
	*head = temp;
}

int deleteFirstVal(struct node **head)
{
	struct node *freePt;
	int val = 0;
	if(*head != NULL)
	{
		freePt = *head;
		*head = (*head)->next;
		val = freePt->key;
		free(freePt);
	}
	return val;
}

void insertAtEnd(struct node **head, int priVal,int secVal)
{
	struct node *temp = (struct node*)malloc(sizeof(struct node));
	temp->key = priVal;
	temp->val = secVal;
	temp->next = NULL;
	if(*head == NULL)
	{
		*head = temp;
	}
	else
	{
		struct node *itr = *head;
		while(itr->next != NULL)
		{
			itr = itr->next;
		}
		itr->next = temp;
	}
}

struct graph* createGraph(int vertexCount)
{
	struct graph *graphObj = malloc(sizeof(struct graph));
	graphObj->vertexCount = vertexCount;
	graphObj->graphList = malloc(sizeof(struct graphNode*)*vertexCount);
	return graphObj;
}

boolean searchEdge(struct graph *graphObj,int startingVertex,int endingVertex)
{
	struct graphNode* temp = *(graphObj->graphList + startingVertex);
	while(temp != NULL && temp->graphNodeVal > endingVertex)
	{
		temp = temp->next;
	}
	if(temp != NULL && temp->graphNodeVal == endingVertex)
	{
		return true;
	}
	return false;
}

void insertVertex(struct graph *graphObj,int key)
{
	if(key >= graphObj->vertexCount)
	{
		return;
	}
	if( *(graphObj->graphList + key) == NULL)
	{
		*(graphObj->graphList + key) = malloc(sizeof(struct graphNode));
		(*(graphObj->graphList + key))->graphNodeVal = -1;
	}
}

void deleteVertex(struct graph *graphObj,int key)
{
	if( *(graphObj->graphList + key) != NULL )
	{
		int itr;
		struct graphNode *temp,**freePt;
		while(*(graphObj->graphList + key) != NULL)
		{
			temp = *(graphObj->graphList + key);
			*(graphObj->graphList + key) = temp->next;
			free(temp);
		}

		for(itr = 0; itr < graphObj->vertexCount; ++itr)
		{
			temp = *(graphObj->graphList + itr);
			if(temp == NULL || temp->graphNodeVal == -1)
			{
				continue;
			}
			freePt = (graphObj->graphList + itr);
			while(*freePt != NULL && (*freePt)->graphNodeVal > key)
			{
				freePt = &(*freePt)->next;
			}
			if(*freePt != NULL && (*freePt)->graphNodeVal == key)
			{
				temp = *freePt;
				*freePt = (*freePt)->next;
				free(temp);
				if(*(graphObj->graphList + itr) == NULL)
				{
					struct graphNode *newNode = malloc(sizeof(struct graphNode));
					newNode->graphNodeVal = -1;
					*(graphObj->graphList + itr) = newNode;
				}
			}
		}
	}
}

void insertEdge(struct graph *graphObj,int startingVertex,int endingVertex)
{
	if(startingVertex >= graphObj->vertexCount || endingVertex >= graphObj->vertexCount)
	{
		return;
	}
	
	struct graphNode *temp = *(graphObj->graphList + startingVertex),*newNode = malloc(sizeof(struct graphNode));
	newNode->graphNodeVal = endingVertex;
	if(temp == NULL || *(graphObj->graphList + endingVertex) == NULL)
	{
		return;
	}
	//this else if and else should be combined! this is really bad coding!!
	else if(temp->graphNodeVal < endingVertex)
	{
		newNode->next = *(graphObj->graphList + startingVertex);
		*(graphObj->graphList + startingVertex) = newNode;
		if(newNode->next->graphNodeVal == -1)
		{
			temp = newNode->next;
			newNode->next = NULL;
			free(temp);
		}
	}
	else
	{
		while(temp->next != NULL && temp->next->graphNodeVal > endingVertex)
		{
			temp = temp->next;
		}

		if(temp->next == NULL || temp->next->graphNodeVal != endingVertex)
		{
			newNode->next = temp->next;
			temp->next = newNode;
		}	
	}

}

void deleteEdge(struct graph *graphObj,int startingVertex,int endingVertex)
{
	if(startingVertex >= graphObj->vertexCount || endingVertex >= graphObj->vertexCount)
	{
		return;
	}

	struct graphNode *temp = *(graphObj->graphList + startingVertex),**freePt;
	if(temp == NULL || temp->graphNodeVal == -1)
	{
		return;
	}
	freePt = (graphObj->graphList + startingVertex);
	while(*freePt != NULL && (*freePt)->graphNodeVal > endingVertex)
	{
		freePt = &(*freePt)->next;
	}

	if(*freePt != NULL && (*freePt)->graphNodeVal == endingVertex)
	{
		temp = *freePt;
		*freePt = (*freePt)->next;
		free(temp);
	}

	if(*(graphObj->graphList + startingVertex) == NULL)
	{
		struct graphNode *newNode = malloc(sizeof(struct graphNode));
		newNode->graphNodeVal = -1;
		*(graphObj->graphList + startingVertex) = newNode;
	}
}

void printGraph(struct graph *graphObj)
{
	int itr;
	struct graphNode *temp;
	for(itr = 0; itr < graphObj->vertexCount; ++itr)
	{
		temp = *(graphObj->graphList + itr);
		if(temp == NULL)
		{
			continue;
		}
		printf("\n %d ",itr);
		while(temp != NULL)
		{
			printf("-> %d ",temp->graphNodeVal);
			temp = temp->next;
		}
		printf("\n");
	}
}

struct graph* reverseGraph(struct graph *graphObj)
{
	struct graph *reverseGraphObj = createGraph(graphObj->vertexCount);
	int itr;
	
	for(itr = 0; itr < graphObj->vertexCount; ++itr)
	{
		if((graphObj->graphList + itr) != NULL)
		{
			insertVertex(reverseGraphObj,itr);
		}
	}
	
	for(itr = 0; itr < graphObj->vertexCount; ++itr)
	{
		struct graphNode *temp = *(graphObj->graphList + itr);
		if(temp->graphNodeVal == -1)
		{
			continue;
		}
		while(temp != NULL)
		{
			insertEdge(reverseGraphObj,temp->graphNodeVal,itr);
			temp = temp->next;
		}
	}

	return reverseGraphObj;
}

void graphSearcher(struct graph *graphObj,struct node *head,int* dist,void (*insertionPoint)(struct node **,int,int))
{
	//this else if make sure for multiple starting point even! so graph need not be strongly connected graph!
	if(head == NULL)
	{
		int itr;
		for(itr = 0; itr < graphObj->vertexCount; ++itr)
		{
			struct graphNode *temp = *(graphObj->graphList + itr);
			if(*(dist + itr) == 0 && temp != NULL && temp->graphNodeVal != -1)
			{
				printf("1::%d <=> 1\n",itr );
				insertionPoint(&head,itr,1);
				graphSearcher(graphObj,head,dist,insertionPoint);
				break;
			}
		}
		return;
	}

	int i,key = head->key,val = head->val;
	deleteFirstVal(&head);
	printf("%d %d %d\n",key,val,*(dist + key));
	if( *(dist + key) == 0)
	{
		struct graphNode *temp = *(graphObj->graphList + key);
		*(dist + key) = val;
		if(temp->graphNodeVal != -1)
		{
			while(temp != NULL)
			{
				printf("2::%d <=> %d\n",temp->graphNodeVal,val + 1 );
				insertionPoint(&head,temp->graphNodeVal,val + 1);
				temp = temp->next;
			}
		}
	}
	graphSearcher(graphObj,head,dist,insertionPoint);
}

void graphSearch(struct graph *graphObj,void (*insertionPoint)(struct node **,int,int))
{
	int* dist = malloc(sizeof(int)*(graphObj->vertexCount));
	int itr;
	struct node *head = NULL;

	//can't believe but when i insert all and do a bfs and then again delete some node and make it multi source no malloc doesn't give 0 in all nodes
	for(itr = 0; itr < graphObj->vertexCount; ++itr)
	{
		*(dist + itr) = 0;
	}
	for(itr = 0; itr < graphObj->vertexCount; ++itr)
	{
		if( (graphObj->graphList + itr) != NULL && (*(graphObj->graphList + itr))->graphNodeVal != -1)
		{
			printf("0::%d <=> 1\n",itr );
			insertionPoint(&head,itr,1);
			break;
		}
	}

	graphSearcher(graphObj,head,dist,insertionPoint);

	for(itr = 0; itr < graphObj->vertexCount; ++itr)
	{
		printf("%d => %d\n", itr,*(dist + itr) - 1);
	}
}

void deapthFirstSearch(struct graph *graphObj)
{
	graphSearch(graphObj,insertAtBegining);
}

void breathFristSearch(struct graph *graphObj)
{
	graphSearch(graphObj,insertAtEnd);
}