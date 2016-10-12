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
	if(temp->left != NULL)
	{
		temp->left->isRed = !temp->left->isRed;
	}
	if(temp->right != NULL)
	{
		temp->right->isRed = !temp->right->isRed;
	}
	if(temp->parent != NULL)
	{
		temp->isRed = !temp->isRed;
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

struct llrbNode* moveRedLeft(struct llrbNode* temp)
{
	colorFlip(temp);
	if(temp->right != NULL && temp->right->left != NULL && temp->right->left->isRed)
	{
		rotateRight(temp->right);
		temp = temp->parent;
		rotateLeft(temp);
		colorFlip(temp);
	}
	return temp;
}

struct llrbNode* moveRedRight(struct llrbNode *temp)
{
	colorFlip(temp);
	if(temp->left != NULL && temp->left->left != NULL && temp->left->left->isRed)
	{
		rotateRight(temp);
		colorFlip(temp);
	}
	return temp;
}

struct llrbNode* deleteMin(struct llrbNode* temp)
{
	if(temp == NULL)
	{
		return NULL;
	}
	if(temp->left == NULL)
	{
		free(temp);
		return NULL;
	}

	if(!temp->left->isRed && temp->left->left != NULL && !temp->left->left->isRed)
	{
		temp = moveRedLeft(temp);
	}

	temp->left = deleteMin(temp->left);

	rotateTree(temp);
}

int min(struct llrbNode *temp)
{
	while(temp->left != NULL)
	{
		temp = temp->left;
	}
	return temp->val;
}

struct llrbNode* deleteFromLLRBTree(struct llrbNode *root,int priVal)
{
	if(root == NULL)
	{
		return NULL;
	}


	if(root->val > priVal)
	{
		//push the red link down to the left
		if(root->left != NULL && root->left->left != NULL && !root->left->isRed && !root->left->left->isRed)
		{
			moveRedLeft(root);
		}
		root->left = deleteFromLLRBTree(root->left,priVal);
	}
	else
	{
		//making tree right lean
		if(root->left != NULL && root->left->isRed)
		{
			rotateRight(root);
		}
		if(root->val == priVal && root->right == NULL)
		{
			free(root);
			return NULL;
		}

		//push the red link down to the right
		if(root->right != NULL && root->right->left != NULL && !root->right->isRed && !root->right->left->isRed)
		{
			moveRedRight(root);
		}

		if(root->val == priVal)
		{
			root->val = min(root->right);
			root->right = deleteMin(root->right);
		}
		else
		{
			root->right = deleteFromLLRBTree(root->right,priVal);
		}
	}

	return rotateTree(root);
}
