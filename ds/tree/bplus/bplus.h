#include<stdio.h>
#define boolean int
#define false 0
#define true 1

struct bPlusNode
{
	struct bPlusDataNode 
	{
		int* val;
		int size;
		struct bPlusNode *parent,**child;
	}*dataRoot;
	int nodeSize;
};

//bPlusNodeSize repersents the no of values inside a b-plus node
struct bPlusNode* createBPlusNode(int bPlusNodeSize)
{
	int i=0;
	struct bPlusNode *temp = (struct bPlusNode*)malloc(sizeof(struct bPlusNode));
	temp->nodeSize = bPlusNodeSize;
	temp->dataRoot = (struct bPlusDataNode*)malloc(sizeof(struct bPlusDataNode));
	temp->dataRoot->val = (int*)malloc(sizeof(int)*bPlusNodeSize);
	temp->dataRoot->size = 0;
	temp->dataRoot->parent = NULL;
	temp->dataRoot->child = (struct bPlusDataNode**)malloc(sizeof(struct bPlusDataNode*)*(bPlusNodeSize+1));
	for(;i<=bPlusNodeSize;++i)
	{
		*(temp->dataRoot->child + i) = NULL;
	}
	/*for(i=0;i<=bPlusNodeSize;++i)
	{
		printf("%p\n", *(temp->root->child + i) );
	}*/
	return temp;
}

struct bPlusNode* searchInBPlusTree(struct bPlusNode *root,int secVal)
{
	/*if(root == NULL)
	{
		return NULL;
	}
	else if(root->val == secVal)
	{
		return root;
	}
	else if(root->val < secVal)
	{
		return searchInBPlusTree(root->right,secVal);
	}
	else
	{
		return searchInBPlusTree(root->left,secVal);
	}*/
}

struct bPlusNode* bPlusInserter(struct bPlusNode **root,struct bPlusNode *insertNode)
{
	/*if((*root)->val < insertNode->val)
	{
		if((*root)->right == NULL)
		{
			(*root)->right = insertNode;
			insertNode->parent = (*root);
			return insertNode;
		}
		else
		{
			BPlusInserter(&(*root)->right,insertNode);
			rotateTree(root);
			return *root;
		}
	}
	else if((*root)->val > insertNode->val)
	{
		if((*root)->left == NULL)
		{
			(*root)->left = insertNode;
			insertNode->parent = (*root);
			return insertNode;
		}
		else
		{
			BPlusInserter(&(*root)->left,insertNode);
			rotateTree(root);
			return *root;
		}
	}
	return NULL;*/
}

struct bPlusDataNode* insertToBPlusTree(struct bPlusNode **root,int priVal)
{
    struct bPlusDataNode *dataRoot = (*root)->dataRoot, *childNode = NULL;
    int nodeSize = (*root)->nodeSize, i = 0, totalSize = dataRoot->size;
    for( ; i < totalSize ; ++i )
    {
    	if( *(dataRoot->val + i) > priVal)
    	{
    		break;
    	}
    }

