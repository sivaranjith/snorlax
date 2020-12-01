#include<stdio.h>
#include"binaryTree.h"

int main()
{
	int priVal,secVal,choice;
	struct biNode *root = NULL;
	while(1)
	{
		printf("\n1.Insert a number\n2.Search for a number\n3.Delete a number\n4.Print\n5.Exit:");
		scanf(" %d",&choice);
		switch(choice)
		{
			case 1: printf("\nEnter the number: ");
				scanf(" %d",&priVal);
				printf("\nEnter the search value: ");
				scanf(" %d",&secVal);
				insertToBinaryTree(&root,priVal,secVal);
				break;
			case 2: printf("\nEnter the number: ");
				scanf(" %d",&priVal);
				if(searchInBinaryTree(root,priVal) == NULL)
				{
					printf("\nMiss\n");
				}
				else
				{
					printf("\nHIT\n");
				}
				break;
			case 3: printf("\nEnter the number: ");
				scanf(" %d",&priVal);
				deleteFromBinaryTree(&root,priVal);
				break;
			case 4: printBinaryTree(root);
				break;
			case 5: printf("Good bye..\n\n");
				return;
			default:printf("\nEnter a proper value!!\n");
		}
	}
}
