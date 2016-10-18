#include<stdio.h>
#define boolean int
#define false 0
#define true 1

struct bTreeNode
{
	struct bTreeDataNode 
	{
		int* val;
		int size;
		struct bTreeDataNode *parent,**child;
	}*dataRoot;
	int nodeSize;
};

//bTreeNodeSize repersents the no of values inside a b-plus node
struct bTreeNode* createBTreeNode(int bTreeNodeSize)
{
	int i=0;
	struct bTreeNode *temp = (struct bTreeNode*)malloc(sizeof(struct bTreeNode));
	temp->nodeSize = bTreeNodeSize;
	temp->dataRoot = (struct bTreeDataNode*)malloc(sizeof(struct bTreeDataNode));
	temp->dataRoot->val = (int*)malloc(sizeof(int)*bTreeNodeSize);
	temp->dataRoot->size = 0;
	temp->dataRoot->parent = NULL;
	temp->dataRoot->child = (struct bTreeDataNode**)malloc(sizeof(struct bTreeDataNode*)*(bTreeNodeSize+1));
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

struct bTreeDataNode* searchData(struct bTreeDataNode *dataRoot,int secVal)
{
	int i;
	if(dataRoot == NULL)
	{
		return NULL;
	}
	for(i = 0; i < dataRoot->size; ++i)
	{
		if(*(dataRoot->val + i) == secVal)
		{
			return dataRoot;
		}
		else if(*(dataRoot->val +i) > secVal)
		{
			return searchData(*(dataRoot->child + i),secVal);
		}
	}
	return searchData(*(dataRoot->child + i),secVal);
}

struct bTreeDataNode* searchInBTreeTree(struct bTreeNode *root,int secVal)
{
	return searchData(root->dataRoot,secVal);
}

struct bTreeDataNode* bTreeInserterroot(struct bTreeDataNode *dataRoot,int nodeSize,int priVal)
{
    struct bTreeDataNode *childNode = NULL;
    int i = 0, totalSize = dataRoot->size;
    for( ; i < totalSize ; ++i )
    {
    	if( *(dataRoot->val + i) > priVal)
    	{
    		break;
    	}
    	else if( *(dataRoot->val + i) == priVal)
    	{
    		return NULL;
    	}
    }

	if( *(dataRoot->child + i) != NULL )
	{
		childNode = bTreeInserterroot(*(dataRoot->child + i),nodeSize,priVal);
		if(childNode != NULL)
		{
			priVal = *(childNode->val);
			for( i = 0 ; i < totalSize ; ++i )
		    {
		    	if( *(dataRoot->val + i) > priVal)
		    	{
		    		break;
		    	}
		    }
		}
		else
		{
			return NULL;
		}
	}
	
