#include<stdio.h>
#include<stdlib.h>
#define boolean int
#define false 0
#define true 1

int input = 0;

struct graph
{
	int vertexCount;
	struct graphNode
	{
		int graphNodeVal,flow,capacity;
		boolean isNormal;
		struct graphNode *next;
	}**graphList;
};

struct node
{
	int key;
	struct node *next;
};

void insertAtBegining(struct node **head, int priVal)
{
	struct node *temp = calloc(sizeof(struct node),1);
	temp->key = priVal;
	temp->next = *head;
	*head = temp;
}

struct graph* createGraph(int vertexCount)
{
	struct graph *graphObj = calloc(sizeof(struct graph),1);
	graphObj->vertexCount = vertexCount;
	graphObj->graphList = calloc(sizeof(struct graphNode*),vertexCount);
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
		*(graphObj->graphList + key) = calloc(sizeof(struct graphNode),1);
		(*(graphObj->graphList + key))->graphNodeVal = -1;
	}
}

void insertEdgeWithCapacityResidual(struct graph *graphObj,int startingVertex,int endingVertex,int capacity,boolean isNormal)
{
	if(startingVertex >= graphObj->vertexCount || endingVertex >= graphObj->vertexCount)
	{
		return;
	}
	
	struct graphNode *temp = *(graphObj->graphList + startingVertex),*newNode = calloc(sizeof(struct graphNode),1);
	newNode->graphNodeVal = endingVertex;
	newNode->capacity = capacity;
	newNode->isNormal = isNormal;
	if(temp == NULL)
	{
		free(newNode);
		return;
	}
	//this else if and else should be combined! this is really bad coding!!
	else if(temp->graphNodeVal < endingVertex)
	{
		newNode->next = *(graphObj->graphList + startingVertex);
		*(graphObj->graphList + startingVertex) = newNode;
		if(newNode->next->graphNodeVal == -1 && newNode->isNormal)
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

void insertEdgeWithCapacity(struct graph *graphObj,int startingVertex,int endingVertex,int capacity)
{
	insertEdgeWithCapacityResidual(graphObj,startingVertex,endingVertex,capacity,true);
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

	temp = *(graphObj->graphList + startingVertex);
	if(temp == NULL || (temp->next == NULL && !temp->isNormal))
	{
		struct graphNode *newNode = calloc(sizeof(struct graphNode),1);
		newNode->graphNodeVal = -1;
		if(temp == NULL)
		{
			*(graphObj->graphList + startingVertex) = newNode;
		}
		else
		{
			temp->next = newNode;
		}
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
			printf("-> %d(%d,%d,%d) ",temp->graphNodeVal,temp->flow,temp->capacity,temp->isNormal);
			temp = temp->next;
		}
		printf("\n");
	}
}

struct graph* cloneGraph(struct graph* graphObj)
{
	struct graph* clonedGraph = createGraph(graphObj->vertexCount);
	int itr;
	struct graphNode *temp;
	for(itr = 0; itr < clonedGraph->vertexCount; ++itr)
	{
		temp = *(graphObj->graphList + itr);
		if( temp != NULL )
		{
			insertVertex(clonedGraph,itr);
			if(temp->graphNodeVal != -1)
			{
				while(temp != NULL)
				{
					insertEdgeWithCapacityResidual(clonedGraph,itr,temp->graphNodeVal,temp->capacity,true);
					temp = temp->next;
				}
			}
		}
	}
	return clonedGraph;
}

//because nodeVisited being long instead of linked list we can only have at max of 32-nodes in the graph(long is 32 bit)
struct node* dfsSearch(struct graph* graphObj,int currentPosition,int *residualValue,long nodeVisited)
{
	struct node* head = NULL;
	if(currentPosition == graphObj->vertexCount - 1)
	{
		insertAtBegining(&head,currentPosition);
		return head;
	}

	struct graphNode *temp = *(graphObj->graphList + currentPosition);

	if(temp == NULL || temp->graphNodeVal == -1)
	{
		return head;
	}
	while(temp != NULL)
	{
		if(temp->capacity > 0 && temp->isNormal && !((nodeVisited>>(temp->graphNodeVal))&1))
		{
			nodeVisited ^= (1 << currentPosition);
			head = dfsSearch(graphObj,temp->graphNodeVal,residualValue,nodeVisited);
			if(head != NULL)
			{
				insertAtBegining(&head,currentPosition);
				if(*residualValue == -1 || *residualValue > temp->capacity)
				{
					*residualValue = temp->capacity;
				}
				break;
			}
		}
		temp = temp->next;
	}
	return head;
}

void updateEdgeValue(struct graph* graphObj,int startingPoint,int endingPoint,int residualValue,boolean isResidual)
{
	struct graphNode *temp = *(graphObj->graphList + startingPoint),*temp1;
	while(temp != NULL && temp->graphNodeVal != endingPoint)
	{
		temp = temp->next;
	}
	if(temp != NULL)
	{
		if(!isResidual)
		{
			temp->flow += residualValue;
		}
		else
		{
			temp->capacity -= residualValue;
			temp1 = *(graphObj->graphList + endingPoint);
			while(temp1 != NULL && temp1->graphNodeVal != startingPoint)
			{
				temp1 = temp1->next;
			}
			if(temp1 == NULL)
			{
				insertEdgeWithCapacityResidual(graphObj,endingPoint,startingPoint,residualValue,false);
			}
			else
			{
				temp1->capacity += residualValue;
			}
			if(temp->capacity == 0)
			{
				deleteEdge(graphObj,startingPoint,endingPoint);
			}
		}
	}
}

struct node* normalDFSSearch(struct graph* graphObj,int currentPosition,long nodeVisited)
{
	struct node* head = NULL;
	struct graphNode *temp = *(graphObj->graphList + currentPosition);
	while(temp != NULL)
	{
		if(temp->graphNodeVal == -1)
		{
			return NULL;
		}
		else if(temp->capacity > 0 && temp->isNormal && !((nodeVisited>>(temp->graphNodeVal))&1))
		{
			nodeVisited ^= (1 << currentPosition);
			head = normalDFSSearch(graphObj,temp->graphNodeVal,nodeVisited);
			insertAtBegining(&head,temp->graphNodeVal);
		}
		temp = temp->next;
	}
	return head;
}

struct node* maxFlow(struct graph* graphObj,int *sum)
{
	struct graph* residualGraph = cloneGraph(graphObj);
	struct graphNode *temp;
	struct node* head;
	int residualValue;
	*sum = 0;
	do
	{
		residualValue = -1;
		head = dfsSearch(residualGraph,0,&residualValue,0L);
		if(head != NULL)
		{
			int startingPoint = head->key,endingPoint = -1;
			head = head->next;
			while(head != NULL)
			{
				endingPoint = head->key;
				updateEdgeValue(graphObj, startingPoint, endingPoint, residualValue, false);
				
				updateEdgeValue(residualGraph, startingPoint, endingPoint, residualValue, true);

				startingPoint = endingPoint;
				head = head->next;
			}
		}
		else
		{
			break;
		}
		*sum += residualValue;
	}while(true);

	head = normalDFSSearch(residualGraph,0,0L);
	insertAtBegining(&head,0);
	return head;
}