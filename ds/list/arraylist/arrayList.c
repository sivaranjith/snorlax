#include<stdio.h>
#include "arrayList.h"
int main()
{
	struct arrayList *head=NULL;
	int choice = 0, val;
	do
	{
		printf("\n1.Enter a new Value\n2.Remove Element at\n3.Remove value\n4.Print all values\n5.Exit:");
		scanf(" %d",&choice);
		switch(choice)
		{
			case 1: printf("\nEnter the value:");
				scanf(" %d",&val);
				addElementArrayList(&head,val);
				break;
			case 2: printf("\nEnter the index:");
				scanf(" %d",&val);
				removeElementArrayList(&head,val,true);
				break;
			case 3: printf("\nEnter the value:");
				scanf(" %d",&val);
				removeElementArrayList(&head,val,false);	
				break;
			case 4: printAll(head);
				break;
			case 5: printf("\n\nGood bye\n\n");
				return 0;
			case 6: printf("%d %d\n",head->size,head->length);
				break;
			default: printf("\nEnter a valid choice\n");
				break;
		}
	}while( choice != 0 );
}
