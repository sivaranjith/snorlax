#include<stdio.h>
#include "../linkedlist/linkedList.h"
int main()
{
	struct node *head;
	int choice,priVal;
	while(1)
	{
		printf("\n1.Enqueue at end\n2.Enqueue at begining\n3.Dequeue at end\n4.Dequeue at begining\n5.Print all\n6.Peek at end\n7.Peek at begining\n8.Exit:");
		scanf(" %d",&choice);
		switch(choice)
		{
			case 1: printf("Enter value:");
				scanf(" %d",&priVal);
				insertAtEnd(&head,priVal);
				break;
			case 2: printf("Enter value:");
				scanf(" %d",&priVal);
				insertAtBegining(&head,priVal);
				break;
			case 3: priVal = deleteLastVal(&head);
				printf("Dequeued value: %d\n",priVal);
				break;
			case 4: priVal = deleteFirstVal(&head);
				printf("Dequeued value: %d\n",priVal);
				break;
			case 5: printAll(head);
				break;
			case 6: priVal = lastValue(head);
				printf("Peeked value: %d\n",priVal);
				break;
			case 7: priVal = valueAt(head,1);
				printf("Peeked value: %d\n",priVal);
				break;
			case 8: printf("Good bye\n\n");
				return 0;
			default:printf("Enter correct value..\n");
		}
	}
}
