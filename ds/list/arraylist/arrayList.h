#include<stdio.h>

#define bool int
#define true 1
#define false 0


#define DEFAULT_ARRAY_SIZE 16

struct arrayList
{
	int* val;
	int length;
	int size;
};

struct arrayList* createArrayList()
{
	struct arrayList *list = (struct arrayList*)malloc(sizeof(struct arrayList));
        list->length = 0;
        list->val = (int*)malloc(sizeof(int)*DEFAULT_ARRAY_SIZE);
	list->size = DEFAULT_ARRAY_SIZE;
}

void reAllocateMemory(struct arrayList **list)
{
	int *oldVal = (*list)->val,i;
	(*list)->val = (int*)malloc(sizeof(int)*((*list)->size));
	for(i=0;i<(*list)->length;i++)
	{
		*((*list)->val + i ) = *(oldVal + i);
	}
}

void addElementArrayList(struct arrayList **list,int newVal)
{
	if(*list == NULL)
	{
		*list = createArrayList();
	}
	else if( (*list)->length == (*list)->size )
	{
		(*list)->size = ((*list)->size * 3) /2;
		reAllocateMemory(list);
	}
	*((*list)->val + (*list)->length++) = newVal;
}

void removeElementArrayList(struct arrayList **list,int val,bool isIndex)
{
	int i;
	if(!isIndex)
	{
		for(i=0;(i<(*list)->length) && (val != *( (*list)->val + i));i++);
		val = i;
	}
	if(val < ((*list)->length - 1) )
	{
		for(i=val;i<(*list)->length;i++)
		{
			*((*list)->val + i) = *((*list)->val + i + 1);
		}
	}
	if(val < (*list)->length)
	{
		int newSize = ((*list)->size * 2)/3;
		(*list)->length--;
		if(newSize > (*list)->length && newSize != DEFAULT_ARRAY_SIZE)
		{
			(*list)->size = newSize;
			reAllocateMemory(list);
		}
	}
}

void printAll(struct arrayList *list)
{
	int i;
	for(i=0;i<list->length;i++)
	{
		printf(":%d",*(list->val+i) );
	}
}
