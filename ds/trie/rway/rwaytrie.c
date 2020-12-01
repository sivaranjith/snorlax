#include "rwaytrie.h"

int main()
{
	int choice,value;
	char key[21];
	struct trieNode *trieObj = createTrie();
	do
	{
		printf("\n1.Enter a key and value\n2.Search for a key\n3.Delete a key\n4.Print Trie\n5.Exit: ");
		scanf(" %d",&choice);
		switch(choice)
		{
			case 1: printf("\nEnter the key and value: ");
					scanf(" %s %d",key,&value);
					insertRWayTrie(trieObj,key,value);
					break;
			case 2: printf("\nEnter the Search key: ");
					scanf(" %s",key);
					value = searchRWayTrie(trieObj,key);
					if(value == 0)
					{
						printf("\nNot available\n");
					}
					else
					{
						printf("\nValue is: %d\n",value);
					}
					break;
			case 3: printf("\nEnter the deletion key: ");
					scanf(" %s",key);
					if(deletingRWayTrie(trieObj,key))
					{
						printf("Successfully deleted\n");
					}
					else
					{
						printf("Couldn't find value\n");
					}
					break;
			case 4: printRWayTrie(trieObj);
					break;
			case 5: printf("\n\nGood bye!\n\n");
					return 0;
			default:printf("\nEnter a proper value...\n");
					break;
		}
	}while(true);
}