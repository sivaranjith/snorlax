#include<stdio.h>
#define boolean int
#define false 0
#define true 1

struct bPlusTreeNode
{
	struct bPlusTreeDataNode 
	{
		int* val;
		int size;
		struct bPlusTreeDataNode *parent,*leafNext,**child;
	}*dataRoot,*leafHead;
	int nodeSize;
};

//bTreeNodeSize repersents the no of values inside a b-plus node
struct bPlusTreeNode* createBPlusTreeNode(int bTreeNodeSize)
{
	int i=0;
	struct bPlusTreeNode *temp = (struct bPlusTreeNode*)malloc(sizeof(struct bPlusTreeNode));
	temp->nodeSize = bTreeNodeSize;
	temp->leafHead = temp->dataRoot = (struct bPlusTreeDataNode*)malloc(sizeof(struct bPlusTreeDataNode));
	temp->dataRoot->val = (int*)malloc(sizeof(int)*bTreeNodeSize);
	temp->dataRoot->child = (struct bPlusTreeDataNode**)malloc(sizeof(struct bPlusTreeDataNode*)*(bTreeNodeSize+1));
	for(;i<=bTreeNodeSize;++i)
	{
		*(temp->dataRoot->child + i) = NULL;
	}
	/*for(i=0;i<=bTreeNodeSize;++i)
	  {
	  printf("%p\n", *(temp->root->child + i) );
	  }*/
	return temp;
}

int binarySearchNode(struct bPlusTreeDataNode *dataRoot,int secVal)
{
	int start,end,mid,val;

	for(start=0, end=dataRoot->size; start != end; )
	{
		mid = (start + end)/2;
		val = *(dataRoot->val + mid);

		if(val == secVal)
		{
			return mid;
		}
		else if(start + 1 == end)
		{
			break;
		}
		else if(val < secVal)
		{
			start = mid;
		}
		else
		{
			end = mid;
		}
	}

	if(*(dataRoot->val + dataRoot->size - 1) < secVal)
	{
		start = dataRoot->size;
	}
	
	//for zero one is added negative no repersents the value should be inserted at this point or further root should be traveled in this child
	return -(start + 1);
}

struct bPlusTreeDataNode* searchData(struct bPlusTreeDataNode *dataRoot,int secVal)
{
	int index;
	if(dataRoot == NULL)
	{
		return NULL;
	}

	index = binarySearchNode(dataRoot,secVal);

	if(index >= 0)
	{
		return dataRoot;
	}

	index = -(index + 1);

	return searchData(*(dataRoot->child + index),secVal);
}

struct bPlusTreeDataNode* searchInBPlusTreeTree(struct bPlusTreeNode *root,int secVal)
{
	return searchData(root->dataRoot,secVal);
}

struct bPlusTreeDataNode* splitNode(struct bPlusTreeDataNode *dataRoot,struct bPlusTreeDataNode *temp,int nodeSize,int index)
{
	struct bPlusTreeDataNode *rightChild = (struct bPlusTreeDataNode*)malloc(sizeof(struct bPlusTreeDataNode)), *parent = (struct bPlusTreeDataNode*)malloc(sizeof(struct bPlusTreeDataNode));
	int srcIt = nodeSize,childIt = 0, mid = (nodeSize + 1)/2,diff;
	boolean isVisited = false, isLeafNode = true;

	rightChild->val = (int*)malloc(sizeof(int)*nodeSize);
	rightChild->child = (struct bPlusTreeDataNode**)malloc(sizeof(struct bPlusTreeDataNode*)*(nodeSize+1));
	parent->val = (int*)malloc(sizeof(int)*nodeSize);
	parent->child = (struct bPlusTreeDataNode**)malloc(sizeof(struct bPlusTreeDataNode*)*(nodeSize+1));
	diff = nodeSize - mid;

	if(*(dataRoot->child) == NULL)
	{
		childIt = diff;
	}
	else
	{
		isLeafNode = false;
		childIt = diff - 1;
	}

	for(; childIt >= 0; --childIt)
	{
		if(index != srcIt || isVisited)
		{
			*(rightChild->val + childIt) = *(dataRoot->val + srcIt - 1);
			if(index != srcIt + 1)
			{
				*(rightChild->child + childIt + 1) = *(dataRoot->child + srcIt);
				if(*(rightChild->child + childIt + 1) != NULL)
				{
					(*(rightChild->child + childIt + 1))->parent = rightChild;
				}
			}
			--srcIt;
		}
		else
		{
			isVisited = true;
			*(rightChild->val + childIt) = *(temp->val);
			*(rightChild->child + childIt) = *(temp->child);
			*(rightChild->child + childIt + 1) = *(temp->child + 1);
			if(*(rightChild->child + childIt) != NULL)
			{
				(*(rightChild->child + childIt))->parent = rightChild;
			}
			if(*(rightChild->child + childIt + 1) != NULL)
			{
				(*(rightChild->child + childIt + 1))->parent = rightChild;
			}
		}
	}

