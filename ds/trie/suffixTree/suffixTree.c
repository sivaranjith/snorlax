#include"suffixTree.h"

int main()
{
	int choice;
	char *ipStr = calloc(sizeof(char),21);
	printf("\nEnter the primary string: ");
	scanf(" %s",ipStr);
	struct suffixTree* suffixTreeObj = createSuffixTree(ipStr);
	do
	{
		printf("\n1.Enter the string to check\n2.Print the suffixTree\n3.Exit: ");
		scanf(" %d",&choice);
		switch(choice)
		{
			case 1: printf("\nEnter the string: ");
					scanf(" %s",ipStr);
					if(checkForSubString(suffixTreeObj,ipStr))
					{
						printf("FOUND\n");
					}
					else
					{
						printf("NOT-FOUND\n");
					}
					break;
			case 2: printSuffixTree(suffixTreeObj);
					break;
			case 3: printf("\n\nGood bye!\n\n");
					break;
			default:printf("\nEnter a proper value...\n");
					break;
		}

	}while(choice != 3);
	return 0;
}