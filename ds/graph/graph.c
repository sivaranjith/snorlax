#include"graph.h"

int main()
{
	int choice,vertexCount,priVal,secVal;

	printf("Enter max no.of.vertex:");
	scanf(" %d",&vertexCount);

	struct graph *graphObj = createGraph(vertexCount);

	do
	{
		printf("\n1.Enter a new vertex\n2.Delete a vertex\n3.Enter a edge\n4.Delete a edge\n5.Print\n6.Exit:");
		scanf(" %d",&choice);

		switch(choice)
		{
			case 1: printf("\nEnter vertex number: ");
					scanf(" %d",&priVal);
					insertVertex(graphObj,priVal);
					break;
			case 2: printf("\nEnter vertex number: ");
					scanf(" %d",&priVal);
					deleteVertex(graphObj,priVal);
					break;
			case 3: printf("\nEnter starting and ending vertex number: ");
					scanf(" %d %d",&priVal,&secVal);
					insertEdge(graphObj,priVal,secVal);
					break;
			case 4: printf("\nEnter starting and ending vertex number: ");
					scanf(" %d %d",&priVal,&secVal);
					deleteEdge(graphObj,priVal,secVal);
					break;
			case 5: printGraph(graphObj);
					break;
			case 6: printf("\n\nGood Bye!!!\n\n");
					break;
			default:printf("\n\nEnter a proper value!\n\n");
					break;
		}
	}while(choice != 6);
}