	if(isLeafNode)
	{
		rightChild->size = diff + 1;
		*(parent->val) = *(rightChild->val);
	}
	else
	{
		rightChild->size = diff;
		*(parent->val) = *(dataRoot->val + diff);
		if(index == diff)
		{
			*(rightChild->child) = *(dataRoot->child + diff + 1);
		}
		else
		{
			*(rightChild->child) = *(dataRoot->child + mid + 1);
		}
		(*(rightChild->child))->parent = rightChild;
		--srcIt;
	}

	isVisited = false;

	for(childIt = mid - 1; childIt >= 0; --childIt)
	{
		if(index != srcIt || isVisited)
		{
			*(dataRoot->val + childIt) = *(dataRoot->val + srcIt - 1);
			if(index != srcIt + 1)
			{
				*(dataRoot->child + childIt + 1) = *(dataRoot->child + srcIt);
				if(*(dataRoot->child + childIt + 1) != NULL)
				{
					(*(dataRoot->child + childIt + 1))->parent = dataRoot;
				}
			}
			--srcIt;
		}
		else
		{
			isVisited = true;
			*(dataRoot->val + childIt) = *(temp->val);
			*(dataRoot->child + childIt) = *(temp->child);
			*(dataRoot->child + childIt + 1) = *(temp->child + 1);

			if(*(dataRoot->child + childIt) != NULL)
			{	
				(*(dataRoot->child + childIt))->parent = dataRoot;
			}
			if(*(dataRoot->child + childIt + 1) != NULL)
			{
				(*(dataRoot->child + childIt + 1))->parent = dataRoot;
			}
		}
	}

	dataRoot->size = mid;

	*(parent->child) = dataRoot;
	*(parent->child + 1) = rightChild;
	parent->size = 1;
	dataRoot->parent = rightChild->parent = parent;
	rightChild->leafNext = dataRoot->leafNext;
	dataRoot->leafNext = rightChild;

	free(temp);

	return parent;
}

struct bPlusTreeDataNode* insertIntoTheNode(struct bPlusTreeDataNode *dataRoot,struct bPlusTreeDataNode *temp,int index)
{
	int i;
	for(i = dataRoot->size; i > index; --i)
	{
		*(dataRoot->val + i) = *(dataRoot->val + i - 1);
	}
	*(dataRoot->val + index) = *(temp->val);

	*(dataRoot->child + index) = *(temp->child);
	*(dataRoot->child + index + 1) = *(temp->child + 1);

	++(dataRoot->size);

	free(temp);

	return NULL;
}

struct bPlusTreeDataNode* bTreeInserterroot(struct bPlusTreeDataNode *dataRoot,int nodeSize,int priVal)
{
	int index = binarySearchNode(dataRoot,priVal);
	if(index >= 0)
	{
		return NULL;
	}
	else
	{
		struct bPlusTreeDataNode *temp;
		index = -(index + 1);
		if(*(dataRoot->child + index) != NULL)
		{
			temp = bTreeInserterroot(*(dataRoot->child + index),nodeSize,priVal);
		}
		else
		{
			temp = (struct bPlusTreeDataNode*)malloc(sizeof(struct bPlusTreeDataNode));
			temp->val = (int*)malloc(sizeof(int));
			temp->child = (struct bPlusTreeDataNode**)malloc(sizeof(struct bPlusTreeDataNode*)*2);

			*(temp->val) = priVal;
			temp->size = 1;
		}
		if(temp == NULL)
		{
			return NULL;
		}
		if(nodeSize == dataRoot->size)
		{
			return splitNode(dataRoot,temp,nodeSize,index);
		}
		else
		{
			return insertIntoTheNode(dataRoot,temp,index);
		}
	}
}

struct bPlusTreeDataNode* insertToBPlusTreeTree(struct bPlusTreeNode *root,int priVal)
{
	struct bPlusTreeDataNode *tempDNode = bTreeInserterroot(root->dataRoot,root->nodeSize,priVal);
	if(tempDNode != NULL)
	{
		root->dataRoot = tempDNode;
	}
	return tempDNode;
}

void printBPlusTreeTree(struct bPlusTreeDataNode *dataRoot)
{
	int i;
	if(dataRoot == NULL)
	{
		return;
	}
	printf("\nme: %p , parent: %p , val: ",dataRoot,dataRoot->parent);
	for(i = 0; i < dataRoot->size; ++i)
	{
		printf("%d ", *(dataRoot->val +i) );
	}
	printf(", children: ");
	for(i = 0; i <= dataRoot->size; ++i)
	{
		printf("%p ", *(dataRoot->child + i) );
	}

	for(i = 0; i <= dataRoot->size; ++i)
	{
		printBPlusTreeTree( *(dataRoot->child + i) );
	}
}

struct bPlusTreeNode* deleteFromBPlusTreeTree(struct bPlusTreeNode **root,int priVal)
{
	return NULL;
}
