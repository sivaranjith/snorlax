#include<stdio.h>
#include<time.h>
#include "linkedList.h"
void main()
{
	struct node *head = NULL;
	int choice = 0, priVal = 0, secVal = 0;
//	struct time_t lastTime,now;
//	localtime(now);
//	return;
	while(1)
	{
		printf("\n1.Enter a value to the start\n2.Enter a value to the end\n3.Enter a value at a particular index\n4.Enter a value after a particular value\n5.Enter a value before a particular value\n6.Delete a particular Value\n7.Delete First Value\n8.Delete Last Value\n9.Delete previous value of\n10.Delete next value of\n11.Print value at\n12.Print all\n13.Exit:");
		scanf(" %d", &choice);
		switch(choice)
		{
			case 1: printf("Enter the new value:");
				scanf(" %d",&priVal);
				insertAtBegining(&head,priVal);
				break;
			case 2: printf("Enter the new Value:");
				scanf(" %d",&priVal);
				insertAtEnd(&head,priVal);
				break;
			case 3: printf("Enter the new Value and the indexValue:");
				scanf(" %d %d",&priVal,&secVal);
				insertAtIndex(&head,priVal,secVal);
				break;
			case 4: printf("Enter the new Value and the after Value:");
				scanf(" %d %d",&priVal,&secVal);
				insertAfter(&head,priVal,secVal);
				break;
			case 5: printf("Enter the new Value and the before Value:");
				scanf(" %d %d",&priVal,&secVal);
				insertBefore(&head,priVal,secVal);
				break;
			case 6: printf("Delete value:");
				scanf(" %d",&priVal);
				deleteVal(&head,priVal);
				break;
			case 7: deleteFirstVal(&head);
				break;
			case 8: deleteLastVal(&head);
				break;
			case 9: printf("Enter previous del val:");
				scanf(" %d",&priVal);
				deletePreVal(&head,priVal);
				break;
			case 10:printf("Enter next del val:");
				scanf(" %d",&priVal);
				deleteAfterVal(&head,priVal);
				break;
			case 11:printf("Index value:");
				scanf(" %d",&priVal);
				printf("the value is::%d\n",valueAt(head,priVal));
				break;
			case 12:printAll(head);
				break;
			case 13:printf("Good Bye\n\n");
				return;
			default:printf("Enter a proper value...\n\n");
		}
	}
}
