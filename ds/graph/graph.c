#include"graph.h"

int main()
{
	int choice,vertexCount,priVal,secVal;

	printf("Enter max no.of.vertex:");
	scanf(" %d",&vertexCount);

	struct graph *graphObj = createGraph(vertexCount);
	struct node *head = NULL;
	int* connectionIt;

	do
	{
		printf("\n1.Enter a new vertex\n2.Delete a vertex\n3.Enter a edge\n4.Delete a edge\n5.Print\n6.Search Edge\n7.Reverse Graph\n8.DFS\n9.BFS\n10.Topological sort\n11.Strongly connected(kosaraju)\n12.kruskal's MST\n13.prim's MST\n14.Exit:");
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
			case 6: printf("\nEnter starting and ending vertex number: ");
					scanf(" %d %d",&priVal,&secVal);
					if(searchEdge(graphObj,priVal,secVal))
					{
						printf("FOUND\n");
					}
					else
					{
						printf("NOT-AVAILABLE\n");
					}
					break;
			case 7: graphObj = reverseGraph(graphObj);
					break;
			case 8: deapthFirstSearch(graphObj);
					break;
			case 9: breathFristSearch(graphObj);
					break;
			case 10:head = reversePostOrder(graphObj);
					printf("\n");
					while(head != NULL)
					{
						printf("%d,",head->key);
						head = head->next;
					}
					printf("\b \n");
					break;
			case 11:connectionIt = getConnectedComponent(graphObj);
					for(priVal = 0; priVal < vertexCount; ++priVal)
					{
						printf("%d => %d\n",priVal,*(connectionIt + priVal));
					}
					break;
			case 14:printf("\n\nGood Bye!!!\n\n");
				 	return;
			default:printf("\n\nEnter a proper value!\n\n");
					break;
		}
	}while(choice != 6);
}
