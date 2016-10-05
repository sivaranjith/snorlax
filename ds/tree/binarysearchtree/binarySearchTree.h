struct biSearchNode
{
	int val;
	struct biSearchNode *parent,*left,*right;
};

struct biSearchNode* searchInBinarySearchTree(struct biSearchNode *root,int secVal)
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
		return searchInBinarySearchTree(root->right,secVal);
	}
	else
	{
		return searchInBinarySearchTree(root->left,secVal);
	}
}

struct biSearchNode* bstInserter(struct biSearchNode *root,struct biSearchNode *insertNode)
{
	if(root->val < insertNode->val)
	{
		if(root->right == NULL)
		{
			root->right = insertNode;
			insertNode->parent = root;
			return insertNode;
		}
		else
		{
			return bstInserter(root->right,insertNode);
		}
	}
	else if(root->val > insertNode->val)
	{
		if(root->left == NULL)
		{
			root->left = insertNode;
			insertNode->parent = root;
			return insertNode;
		}
		else
		{
			return bstInserter(root->left,insertNode);
		}
	}
	return NULL;
}

void insertToBinarySearchTree(struct biSearchNode **root,int priVal)
{
        struct biSearchNode *insertNode = (struct biSearchNode*)malloc(sizeof(struct biSearchNode));
        insertNode->val = priVal;
        insertNode->parent = insertNode->left = insertNode->right = NULL;
        if(*root == NULL)
        {
                *root = insertNode;
                return;
        }
        if(bstInserter(*root,insertNode) == NULL)
        {
                free(insertNode);
        }
}

void printBinarySearchTree(struct biSearchNode *root)
{
	if(root == NULL)
	{
		return;
	}
	printf("\nval: %d , me: %p , left: %p , right: %p , parent: %p",root->val,root,root->left,root->right,root->parent);
	if(root->left != NULL)
	{
		printBinarySearchTree(root->left);
	}
	if(root->right != NULL)
	{
		printBinarySearchTree(root->right);
	}
}

struct biSearchNode* deleteFromBinarySearchTree(struct biSearchNode **root,int priVal)
{
	struct biSearchNode *freePt = NULL;
	if(*root == NULL)
	{
		return NULL;
	}
	else if((*root)->val < priVal)
	{
		(*root)->right = deleteFromBinarySearchTree(&(*root)->right,priVal);
	}
	else if((*root)->val > priVal)
	{
		(*root)->left = deleteFromBinarySearchTree(&(*root)->left,priVal);
	}
	else
	{
		struct biSearchNode* temp = NULL;
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
