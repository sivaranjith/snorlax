#include<stdio.h>
#define boolean int
#define false 0
#define true 1
#define isInsertable(actualNodeSize,currentSize) ( ((3*actualNodeSize)/4) > currentSize )
#define isDeleteable(actualNodeSize,currentSize) ( actualNodeSize/2 <= currentSize )
struct bStarTreeNode
{
	struct bStarTreeDataNode 
	{
		int* val;
		int size;
		struct bStarTreeDataNode *parent,*leafNext,**child;
	}*dataRoot,*leafHead;
	int nodeSize;
};

boolean moveToSibiling(struct bStarTreeDataNode *dataRoot,struct bStarTreeDataNode *actualNode,int nodeSize,int index,int type);

//bTreeNodeSize repersents the no of values inside a b-star node
struct bStarTreeNode* createBStarTreeNode(int bTreeNodeSize)
{
	int i=0;
	struct bStarTreeNode *temp = (struct bStarTreeNode*)malloc(sizeof(struct bStarTreeNode));
	temp->nodeSize = bTreeNodeSize;
	temp->leafHead = temp->dataRoot = (struct bStarTreeDataNode*)malloc(sizeof(struct bStarTreeDataNode));
	temp->dataRoot->val = (int*)malloc(sizeof(int)*bTreeNodeSize);
	temp->dataRoot->child = (struct bStarTreeDataNode**)malloc(sizeof(struct bStarTreeDataNode*)*(bTreeNodeSize+1));
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

int binarySearchNode(struct bStarTreeDataNode *dataRoot,int secVal,boolean findChild)
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

	if(findChild)
	{
		return -1;
	}
	else if(*(dataRoot->val + dataRoot->size - 1) < secVal)
	{
		start = dataRoot->size;
	}
	
	//for zero one is added negative no repersents the value should be inserted at this point or further root should be traveled in this child
	return -(start + 1);
}

struct bStarTreeDataNode* searchData(struct bStarTreeDataNode *dataRoot,int secVal)
{
	int index;
	if(dataRoot == NULL)
	{
		return NULL;
	}

	index = binarySearchNode(dataRoot,secVal,false);

	if(index >= 0)
	{
		return dataRoot;
	}

	index = -(index + 1);

	return searchData(*(dataRoot->child + index),secVal);
}

struct bStarTreeDataNode* searchInBStarTree(struct bStarTreeNode *root,int secVal)
{
	return searchData(root->dataRoot,secVal);
}

struct bStarTreeDataNode* splitNode(struct bStarTreeDataNode *dataRoot,struct bStarTreeDataNode *temp,int nodeSize,int index)
{
	struct bStarTreeDataNode *rightChild = (struct bStarTreeDataNode*)malloc(sizeof(struct bStarTreeDataNode)), *parent = (struct bStarTreeDataNode*)malloc(sizeof(struct bStarTreeDataNode));
	int srcIt = nodeSize,childIt = 0, mid = (nodeSize + 1)/2,diff;
	boolean isVisited = false, isLeafNode = true;

	rightChild->val = (int*)malloc(sizeof(int)*nodeSize);
	rightChild->child = (struct bStarTreeDataNode**)malloc(sizeof(struct bStarTreeDataNode*)*(nodeSize+1));
	parent->val = (int*)malloc(sizeof(int)*nodeSize);
	parent->child = (struct bStarTreeDataNode**)malloc(sizeof(struct bStarTreeDataNode*)*(nodeSize+1));
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

struct bStarTreeDataNode* insertIntoTheNode(struct bStarTreeDataNode *dataRoot,struct bStarTreeDataNode *temp,int index)
{
	int i;
	for(i = dataRoot->size; i > index; --i)
	{
		*(dataRoot->val + i) = *(dataRoot->val + i - 1);
	}
	*(dataRoot->val + index) = *(temp->val);

	*(dataRoot->child + index) = *(temp->child);
	*(dataRoot->child + index + 1) = *(temp->child + 1);

	if(*(temp->child) != NULL && (*(temp->child))->parent != NULL)
	{
		(*(temp->child))->parent = dataRoot;
		(*(temp->child + 1))->parent = dataRoot;
	}

	++(dataRoot->size);

