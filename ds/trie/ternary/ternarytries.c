#include "ternarytries.h"

int main()
{
	int choice;
	struct ternaryTrieNode *ternaryTrieObj = createTernaryTrie();
	do
	{
		printf("\n1.Enter a key and value\n2.Search for a key\n3.Delete a key\n4.Print Trie\n5.Exit: ");
		scanf(" %d",&choice);
		switch(choice)
		{
			case 1: printf("\nEnter the key and value: ");
					scanf(" %s %d",key,&value);
					insertTernaryTrie(trieObj,key,value);
					break;
			case 2: printf("\nEnter the Search key: ");
					scanf(" %s",key);
					value = searchTernaryTrie(trieObj,key);
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
					if(deletingTernaryTrie(trieObj,key))
					{
						printf("Successfully deleted\n");
					}
					else
					{
						printf("Couldn't find value\n");
					}
					break;
			case 4: printTernaryTrie(trieObj);
					break;
			case 5: printf("\n\nGood bye!\n\n");
					return 0;
			default:printf("\nEnter a proper value...\n");
					break;
		}
	}
}