#include"maxheap.h"

int main()
{
	int choice,priVal;
	struct maxHeap *maxHeapObj = createMaxHeap();
	do
	{
		printf("\n1.Insert into max heap\n2.Delete from max heap\n3.Print max heap\n4.Search value\n5.Get Max value\n6.Exit: ");
		scanf(" %d",&choice);
		switch(choice)
		{
			case 1: printf("\nEnter the value: ");
					scanf(" %d",&priVal);
					insertToMaxHeap(maxHeapObj,priVal);
					break;
			case 2: printf("\nDeleted value: %d\n",deleteFromMaxHeap(maxHeapObj));
					break;
			case 3: printMaxHeap(maxHeapObj);
					break;
			case 4: printf("\nEnter the value: ");
					scanf(" %d",&priVal);
					if(searchMaxHeap(maxHeapObj,priVal))
					{
						printf("\nFOUND\n");
					}
					else
					{
						printf("\nNOT FOUND\n");
					}
					break;
			case 5: printf("\nThe max value is: %d\n",getMaxValueFromMaxHeap(maxHeapObj));
					break;
			case 6: printf("\n\nGood Bye!\n\n");
					break;
			default:printf("\nEnter a proper value...\n");
					break;
		}
	}while(choice != 6);
}