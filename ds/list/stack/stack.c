#include<stdio.h>
#include "../linkedlist/linkedList.h"
int main()
{
	struct node *head = NULL;
	int choice,priVal;
	while(1)
	{
		printf("\n1.Push value\n2.Pop value\n3.Print all\n4.Peek\n5.Exit:");
		scanf(" %d",&choice);
		switch(choice)
		{
			case 1: printf("Enter the value:");
				scanf(" %d",&priVal);
				insertAtBegining(&head,priVal);
				break;
			case 2: priVal = deleteFirstVal(&head);
				printf("Poped value: %d\n",priVal);
				break;
			case 3: printAll(head);
				break;
			case 4: priVal = valueAt(head,1);
				printf("Peeked value: %d\n",priVal);
				break;
			case 5: printf("Good bye\n\n");
				return 0;
			default:printf("Enter a proper value\n");
		}
	}
}