	free(temp);

	return NULL;
}

boolean rotateLeft(struct bStarTreeDataNode *dataRoot,struct bStarTreeDataNode *actualNode,int nodeSize,int index,int type)
{
	int i = 0,j;
	boolean canInsert;
	struct bStarTreeDataNode *parent = dataRoot->parent;
	struct bStarTreeDataNode *sibiling = *(parent->child + index + 1);

	do
	{
		*(dataRoot->val + dataRoot->size) = *(parent->val + index);
		++(dataRoot->size);
		*(parent->val + index) = *(sibiling->val + i + 1);
		++i;
		
	} while (!isInsertable(nodeSize,sibiling->size - i) && isInsertable(nodeSize,dataRoot->size));	

	for(j=0;j<sibiling->size - i;j++)
	{
		*(sibiling->val + j) = *(sibiling->val + j + i);
	}
	sibiling->size -= i;

	if(sibiling == actualNode)
	{
		canInsert = sibiling->size < nodeSize;
	}
	else
	{
		canInsert = isInsertable(nodeSize,sibiling->size);
	}

	if(!canInsert && ((type == 1 && index != dataRoot->parent->size) || (type == -1 && index != 0)))
	{
		if(moveToSibiling(*(parent->child + index + type),actualNode,nodeSize,index+type,type))
		{
			return rotateLeft(dataRoot,actualNode,nodeSize,index,type);
		}
		else
		{
			return false;
		}
	}

	return true;
}

boolean rotateRight(struct bStarTreeDataNode *dataRoot,struct bStarTreeDataNode *actualNode,int nodeSize,int index,int type)
{
	int i,tempSize = 0;
	boolean canInsert;
	struct bStarTreeDataNode *parent = dataRoot->parent;
	struct bStarTreeDataNode *sibiling = *(parent->child + index - 1);
	int* tempHolders = (int*)malloc(sizeof(int)*nodeSize);

	do
	{
		*(tempHolders + tempSize) = *(parent->val + index - 1);
		++tempSize;
		*(parent->val + index - 1) = *(sibiling->val + sibiling->size - tempSize);		
	} while(!isInsertable(nodeSize,sibiling->size - i) && isInsertable(nodeSize,dataRoot->size));	

	for(i = 0; i < tempSize; ++i)
	{
		*(sibiling->val + i + sibiling->size) = *(sibiling->val + i);
		*(sibiling->val + i) = *(tempHolders + i);
	}

	sibiling->size -= i;
	dataRoot->size += i;

	if(sibiling == actualNode)
	{
		canInsert = sibiling->size < nodeSize;
	}
	else
	{
		canInsert = isInsertable(nodeSize,sibiling->size);
	}

	if(!canInsert && ((type == 1 && index != dataRoot->parent->size) || (type == -1 && index != 0)))
	{
		if(moveToSibiling(*(parent->child + index + type),actualNode,nodeSize,index+type,type))
		{
			return rotateRight(dataRoot,actualNode,nodeSize,index,type);
		}
		else
		{
			return false;
		}
	}

	return true;
}

boolean moveToSibiling(struct bStarTreeDataNode *dataRoot,struct bStarTreeDataNode *actualNode,int nodeSize,int index,int type)
{
	struct bStarTreeDataNode *parent = dataRoot->parent;
	boolean callRecursively = true;
	boolean (*rotateDirection)(struct bStarTreeDataNode*,struct bStarTreeDataNode*,int,int,int);

	if(type == 0)
	{
		if(index != 0)
		{
			if(moveToSibiling(*(parent->child + index - 1),actualNode,nodeSize,index-1,-1))
			{
				return true;
			} 
			else if(index != dataRoot->parent->size)
			{
				return moveToSibiling(*(parent->child + index + 1),actualNode,nodeSize,index+1,1);
			}
			return false;
		}
		else
		{
			return moveToSibiling(*(parent->child + index + 1),actualNode,nodeSize,index+1,1);
		}
	}
	else if(type == 1)
	{
		if(index == dataRoot->parent->size)
		{
			callRecursively = false;
		}
		rotateDirection = &rotateRight;
	}
	else
	{
		if(index == 0)
		{
			callRecursively = false;
		}
		rotateDirection = &rotateLeft;
	}
	
	if(isInsertable(nodeSize,dataRoot->size))
	{
		return rotateDirection(dataRoot,actualNode,nodeSize,index,type);
	}
	else if(callRecursively && moveToSibiling(*(parent->child + index + type),actualNode,nodeSize,index+type,type) && isInsertable(nodeSize,dataRoot->size))
	{
		return rotateDirection(dataRoot,actualNode,nodeSize,index,type);
	}
	return false;
}
struct bStarTreeDataNode* bTreeInserterroot(struct bStarTreeDataNode *dataRoot,int nodeSize,int priVal)
{
	int index = binarySearchNode(dataRoot,priVal,false);
	if(index >= 0)
	{
		return NULL;
	}
	else
	{
		struct bStarTreeDataNode *temp;
		index = -(index + 1);
		if(*(dataRoot->child + index) != NULL)
		{
			temp = bTreeInserterroot(*(dataRoot->child + index),nodeSize,priVal);
		}
		else
		{
			temp = (struct bStarTreeDataNode*)malloc(sizeof(struct bStarTreeDataNode));
			temp->val = (int*)malloc(sizeof(int));
			temp->child = (struct bStarTreeDataNode**)malloc(sizeof(struct bStarTreeDataNode*)*2);

			*(temp->val) = priVal;
			temp->size = 1;
		}
		if(temp == NULL)
		{
			return NULL;
		}
		if(nodeSize == dataRoot->size)
		{
			if( *(dataRoot->child) == NULL && dataRoot->parent != NULL)
			{
				int myIndex = binarySearchNode(dataRoot->parent,*(dataRoot->val),true);
				++myIndex;
				if(moveToSibiling(dataRoot,dataRoot,nodeSize,myIndex,0))
				{
					*(dataRoot->val + dataRoot->size) = priVal;
					free(temp);
					++(dataRoot->size);
					return NULL;
				}
			}
			return splitNode(dataRoot,temp,nodeSize,index);
		}
		else
		{
			return insertIntoTheNode(dataRoot,temp,index);
		}
	}
}

struct bStarTreeDataNode* insertToBStarTree(struct bStarTreeNode *root,int priVal)
{
	struct bStarTreeDataNode *tempDNode = bTreeInserterroot(root->dataRoot,root->nodeSize,priVal);
	if(tempDNode != NULL)
	{
		root->dataRoot = tempDNode;
	}
	return tempDNode;
}

void printBStarTree(struct bStarTreeDataNode *dataRoot)
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
		printBStarTree( *(dataRoot->child + i) );
	}
}

