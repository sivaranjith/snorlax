#include"avl.h"

int main()
{
	int priVal,choice;
	struct avlNode *root = NULL;
	while(1)
	{
		printf("\n1.Insert a number\n2.Search for a number\n3.Delete a number\n4.Print\n5.Exit:");
		scanf(" %d",&choice);
		switch(choice)
		{
			case 1: printf("\nEnter the number: ");
				scanf(" %d",&priVal);
				insertToAVLTree(&root,priVal);
				break;
			case 2: printf("\nEnter the number: ");
				scanf(" %d",&priVal);
				if(searchInAVLTree(root,priVal) == NULL)
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
				deleteFromAVLTree(&root,priVal);
				break;
			case 4: printAVLTree(root);
				break;
			case 5: printf("Good bye..\n\n");
				return;
			default:printf("\nEnter a proper value!!\n");
		}
	}
}