	if(totalSize < nodeSize)
	{
		int j=totalSize;
		for( ; j > i ; --j)
		{
			*(dataRoot->val + j) = *(dataRoot->val + j - 1);
		}
		*(dataRoot->val + j) = priVal;
		++(dataRoot->size);
		
		if(childNode != NULL)
		{
			*(dataRoot->child + i) = *(childNode->child);
			*(dataRoot->child + i + 1) = *(childNode->child + 1);
			(*(childNode->child))->parent = (*(childNode->child + 1))->parent = dataRoot;
		}
		
		return NULL;
	}
	else
	{
		//break up the node
		int j,k,childCounter = 0;
		struct bTreeDataNode *tempData1,*tempData2;

		//creating two new nodes
		tempData1 = (struct bTreeDataNode*)malloc(sizeof(struct bTreeDataNode));
		tempData1->val = (int*)malloc(sizeof(int)*nodeSize);
		tempData1->size = 0;
		tempData1->parent = NULL;
		tempData1->child = (struct bTreeDataNode**)malloc(sizeof(struct bTreeDataNode*)*(nodeSize+1));

		tempData2 = (struct bTreeDataNode*)malloc(sizeof(struct bTreeDataNode));
		tempData2->val = (int*)malloc(sizeof(int)*nodeSize);
		tempData2->size = 0;
		tempData2->parent = NULL;
		tempData2->child = (struct bTreeDataNode**)malloc(sizeof(struct bTreeDataNode*)*(nodeSize+1));
		for(k = 0; k <= nodeSize; ++k)
		{
			*(tempData1->child + k) = *(tempData2->child + k) = NULL;
		}
		

		//coping the value across the nodes
		for( j = 0; j < nodeSize/2 ; ++j)
		{
			if(j != i)
			{
				*(tempData1->val + j) = *(dataRoot->val + j);
				if(j != i+1)
				{
					*(tempData1->child + j) = *(dataRoot->child + j);
					if(*(tempData1->child +j) != NULL)
					{
						(*(tempData1->child + j))->parent = tempData1;
					}
				}
			}
			else
			{
				*(tempData1->val + j) = priVal;
				if(childNode != NULL)
				{
					*(dataRoot->child + i) = *(childNode->child);
					*(dataRoot->child + i + 1) = *(childNode->child + 1);
					(*(childNode->child))->parent = (*(childNode->child + 1))->parent = dataRoot;
					
					*(tempData1->child + j) = *(childNode->child);
					*(tempData1->child + j + 1) = *(childNode->child + 1);

					if(*(tempData1->child + j) != NULL)
					{
						(*(tempData1->child + j))->parent = (*(tempData1->child + j + 1))->parent = tempData1;
					}
				}
			}
		}
		tempData1->size = j;

		if(j != i)
		{
			*(dataRoot->val) = *(dataRoot->val + j);
			if(j != i+1)
			{
				*(tempData1->child + j) = *(dataRoot->child + j);
				if(*(tempData1->child +j) != NULL)
				{
					(*(tempData1->child + j))->parent = tempData1;
				}
			}
		}
		else
		{
			*(dataRoot->val) = priVal;
			if(childNode != NULL)
			{
				*(dataRoot->child + i) = *(childNode->child);
				*(dataRoot->child + i + 1) = *(childNode->child + 1);
				(*(childNode->child))->parent = (*(childNode->child + 1))->parent = dataRoot;
				
				*(tempData1->child + j) = *(childNode->child);
				*(tempData2->child + childCounter) = *(childNode->child + 1);

				if(*(tempData1->child + j) != NULL)
				{
					(*(tempData1->child + j))->parent = tempData1;
					(*(tempData2->child + childCounter))->parent = tempData2;
				}
			}
			++childCounter;
		}
		dataRoot->size = 1;

		for( ++j,k = 0; j <= nodeSize ; ++j,++k)
		{
			if(j != i)
			{
				*(tempData2->val + k) = *(dataRoot->val + j);
				if(j != i+1)
				{
					*(tempData2->child + childCounter) = *(dataRoot->child + j);
					if(*(tempData2->child + childCounter) != NULL)
					{
						(*(tempData2->child + childCounter))->parent = tempData2;
					}
					++childCounter;
				}
			}
			else
			{
				*(tempData2->val + k) = priVal;

				if(childNode != NULL)
				{
					*(dataRoot->child + i) = *(childNode->child);
					*(dataRoot->child + i + 1) = *(childNode->child + 1);
					(*(childNode->child))->parent = (*(childNode->child + 1))->parent = dataRoot;
	
					*(tempData2->child + childCounter) = *(childNode->child);
					*(tempData2->child + childCounter + 1) = *(childNode->child + 1);

					if(*(tempData2->child + childCounter) != NULL)
					{
						(*(tempData2->child + childCounter))->parent = (*(tempData2->child + childCounter + 1))->parent = tempData2;
					}

				}
				childCounter+=2;
			}
		}
		tempData2->size = k;

		//keeping up the child parent relationship
		tempData1->parent = tempData2->parent = dataRoot;
		*(dataRoot->child) = tempData1;
		*(dataRoot->child + 1) = tempData2;
	}

