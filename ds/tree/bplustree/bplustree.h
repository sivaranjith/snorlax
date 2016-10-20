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
	temp->dataRoot->size = 0;
	temp->dataRoot->parent = NULL;
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
			return dataRoot;
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

	if(*(dataRoot->child + dataRoot->size - 1) < secVal)
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

struct bPlusTreeDataNode* bTreeInserterroot(struct bPlusTreeDataNode *dataRoot,int nodeSize,int priVal)
{
	int index = binarySearchNode(dataRoot,priVal);
	if(index >= 0)
	{
		return NULL;
	}
	else
	{
		if(*(dataRoot->child + index) != NULL)
		{
			struct bPlusTreeDataNode *temp = bTreeInserterroot(*(dataRoot->child + index),nodeSize,priVal);
			if(temp != NULL)
			{
				//check for space and insert value
			}
			return temp;
		}
		else if(nodeSize == dataRoot->size)
		{
			struct bPlusTreeDataNode *rightChild = (struct bPlusTreeDataNode*)malloc(sizeof(struct bPlusTreeDataNode)), *parent = (struct bPlusTreeDataNode*)malloc(sizeof(struct bPlusTreeDataNode));


			int srcIt = nodeSize,childIt = 0, mid = (nodeSize + 1)/2;
			for(childIt = nodeSize - mid; childIt >= 0; --childIt)
			{
				if(index != srcIt)
				{
					*(rightChild->val + childIt) = *(dataRoot->val + srcIt);
					--srcIt;
				}
				else
				{
					*(rightChild->val + childIt) = priVal;
				}
			}

			for(childIt = mid; childIt >= 0 && srcIt >= index; --childIt)
			{
				if(index == srcIt)
				{
					*(dataRoot->val + childIt) = secVal;
				}
				else
				{
					*(dataRoot->val + childIt) = *(dataRoot->val + srcIt);
					--srcIt;
				}
			}

			*(parent->val) = *(rightChild->val);
			*(parent->child) = dataRoot;
			*(parent->child + 1) = rightChild;
			dataRoot->parent = rightChild->parent = parent;
			rightChild->leafNext = dataRoot->leafNext;
			dataRoot->leafNext = rightChild;
			return parent;
		}
		else
		{
			int i;
			for(i = dataRoot->size; i > index; --i)
			{
				*(dataRoot->val + i) = *(dataRoot->val + i - 1);
			}
			*(dataRoot + index) = priVal;
			return NULL;
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