struct bStarTreeDataNode* deleteFromBStarTree0(struct bStarTreeDataNode *dataRoot,int nodeSize,int priVal)
{
	int index = binarySearchNode(dataRoot,priVal,false);
	if(*(dataRoot->child) == NULL && index < 0)
	{
		return NULL;
	}
	else
	{
		struct bStarTreeDataNode *temp;
		if(*(dataRoot->child + index) != NULL)
		{
			index = -(index + 1);
			temp = bTreeInserterroot(*(dataRoot->child + index),nodeSize,priVal);
			if(temp == NULL)
			{
				return NULL;
			}
		}
		if(isDeleteable(nodeSize,dataRoot->size))
		{
			int i;
			for(i = index;i < nodeSize - 1; ++i)
			{
				*(dataRoot->val + i) = *(dataRoot->val + i + 1);
				*(dataRoot->child + i) = *(dataRoot->child + i + 1);
			}
			*(dataRoot->child + i) = *(dataRoot->child + i + 1);
		}
		else
		{
			/**
			 * check if sibiling can lend one recursively on both sides
			 * if yes move and at last delete this node
			 * else merge with a sibiling and bring the parent down
			 * 		and move recursively up and do this same for the parent
			**/

		}
	}	
}

struct bStarTreeNode* deleteFromBStarTree(struct bStarTreeNode **root,int priVal)
{
	struct bStarTreeDataNode *temp = deleteFromBStarTree0((*root)->dataRoot,nodeSize,priVal);
	if(temp != NULL)
	{
		(*root)->dataRoot = temp;
	}
	return root;
}
