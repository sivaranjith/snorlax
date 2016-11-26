#include "dfa.h"

int main()
{
	int choice,length;
	char source[66],searchString[66];
	printf("\nEnter the sub string: ");
	scanf(" %s",source);

	for(; source[length] != '\0'; ++length);

	int** dfaObj = getDFAObj(source,length);
	do
	{
		printf("\n1.Search in a string\n2.Exit:");
		scanf(" %d",&choice);
		switch(choice)
		{
			case 1: printf("\nEnter the string to search in: ");
					scanf(" %s",searchString);
					if(searchUsingDFA(dfaObj,searchString,length))
					{
						printf("\nFOUND\n");
					}
					else
					{
						printf("\nNOT FOUND\n");
					}
					break;
			case 2: printf("\n\nGood bye!\n\n");
					break;
			case 3: printf("\nEnter proper value...\n");
					break;
		}
	}while(choice != 2);
}