	return dataRoot;
}

struct bTreeDataNode* insertToBTreeTree(struct bTreeNode *root,int priVal)
{
	struct bTreeDataNode *tempDNode = bTreeInserterroot(root->dataRoot,root->nodeSize,priVal);
	if(tempDNode != NULL)
	{
		root->dataRoot = tempDNode;
		// tempDNode->parent = NULL;
	}
	return tempDNode;
}

void printBTreeTree(struct bTreeDataNode *dataRoot)
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
		printBTreeTree( *(dataRoot->child + i) );
	}
}

struct bTreeDataNode* mergeByDeletingvalue(struct bTreeDataNode *dataRootLeft,struct bTreeDataNode *dataRootRight,int nodeSize)
{
	struct bTreeDataNode *tempFromChild = NULL;
	int leftSize = dataRootLeft->size, rightSize = dataRootRight->size, tempSize = 0,i,j;
	if( *(dataRootRight->child) != NULL)
	{
		tempFromChild = mergeByDeletingvalue( *(dataRootLeft->child + dataRootLeft->size), *(dataRootRight->child), nodeSize);
		tempSize = tempFromChild->size;
	}

	if( (tempSize != 1 && leftSize + rightSize > nodeSize) || (tempSize == 1 && leftSize + rightSize + 1 > nodeSize))
	{
		if(tempSize == 1)
		{
			*(dataRootLeft->child + dataRootLeft->size) = *(tempFromChild->child);
			*(dataRootRight->child) = *(tempFromChild->child + 1);
			(*(tempFromChild->child))->parent = dataRootLeft;
			(*(tempFromChild->child + 1))->parent = dataRootRight;

			*(tempFromChild->child) = dataRootLeft;
			*(tempFromChild->child + 1) = dataRootRight;
			dataRootLeft->parent = dataRootRight->parent = tempFromChild;
			return tempFromChild;
		}
		else
		{
			struct bTreeDataNode *referenceNode = NULL, *otherNode = NULL, *newNode = (struct bTreeDataNode*)malloc(sizeof(struct bTreeDataNode));
			int size = 0, otherNodeValue;
			
			if(leftSize >= rightSize)
			{
				referenceNode = dataRootRight;
				*(newNode->val) = *(dataRootLeft->val + dataRootLeft->size - 1);
				--(dataRootLeft->size);
			}
			else
			{
				referenceNode = dataRootLeft;
				*(newNode->val) = *(dataRootRight->val);
				size = dataRootLeft->size;
				for(i = 0; i < dataRootRight->size - 1; ++i)
				{
					*(dataRootRight->val + i) = *(dataRootRight->val + i + 1);
					*(dataRootRight->child + i) = *(dataRootRight->child + i + 1);
				}
				*(dataRootRight->child + i) = *(dataRootRight->child + i + 1);
				--(dataRootRight->size);
			}

			*(referenceNode->child + size) = tempFromChild;
			if(tempFromChild != NULL)
			{
				tempFromChild->parent = referenceNode;
			}
			newNode->parent = NULL;
			*(newNode->child) = dataRootLeft;
			*(newNode->child + 1) = dataRootRight;
			dataRootRight->parent = dataRootLeft->parent = newNode;

			return newNode;
		}
	}
	else
	{
		if(tempSize == 1)
		{
			*(dataRootLeft->val + dataRootLeft->size) = *(tempFromChild->val);
			*(dataRootLeft->child + dataRootRight->size) = *(tempFromChild->child);
			*(dataRootLeft->child + dataRootRight->size + 1) = *(tempFromChild->child + 1);
			(*(tempFromChild->child))->parent = dataRootLeft;
			(*(tempFromChild->child + 1))->parent = dataRootLeft;
			++(dataRootLeft->size);
		}
		else
		{
			if(tempFromChild != NULL)
			{
				tempFromChild->parent = dataRootLeft;
			}
			*(dataRootLeft->child + dataRootLeft->size) = tempFromChild;
		}

		*(dataRootLeft->val + dataRootLeft->size) = *(dataRootRight->val);

		for(i = 1; i < dataRootRight->size; ++i)
		{
			*(dataRootLeft->val + dataRootLeft->size + i) = *(dataRootRight->val + i);
			*(dataRootLeft->child + dataRootLeft->size + i) = *(dataRootRight->child + i);
		}
		
		*(dataRootLeft->child + dataRootLeft->size + i) = *(dataRootRight->child + i);
		dataRootLeft->size += dataRootRight->size;
		
		free(dataRootRight);
		return dataRootLeft;
	}
}

