#include"bplus.h"

int main()
{
	int priVal,choice/*,**ptr*/;
	struct bPlusNode *obj = NULL;

	/*ptr = (int**)malloc(sizeof(int*)*5);
	for(priVal=0;priVal<5;++priVal)
	{
		*(ptr+priVal) = (int*)malloc(sizeof(int)*5);
	}

	for(priVal = 0; priVal < 5 ; ++priVal)
	{
		for(choice = 0; choice < 5; ++choice)
		{
			printf("%d ",*(*(ptr+priVal)+choice));
		}
		printf("\n");
	}*/

	while(1)
	{
		printf("\nEnter the node size: ");
		scanf(" %d",&priVal);
		if(priVal > 3)
		{
			break;
		}
		else if(priVal == 3)
		{
			printf("\nUse a red black tree in this case.\n\n");
			return;
		}
		else if(priVal == 2)
		{
			printf("\nUse a avl tree in this case.\n\n");
			return;
		}
	}
	obj = createBPlusNode(priVal);
	while(1)
	{
		printf("\n1.Insert a number\n2.Search for a number\n3.Delete a number\n4.Print\n5.Exit:");
		scanf(" %d",&choice);
		switch(choice)
		{
			case 1: printf("\nEnter the number: ");
				scanf(" %d",&priVal);
				insertToBPlusTree(obj,priVal);
				break;
			case 2: printf("\nEnter the number: ");
				scanf(" %d",&priVal);
				if(searchInBPlusTree(obj,priVal) == NULL)
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
				deleteFromBPlusTree(&obj,priVal);
				break;
			case 4: printBPlusTree(obj->dataRoot);
				break;
			case 5: printf("Good bye..\n\n");
				return;
			default:printf("\nEnter a proper value!!\n");
		}
	}
}
