#include<stdio.h>
struct avlNode
{
	int val;
	struct avlNode *parent,*left,*right;
};

void rotateRight(struct avlNode *temp)
{
	struct avlNode *temp1 = temp->left,*temp2 = temp->left->right;

	if(temp->parent != NULL)
	{
		if(temp->parent->left == temp)
		{
			temp->parent->left = temp1;
		}
		else
		{
			temp->parent->right = temp1;
		}
	}

	temp1->parent = temp->parent;
	temp1->right = temp;
	temp->parent = temp1;
	temp->left = temp2;
	if(temp2 != NULL)
	{
		temp2->parent = temp;
	}
}

void rotateLeft(struct avlNode *temp)
{
	struct avlNode *temp1 = temp->right,*temp2 = temp->right->left;

	if(temp->parent != NULL)
	{
		if(temp->parent->left == temp)
		{
			temp->parent->left = temp1;
		}
		else
		{
			temp->parent->right = temp1;
		}
	}
	
	temp1->parent = temp->parent;
	temp1->left = temp;
	temp->parent = temp1;
	temp->right = temp2;
	if(temp2 != NULL)
	{
		temp2->parent = temp;
	}
}

int height(struct avlNode* temp)
{
	int leftHeight,rightHeight,max;
	if(temp == NULL)
	{
		return 0;
	}
	leftHeight = height(temp->left);
	rightHeight = height(temp->right);
	return leftHeight < rightHeight ? rightHeight + 1 :  leftHeight + 1;
}

void rotateTree(struct avlNode **root)
{
	struct avlNode *temp = *root;
	int diff=0;
	if(temp == NULL)
	{
		return;
	}
	diff = height(temp->right) - height(temp->left);
	if( diff < -1 )
	{
		/*int diff = height(temp->left->right) - height(temp->left->left);
		if(diff < -1 || diff > 1)
		{
			return;
		}
		else if(diff == 1)
		{
			rotateLeft(temp->left);
			rotateRight(temp);
		}
		else
		{
			rotateRight(temp);
		}*/
		rotateRight(temp);
	}
	else if( diff > 1 )
	{
		/*int diff = height(temp->right->right) - height(temp->right->left);
		if(diff < -1 || diff > 1)
		{
			return;
		}
		else if(diff == -1)
		{
			rotateRight(temp->right);
			rotateLeft(temp);
		}
		else
		{
			rotateLeft(temp);
		}*/
		rotateLeft(temp);
	}
	else
	{
		return;
	}

	if(temp->parent->parent == NULL)
	{
		*root = temp->parent;
	}
}

struct avlNode* searchInAVLTree(struct avlNode *root,int secVal)
{
	if(root == NULL)
	{
		return NULL;
	}
	else if(root->val == secVal)
	{
		return root;
	}
	else if(root->val < secVal)
	{
		return searchInAVLTree(root->right,secVal);
	}
	else
	{
		return searchInAVLTree(root->left,secVal);
	}
}

struct avlNode* avlInserter(struct avlNode **root,struct avlNode *insertNode)
{
	if((*root)->val < insertNode->val)
	{
		if((*root)->right == NULL)
		{
			(*root)->right = insertNode;
			insertNode->parent = (*root);
			return insertNode;
		}
		else
		{
			avlInserter(&(*root)->right,insertNode);
			rotateTree(root);
			return (*root);
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
			avlInserter(&(*root)->left,insertNode);
			rotateTree(root);
			return (*root);
		}
	}
	return NULL;
}

void insertToAVLTree(struct avlNode **root,int priVal)
{
        struct avlNode *insertNode = (struct avlNode*)malloc(sizeof(struct avlNode));
        insertNode->val = priVal;
        insertNode->parent = insertNode->left = insertNode->right = NULL;
        if(*root == NULL)
        {
                *root = insertNode;
                return;
        }
        if(avlInserter(root,insertNode) == NULL)
        {
                free(insertNode);
        }
	/*else
	{
		rotateTree(root);
	}*/
}

void printAVLTree(struct avlNode *root)
{
	if(root == NULL)
	{
		return;
	}
	printf("\nval: %d , me: %p , left: %p , right: %p , parent: %p",root->val,root,root->left,root->right,root->parent);
	if(root->left != NULL)
	{
		printAVLTree(root->left);
	}
	if(root->right != NULL)
	{
		printAVLTree(root->right);
	}
}

struct avlNode* deleteFromBSTTree(struct avlNode **root,int priVal)
{
	struct avlNode *freePt = NULL;
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
		struct avlNode* temp = NULL;
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
	return *root;
}

struct avlNode* deleteFromAVLTree(struct avlNode **root,int priVal)
{
	deleteFromBSTTree(root,priVal);
}