struct bTreeDataNode* rotateOrMerge(struct bTreeDataNode *dataRoot,int i,int t)
{
	int g,j;
	struct bTreeDataNode *parent = dataRoot->parent, *sibiling;
	for(j = 0; j < parent->size; ++j)
	{
		if(*(parent->child + j) == dataRoot)
		{
			break;
		}
	}

	if(j != 0)
	{
		sibiling = *(parent->child + j - 1);
		if(sibiling->size >= t )
		{
			for(g = i; g > 0; --g)
			{
				*(dataRoot->val + g) = *(dataRoot->val + g - 1);
				*(dataRoot->child + g) = *(dataRoot->child + g - 1);
			}
			*(dataRoot->val) = *(parent->val + j - 1);
			*(dataRoot->child) = *(sibiling->child + sibiling->size);

			*(parent->val + j - 1) = *(sibiling->val + sibiling->size - 1);

			--(sibiling->size);
			return NULL;
		}
	}

	if(j != parent->size)
	{
		sibiling = *(parent->child + j + 1);
		if(sibiling->size >= t )
		{
			*(dataRoot->val + dataRoot->size) = *(parent->val + j);
			*(dataRoot->child + dataRoot->size + 1) = *(sibiling->child);

			*(parent->val + j) = *(sibiling->val);

			for(g = 0; g < sibiling->size - 1; ++g)
			{
				*(sibiling->val + g) = *(sibiling->val + g + 1);
				*(sibiling->child + g) = *(sibiling->child + g + 1);
			}
			*(sibiling->child + g) = *(sibiling->child + g + 1);

			for(g = i; g < dataRoot->size ; ++g)
			{
				*(dataRoot->val + g) = *(dataRoot->val + g + 1);
				*(dataRoot->child + g) = *(dataRoot->child + g + 1);
			}
			*(dataRoot->child + g) = *(dataRoot->child + g + 1);

			--(sibiling->size);
			return NULL;
		}
		sibiling = *(parent->child + j - 1);
	}

	if(j != 0)
	{
		sibiling = *(parent->child + j - 1);
		*(sibiling->val + sibiling->size) = *(parent->val + j - 1);
		++(sibiling->size);

		for(g = 0; g < dataRoot->size; ++g)
		{
			*(sibiling->val + sibiling->size + g) = *(dataRoot->val + g);
			*(sibiling->child + sibiling->size + g) = *(dataRoot->child + g);
		}
		*(sibiling->child + sibiling->size + g) = *(dataRoot->child + g);

		sibiling->size += dataRoot->size;

		free(dataRoot);

		g = j - 1;
	}
	else
	{
		sibiling = *(parent->child + j + 1);
		*(dataRoot->val + dataRoot->size) = *(parent->val + j);
		++(dataRoot->size);

		for(g = 0; g < sibiling->size; ++g)
		{
			*(dataRoot->val + dataRoot->size + g) = *(sibiling->val + g);
			*(dataRoot->child + dataRoot->size + g) = *(sibiling->child + g);
		}
		*(dataRoot->child + dataRoot->size + g) = *(sibiling->child + g);

		dataRoot->size += sibiling->size;

		free(sibiling);

		g = j;
	}
	
	for(; g < parent->size - 1; ++g)
	{
		*(parent->val + g) = *(parent->val + g + 1);
		*(parent->child + g + 1) = *(parent->child + g + 2);
	}
	--(parent->size);

