#include<stdio.h>
#include<conio.h>

#define DEFAULT_ARRAY_SIZE 16

struct arrayList
{
	int* val;
	int length;
};

struct arrayList* createArrayList()
{
	struct arrayList *list = (struct arrayList*)malloc(sizeof(struct arrayList));
        (*list)->length = 0;
        (*list)->val = (int*)malloc(sizeof(int)*DEFAULT_ARRAY_SIZE));
}

void addElementArrayList(struct arrayList **list,int newVal)
{
	if(list == NULL)
	{
		*list = createArrayList();
	}
	(*list)->(val + (*list)->length++ ) = newVal;
}
