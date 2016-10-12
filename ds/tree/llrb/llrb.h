#include<stdio.h>
#define boolean int
#define false 0
#define true 1

struct llrbNode
{
	int val;
	struct llrbNode *parent,*left,*right;
	boolean isRed;
};

void rotateRight(struct llrbNode *temp)
{
	struct llrbNode *temp1 = temp->parent;
	temp->parent = temp1->parent;
	if(temp->parent != NULL)
	{
		if(temp->parent->left == temp1)
		{
			temp->parent->left = temp;
		}
		else
		{
			temp->parent->right = temp;
		}
	}
	temp->isRed = temp1->isRed;
	temp1->left = temp->right;
	if( temp1->left != NULL)
	{
		temp1->left->parent = temp1;
	}
	temp->right = temp1;
	temp1->parent = temp;
	temp1->isRed = true;
}

void rotateLeft(struct llrbNode *temp)
{
	struct llrbNode *temp1 = temp->right,*temp2 = temp->right->left;

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
	temp1->isRed = temp->isRed;
	temp->isRed = true;
}

void colorFlip(struct llrbNode *temp)
{
	temp->left->isRed = temp->right->isRed = false;
	if(temp->parent != NULL)
	{
		temp->isRed = true;
	}
	else
	{
		temp->isRed = false;
	}
}

int height(struct llrbNode* temp)
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

struct llrbNode* rotateTree(struct llrbNode *root)
{
	boolean isChanged = false;

	if(root == NULL)
	{
		return;
	}
	if(root->right!= NULL && root->right->isRed && (root->left == NULL || !root->left->isRed))
	{
		rotateLeft(root);
		root = root->parent;
	}

	if(root->isRed && root->left!= NULL && root->left->isRed )
	{
		rotateRight(root);
	}

	if(root->left != NULL && root->right != NULL && root->left->isRed && root->right->isRed)
	{
		colorFlip(root);
		isChanged = true;
	}

	return root;
}

void printLLRBTree(struct llrbNode *root)
{
	if(root == NULL)
	{
		return;
	}
	printf("\nval: %d , me: %p , left: %p , right: %p , parent: %p , color : %s",root->val,root,root->left,root->right,root->parent,root->isRed ? "RED" : "BLACK");
	if(root->left != NULL)
	{
		printLLRBTree(root->left);
	}
	if(root->right != NULL)
	{
		printLLRBTree(root->right);
	}
}

struct llrbNode* searchInLLRBTree(struct llrbNode *root,int secVal)
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
		return searchInLLRBTree(root->right,secVal);
	}
	else
	{
		return searchInLLRBTree(root->left,secVal);
	}
}

struct llrbNode* llrbInserter(struct llrbNode *root,struct llrbNode *insertNode)
{
	if(root->val < insertNode->val)
	{
		if(root->right == NULL)
		{
			root->right = insertNode;
			insertNode->parent = (root);
		}
		else
		{
			llrbInserter(root->right,insertNode);
		}
	}
	else if(root->val > insertNode->val)
	{
		if(root->left == NULL)
		{
			root->left = insertNode;
			insertNode->parent = (root);
		}
		else
		{
			llrbInserter(root->left,insertNode);
		}
	}
	else
	{
		//already value present
		return NULL;
	}

	return rotateTree(root);
}

void insertToLLRBTree(struct llrbNode **root,int priVal)
{
    struct llrbNode *insertNode = (struct llrbNode*)malloc(sizeof(struct llrbNode));
    insertNode->val = priVal;
    insertNode->parent = insertNode->left = insertNode->right = NULL;
    insertNode->isRed = true;
    if(*root == NULL)
    {
            *root = insertNode;
            insertNode->isRed = false;
            return;
    }

    if(llrbInserter(*root,insertNode) == NULL)
    {
        free(insertNode);
    }
    else if((*root)->parent != NULL)
    {
    	*root = (*root)->parent;
    }
}


struct llrbNode* deleteFromBSTTree(struct llrbNode **root,int priVal)
{
	struct llrbNode *freePt = NULL;
	if(*root == NULL)
	{
		return NULL;
	}
	else if((*root)->val < priVal)
	{
		(*root)->right = deleteFromBSTTree(&(*root)->right,priVal);
		rotateTree(*root);
	}
	else if((*root)->val > priVal)
	{
		(*root)->left = deleteFromBSTTree(&(*root)->left,priVal);
		rotateTree(*root);
	}
	else
	{
		struct llrbNode* temp = NULL;
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
	return *root;
}

struct llrbNode* deleteFromLLRBTree(struct llrbNode **root,int priVal)
{
	deleteFromBSTTree(root,priVal);
	// rotateTree(root);
	// rootCorrector(root);
}