	if(parent->size == 0)
	{
		(*(parent->child))->parent = NULL;
		return *(parent->child);
	}
	return NULL;
}

struct bTreeDataNode* deleteFromBSTTree(struct bTreeDataNode *dataRoot,int priVal,int nodeSize)
{
	int i,j;
	int t = (nodeSize + 1)/2;
	if(dataRoot == NULL)
	{
		return NULL;
	}
	for(i = 0; i < dataRoot->size; ++i)
	{
		if(*(dataRoot->val + i) == priVal)
		{
			if(*(dataRoot->child + i) == NULL && *(dataRoot->child + i + 1) == NULL)
			{
				if(dataRoot->size >= t || dataRoot->parent == NULL)
				{
					for(j = i; j < dataRoot->size - 1; ++j)
					{
						*(dataRoot->val + j) = *(dataRoot->val + j + 1);
					}
					--(dataRoot->size);
					return NULL;
				}
				else
				{
					return rotateOrMerge(dataRoot,i,t);
				}
			}
			else
			{
				int sizePre = 0, sizePost = 0;
				struct bTreeDataNode *temp = *(dataRoot->child + i);

				while(*(temp->child + temp->size) != NULL)
				{
					temp = *(temp->child + temp->size);
				}
				sizePre = temp->size;

				if(temp->size >= t)
				{
					*(dataRoot->val + i) = *(temp->val + temp->size - 1);
					return deleteFromBSTTree(*(dataRoot->child + i),*(dataRoot->val + i),nodeSize);
				}
				else
				{
					temp = *(dataRoot->child + i + 1);
					while(*(temp->child) != NULL)
					{
						temp = *(temp->child);
					}
					sizePost = temp->size;

					if(temp->size >= t)
					{
						*(dataRoot->val + i) = *(temp->val);
						return deleteFromBSTTree(*(dataRoot->child + i + 1),*(dataRoot->val + i),nodeSize);
					}
					else
					{
						struct bTreeDataNode *tempRoot = mergeByDeletingvalue(*(dataRoot->child + i),*(dataRoot->child + i + 1),nodeSize);
						if(tempRoot->size == 1)
						{
							*(dataRoot->val + i) = *(tempRoot->val);
							*(dataRoot->child + i) = *(tempRoot->child);
							*(dataRoot->child + i + 1) = *(tempRoot->child + 1);
							(*(tempRoot->child))->parent = (*(tempRoot->child + 1))->parent = dataRoot;
						}
						else
						{
							int g;
							*(dataRoot->child + i) = tempRoot;
							tempRoot->parent = dataRoot;

							for(g = i; g < dataRoot->size - 1; ++g)
							{
								*(dataRoot->val + g) = *(dataRoot->val + g + 1);
								*(dataRoot->child + g + 1) = *(dataRoot->child + g + 2);
							}
							--(dataRoot->size);
						}
						return dataRoot;
					}
				}
			}
		}
		else if(*(dataRoot->val + i) > priVal)
		{
			//actually should check for t-1 values in this node and do the neccessary actions if not
			//solution should make sure all the above the ansestors have t-1(except for root) after the parent got t-1 values
			if( dataRoot->size < t-1)
			{
				// rotateOrMerge(dataRoot,i,t);
			}
			return deleteFromBSTTree(*(dataRoot->child + i),priVal,nodeSize);
		}
	}
	return deleteFromBSTTree(*(dataRoot->child + i),priVal,nodeSize);
}

struct bTreeNode* deleteFromBTreeTree(struct bTreeNode **root,int priVal)
{
	struct bTreeDataNode *dataRoot = (*root)->dataRoot;
	struct bTreeDataNode *temp = deleteFromBSTTree(dataRoot,priVal,(*root)->nodeSize);
	if(temp != NULL && temp->parent == NULL)
	{
		(*root)->dataRoot = temp;
	}
	return *root;
	// rotateTree(root);
	// rootCorrector(root);
}
