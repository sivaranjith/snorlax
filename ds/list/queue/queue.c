#include<stdio.h>
#include "../linkedlist/linkedList.h"
int main()
{
	int choice,priVal;
	struct node *head = NULL;
	while(1)
	{
		printf("\n1.Enqueue a value\n2.Dequeue a value\n3.Print all\n4.First Value\n5.Exit:");
		scanf(" %d",&choice);
		switch(choice)
		{
			case 1: printf("Enter the value:");
				scanf(" %d",&priVal);
				insertAtEnd(&head,priVal);
				break;
			case 2: priVal = deleteFirstVal(&head); 
				printf("The dequeued value: %d\n",priVal);
				break;
			case 3: printAll(head);
				break;
			case 4: priVal = valueAt(head,1);
				printf("The First Value: %d\n",priVal);
				break;
			case 5: printf("Good bye\n\n");
				return 0;
			default:printf("Enter a proper value again\n");
		}
	}
}
