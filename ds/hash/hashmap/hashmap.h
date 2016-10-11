#include<stdio.h>
#define INIT_SIZE 4
#define INC_LIMIT 2
#define DEC_LIMIT 1


struct hashMap
{
	struct node
	{
		int key,value;
		struct node *next,*linkNext,*linkPrev;
	}*linkedRoot;
	struct node **map;
	int size,count;
};

struct hashMap* createHashMap()
{
	struct hashMap *obj = (struct hashMap*)malloc(sizeof(struct hashMap));
	obj->map = (struct node**)malloc(sizeof(struct node*)*INIT_SIZE);
	obj->size = INIT_SIZE;
}

void reHash(struct hashMap *obj,int newSize)
{
	int i,oldSize = obj->size;
	struct node **tempMap = (struct node**)malloc(sizeof(struct node*)*newSize);

	obj->size = newSize;
	for(i = 0; i < oldSize ; ++i)
	{
		struct node *temp = *(obj->map + i);
		while(temp != NULL)
		{
			struct node *swap = temp->next;
			int hash = hashing(obj,temp->key);
			temp->next = *(tempMap + hash);
			*(tempMap + hash) = temp;
			temp = swap;
		}
	}

	obj->map = tempMap;
}

void putValue(struct hashMap *obj,int key,int val)
{
	struct node *temp = (struct node*)malloc(sizeof(struct node)),**itr;
	int hash = hashing(obj,key);
	temp->key = key;
	temp->value = val;
	temp->next = NULL;
	itr = (obj->map + hash);
	while(*itr != NULL)
	{
		if((*itr)->key == key)
		{
			(*itr)->value = val;
			return;
		}
		else if((*itr)->next == NULL)
		{
			break;
		}
		itr = &(*itr)->next;
	}
	
	if(*itr == NULL)
	{
		*itr = temp;
	}
	else
	{
		(*itr)->next = temp;
	}

	temp->linkNext = obj->linkedRoot;
	temp->linkPrev = NULL;
	if(obj->linkedRoot != NULL)
	{
		obj->linkedRoot->linkPrev = temp;
	}
	obj->linkedRoot = temp;
	++(obj->count);
	if(obj->count >= obj->size*INC_LIMIT)
	{
		reHash(obj,obj->size*3);
	}
}

int* getValue(struct hashMap *obj,int key)
{
	struct node *temp = *(obj->map + hashing(obj,key));
	while(temp != NULL)
	{
		if(temp->key == key)
		{
			int val = temp->value;
			return &val;
		}
		temp = temp->next;
	}
	return NULL;
}

int* removeValue(struct hashMap *obj,int key)
{
	int val;
	struct node **temp = (obj->map + hashing(obj,key)),*freePt;
	while(*temp != NULL && (*temp)->key != key)
	{
		temp = &(*temp)->next;
	}

	if(*temp == NULL)
	{
		return NULL;
	}

	freePt = *temp;

	if((*temp)->linkPrev == NULL)
	{
		obj->linkedRoot = (*temp)->linkNext;
	}
	else
	{
		(*temp)->linkPrev->linkNext = (*temp)->linkNext;
	}

	if((*temp)->linkNext != NULL)
	{
		(*temp)->linkNext->linkPrev = (*temp)->linkPrev;
	}

	*temp = (*temp)->next;
	val = freePt->value;
	free(freePt);
	--(obj->count);
	if(obj->count <= obj->size*DEC_LIMIT)
	{
		reHash(obj,obj->size/2 > INIT_SIZE ? obj->size/2 : INIT_SIZE);
	}
	return &val;
}

int hashing(struct hashMap* obj,int key)
{
	return key >= 0 ? key%obj->size : (-key)%obj->size;
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
		printLinkedHashMap(linkedRoot->linkNext);
		printf("Key:%d Value:%d\n",linkedRoot->key,linkedRoot->value );
	}
}