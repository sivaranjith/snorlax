#include"minheap.h"

int main()
{
	int choice,priVal;
	struct minHeap *minHeapObj = createMinHeap();
	do
	{
		printf("\n1.Insert into min heap\n2.Delete from min heap\n3.Print min heap\n4.Search value\n5.Get Min value\n6.Exit: ");
		scanf(" %d",&choice);
		switch(choice)
		{
			case 1: printf("\nEnter the value: ");
					scanf(" %d",&priVal);
					insertToMinHeap(minHeapObj,priVal);
					break;
			case 2: printf("\nDeleted value: %d\n",deleteFromMinHeap(minHeapObj));
					break;
			case 3: printMinHeap(minHeapObj);
					break;
			case 4: printf("\nEnter the value: ");
					scanf(" %d",&priVal);
					if(searchMinHeap(minHeapObj,priVal))
					{
						printf("\nFOUND\n");
					}
					else
					{
						printf("\nNOT FOUND\n");
					}
					break;
			case 5: printf("\nThe min value is: %d\n",getMinValueFromMinHeap(minHeapObj));
					break;
			case 6: printf("\n\nGood Bye!\n\n");
					break;
			default:printf("\nEnter a proper value...\n");
					break;
		}
	}while(choice != 6);
}