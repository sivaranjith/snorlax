#include<stdio.h>
#define INIT_SIZE 16

struct hashMap
{
	struct node
	{
		int key,value;
		struct node *next,*link;
	}*linkedRoot;
	struct node **map;
	int size;
};

struct hashMap* createHashMap()
{
	struct hashMap *obj = (struct hashMap*)malloc(sizeof(struct hashMap));
	obj->map = (struct hashMap**)malloc(sizeof(struct hashMap*)*INIT_SIZE);
	obj->size = INIT_SIZE;
}

void putValue(struct hashMap *obj,int key,int val)
{
	struct node *temp = (struct node*)malloc(sizeof(struct node));
	int hash = hashing(key);
	temp->key = key;
	temp->value = val;
	temp->next = *(obj->map + hash);
	*(obj->map + hash) = temp;
	temp->link = obj->linkedRoot;
	obj->linkedRoot = temp;
}

int* getValue(struct hashMap *obj,int key)
{
	struct node *temp = *(obj->map + hashing(key));
	while(temp != NULL)
	{
		if(temp->key == key)
		{
			int val = temp->value;
			return &val;
		}
	}
	return NULL;
}

int* removeValue(struct hashMap *obj,int key)
{
	int val;
	struct node **temp = (obj->map + hashing(key)),*freePt;
	while(*temp != NULL && (*temp)->key != key)
	{
		temp = &(*temp)->next;
	}

	if(*temp == NULL)
	{
		return NULL;
	}

	freePt = *temp;
	*temp = (*temp)->next;

	temp = &(obj->linkedRoot);
	while((*temp)->key != key)
	{
		temp = &(*temp)->link;
	}

	*temp = (*temp)->link;
	val = freePt->value;
	free(freePt);
	return &val;
}

int hashing(int key)
{
	return key >= 0 ? key%INIT_SIZE : (-key)%INIT_SIZE;
}

void printHashMap(struct hashMap *obj)
{
	int i;
	for(i = 0; i < obj->size ; ++i)
	{
		struct node *temp = *(obj->map + i);
		while(temp != NULL)
		{
			printf("Key:%d Value:%d\n",temp->key,temp->value);
			temp = temp->next;
		}
	}
}

void printLinkedHashMap(struct node *linkedRoot)
{
	if(linkedRoot != NULL)
	{
		printLinkedHashMap(linkedRoot->link);
		printf("Key:%d Value:%d\n",linkedRoot->key,linkedRoot->value );
	}
}