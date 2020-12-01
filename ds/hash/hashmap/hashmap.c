#include"hashmap.h"

int main()
{
	int priVal,choice,secVal,*val;
	struct hashMap *obj = createHashMap();
	do
	{
		printf("\n1.Put value\n2.Get value\n3.Remove\n4.Print All\n5.Print LinkedHashMap\n6.Exit:");
		scanf(" %d",&choice);
		switch(choice)
		{
			case 1: printf("Enter the key and value: ");
					scanf(" %d %d",&priVal,&secVal);
					putValue(obj,priVal,secVal);
					break;
			case 2: printf("Enter the key: ");
					scanf(" %d",&priVal);
					val = getValue(obj,priVal);
					if(val == NULL)
					{
						printf("Value: NULL\n");
					}
					else
					{
						printf("Value: %d\n",*val);
					}
					break;
			case 3: printf("Enter the key: ");
					scanf(" %d",&priVal);
					removeValue(obj,priVal);
					break;
			case 4: printHashMap(obj);
					break;
			case 5: printLinkedHashMap(obj->linkedRoot);
					break;
			case 6: printf("\n\nGood bye\n\n");
					break;
			default:printf("\nEnter a proper value...\n\n");
					break;
		}
	}while(choice != 6);
}