	if( *(dataRoot->child + i) != NULL )
	{
		childNode = insertToBPlusTree((dataRoot->child + i),priVal);
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
	

	if(totalSize <= nodeSize)
	{
		int j=totalSize;
		for( ; j > i ; --j)
		{
			*(dataRoot->val + j) = *(dataRoot->val + j - 1);
		}
		*(dataRoot->val + j) = priVal;
		dataRoot->size = dataRoot->size + 1;
		
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
		int j,k;
		struct bPlusDataNode tempData1,tempData2;

		//creating two new nodes
		tempData1 = (struct bPlusDataNode*)malloc(sizeof(struct bPlusDataNode));
		tempData1->val = (int*)malloc(sizeof(int)*bPlusNodeSize);
		tempData1->size = 0;
		tempData1->parent = NULL;
		tempData1->child = (struct bPlusDataNode**)malloc(sizeof(struct bPlusDataNode*)*(bPlusNodeSize+1));

		tempData2 = (struct bPlusDataNode*)malloc(sizeof(struct bPlusDataNode));
		tempData2->val = (int*)malloc(sizeof(int)*bPlusNodeSize);
		tempData2->size = 0;
		tempData2->parent = NULL;
		tempData2->child = (struct bPlusDataNode**)malloc(sizeof(struct bPlusDataNode*)*(bPlusNodeSize+1));
		for(;i<=bPlusNodeSize;++i)
		{
			*(tempData1->child + i) = *(tempData2->child + i) = NULL;
		}
		

		//coping the value across the nodes
		for( j = 0; j < nodeSize/2 ; ++j)
		{
			if(j != i)
			{
				*(tempData1->val + j) = *(dataRoot->val + j);
			}
			else
			{
				*(tempData1->val + j) = priVal;
				if(childNode != NULL)
				{
					*(dataRoot->child + i) = *(childNode->child);
					*(dataRoot->child + i + 1) = *(childNode->child + 1);
					(*(childNode->child))->parent = (*(childNode->child + 1))->parent = dataRoot;
				}
			}
		}
		tempData1->size = j;

		if(j != i)
		{
			*(dataRoot->val) = *(dataRoot->val + j);
		}
		else
		{
			*(dataRoot->val) = priVal;
			if(childNode != NULL)
			{
				*(dataRoot->child + i) = *(childNode->child);
				*(dataRoot->child + i + 1) = *(childNode->child + 1);
				(*(childNode->child))->parent = (*(childNode->child + 1))->parent = dataRoot;
			}
		}
		dataRoot->size = 1;

		for( ++j,k = 0; j < nodeSize ; ++j,++k)
		{
			if(j != i)
			{
				*(tempData2->val + k) = *(dataRoot->val + j);
			}
			else
			{
				*(tempData2->val + k) = priVal;
				if(childNode != NULL)
				{
					*(dataRoot->child + i) = *(childNode->child);
					*(dataRoot->child + i + 1) = *(childNode->child + 1);
					(*(childNode->child))->parent = (*(childNode->child + 1))->parent = dataRoot;
				}
			}
		}

		//keeping up the child parent relationship
		tempData1->parent = tempData2->parent = dataRoot;
		*(dataRoot->child) = tempData1;
		*(dataRoot->child + 1) = tempData2;
	}

	return dataRoot;
}

void printBPlusTree(struct bPlusNode *root)
{
	/*if(root == NULL)
	{
		return;
	}
	printf("\nval: %d , me: %p , left: %p , right: %p , parent: %p , color : %s",root->val,root,root->left,root->right,root->parent,root->isRed ? "RED" : "BLACK");
	if(root->left != NULL)
	{
		printBPlusTree(root->left);
	}
	if(root->right != NULL)
	{
		printBPlusTree(root->right);
	}*/
}

struct bPlusNode* deleteFromBSTTree(struct bPlusNode **root,int priVal)
{
	/*struct bPlusNode *freePt = NULL;
	if(*root == NULL)
	{
		return NULL;
	}
	else if((*root)->val < priVal)
	{
		(*root)->right = deleteFromBSTTree(&(*root)->right,priVal);
		rotateTree(root);
	}
	else if((*root)->val > priVal)
	{
		(*root)->left = deleteFromBSTTree(&(*root)->left,priVal);
		rotateTree(root);
	}
	else
	{
		struct bPlusNode* temp = NULL;
		if((*root)->left == NULL && (*root)->right == NULL)
		{
			//do nothing
		}
		else if((*root)->left == NULL)
		{
			temp = (*root)->right;
			temp->parent = (*root)->parent;			
			freePt = *root;
		}
		else if((*root)->right == NULL)
		{
			temp = (*root)->left;
			temp->parent = (*root)->parent;
			temp->isRed = false;
			freePt = *root;
		}
		else
		{
			//replacing with the predecessor
			temp = (*root)->left;
			while(temp->right != NULL)
			{
				temp = temp->right;
			}
			(*root)->val = temp->val;
			if(temp->parent != *root)
			{
				temp->parent->right = temp->left;
			}
			else
			{
				temp->parent->left = temp->left;
			}
			if(temp->left != NULL)
            {
                temp->left->parent = temp->parent;
            }
			freePt = temp;
			temp = *root;
		}
		if(freePt != NULL)
		{
			if(temp->parent == NULL)
			{
				*root = temp;
			}
			free(freePt);
		}
		return temp;
	}
	return *root;*/
}

struct bPlusNode* deleteFromBPlusTree(struct bPlusNode **root,int priVal)
{
	// deleteFromBSTTree(root,priVal);
	// rotateTree(root);
	// rootCorrector(root);
}
