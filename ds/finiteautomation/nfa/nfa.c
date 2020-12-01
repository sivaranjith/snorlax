#include "nfa.h"

int main()
{
	int choice,length;
	char source[66],searchString[66];
	printf("\nEnter the regex: ");
	scanf(" %s",source);

	for(; source[length] != '\0'; ++length);

	struct nfaNode* nfaNodeObj = getNFAObj(source,length);
	do
	{
		printf("\n1.Search in a string\n2.Exit:");
		scanf(" %d",&choice);
		switch(choice)
		{
			case 1: printf("\nEnter the string to search in: ");
					scanf(" %s",searchString);
					if(searchUsingNFA(nfaNodeObj,searchString,length))
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