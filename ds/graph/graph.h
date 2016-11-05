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

struct graph* createGraph(int vertexCount)
{
	struct graph *graphObj = malloc(sizeof(struct graph));
	graphObj->vertexCount = vertexCount;
	graphObj->graphList = malloc(sizeof(struct graphNode*)*vertexCount);
	return graphObj;
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
			while((*freePt)->graphNodeVal > key)
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
	if(startingVertex >= graphObj->vertexCount || endingVertex >= endingVertex)
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
	if(startingVertex >= graphObj->vertexCount || endingVertex >= endingVertex)
	{
		return;
	}

	struct graphNode *temp = *(graphObj->graphList + startingVertex),**freePt;
	if(temp == NULL || temp->graphNodeVal == -1)
	{
		return;
	}
	freePt = (graphObj->graphList + startingVertex);
	while((*freePt)->graphNodeVal > endingVertex)
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