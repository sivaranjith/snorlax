#include "graph_1.h"

int main()
{
	int choice,priVal,secVal,temp1,temp2,vertexCount;
	struct node* head;

	printf("Enter max no.of.vertex:");
	scanf(" %d",&vertexCount);

	struct graph *graphObj = createGraph(vertexCount);
	while(true)
	{
		printf("1.Insert Vertex\n2.Insert Edge\n3.Print Graph\n4.Max Flow Algorithm\n5.Exit: ");
		scanf(" %d",&choice);
		switch(choice)
		{
			case 1: printf("\nEnter vertex number: ");
					scanf(" %d",&priVal);
					insertVertex(graphObj,priVal);
					break;
			case 2: printf("\nEnter starting and ending vertex number and capacity: ");
					scanf(" %d %d %d",&priVal,&secVal,&temp1);
					insertEdgeWithCapacity(graphObj,priVal,secVal,temp1);
					break;
			case 3: printGraph(graphObj);
					break;
			case 4: head = maxFlow(graphObj,&priVal);
					printf("\nMaximum flow through graph:%d\n\n",priVal);
					printf("\nMinimum cut vertex: ");
					while(head != NULL)
					{
						printf("%d ",head->key);
						head = head->next;
					}
					printf("\n\n");
					break;
			case 5: printf("\n\nGood bye!!\n\n");
					return 0;
			default:printf("\nEnter a correct value!!\n");
					break;

		}
	}
}