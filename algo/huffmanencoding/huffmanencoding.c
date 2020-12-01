#include"huffmanencoding.h"

int main()
{
	int choice;
	char priVal[200],*secVal = calloc(sizeof(char),200);
	char **encoder = calloc(sizeof(char*),26);
	for(choice = 0; choice < 26; ++choice)
	{
		*(encoder + choice) = calloc(sizeof(char),200);
	}
	
	struct huffmanTrieNode* trieRoot = createHuffmanTrie();
	getEncoder(trieRoot,encoder,secVal,0);

	free(secVal);
	do
	{
		printf("\n1.Encode a string\n2.Decode a binary sequence\n3.Write the trie to a file\n4.Read from the file and print\n5.Print the trie\n6.Exit:");
		scanf(" %d",&choice);
		switch(choice)
		{
			case 1: printf("\nEnter the string: ");
					scanf(" %s",priVal);
					secVal = encodeString(encoder,priVal);
					printf("%s\n",secVal);
					free(secVal);
					break;
			case 2: printf("\nEnter the binary sequence: ");
					scanf(" %s",priVal);
					secVal = decodeString(trieRoot,priVal);
					printf("%s\n",secVal);
					free(secVal);
					break;
			case 3: printf("\nEnter the file name: ");
					scanf(" %s",priVal);
					writeTrieToFile(trieRoot,priVal);
					break;
			case 4: printf("\nEnter the file name: ");
					scanf(" %s",priVal);
					readTrieFromFile(priVal);
					break;
			case 5: printHuffmanTrie(trieRoot);
					break;
			case 6: printf("\n\nThank you!\n\n");
					break;
			default:printf("\nEnter a proper value...\n");
					break;
		}
	}while(choice != 6);
	return 0;
}