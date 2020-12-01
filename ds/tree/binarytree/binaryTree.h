struct biNode
{
	int val;
	struct biNode *parent,*left,*right;
};

struct biNode* searchInBinaryTree(struct biNode *root,int secVal)
{
	struct biNode *itr = root,*temp = NULL;
	if(itr == NULL)
	{
		return NULL;
	}
	else if(itr->val == secVal)
	{
		return itr;
	}
	if(itr->left != NULL)
	{
		temp = searchInBinaryTree(itr->left,secVal);
	}
	if(temp == NULL && itr->right != NULL)
	{
		temp = searchInBinaryTree(itr->right,secVal);
	}
	return temp;
}

void insertToBinaryTree(struct biNode **root,int priVal,int secVal)
{
	struct biNode *insertNode = (struct biNode*)malloc(sizeof(struct biNode));
	insertNode->val = priVal;
	insertNode->parent = insertNode->left = insertNode->right = NULL;
	struct biNode *temp = searchInBinaryTree(*root,secVal);
	if(temp != NULL)
	{
		if(temp->left == NULL)
		{
			temp->left = insertNode;
		}
		else if(temp->right == NULL)
		{
			temp->right = insertNode;
		}
		else
		{
			insertNode->left = temp->left;
			insertNode->left->parent = insertNode;
			temp->left = insertNode;
		}
		insertNode->parent = temp;
	}
	else if(*root == NULL)
	{
		*root = insertNode;
	}
	else
	{
		printf("Search value not found!!");
	}
}

void printBinaryTree(struct biNode *root)
{
	if(root == NULL)
	{
		return;
	}
	printf("\nval: %d , me: %p , left: %p , right: %p , parent: %p",root->val,root,root->left,root->right,root->parent);
	if(root->left != NULL)
	{
		printBinaryTree(root->left);
	}
	if(root->right != NULL)
	{
		printBinaryTree(root->right);
	}
}

void deleteFromBinaryTreeRef(struct biNode **root,struct biNode *temp)
{
	struct biNode **tempRef;
	if(temp == NULL)
	{
		return;
	}

	//hope i don't code like this again my life time
	if(temp->left == NULL && temp->right == NULL)
	{
		if(temp->parent == NULL)
		{
			*root = NULL;
		}
		else if(temp->parent->left == temp)
		{
			temp->parent->left = NULL;
		}
		else
		{
			temp->parent->right = NULL;
		}
	}
	else if(temp->right == NULL)
	{
		if(temp->parent == NULL)
		{
			temp->val = temp->left->val;
			deleteFromBinaryTreeRef(root,temp->left);
			return;
		}
                else if(temp->parent->left == temp)
                {
                        temp->parent->left = temp->left;
			temp->left->parent = temp->parent;
                }
                else
                {
                        temp->parent->right = temp->left;
			temp->right->parent = temp->parent;
                }
	}
	else if(temp->left == NULL)
	{
		if(temp->parent == NULL)
                {
                        temp->val = temp->right->val;
			deleteFromBinaryTreeRef(root,temp);
			return;
                }
                else if(temp->parent->left == temp)
                {
                        temp->parent->left = temp->right;
			temp->left->parent = temp->parent;
                }
                else
                {
                        temp->parent->right = temp->right;
			temp->right->parent = temp->parent;
                }
	}
	else
	{
		//replacing the node with it's in-order predecessor
		struct biNode *tempPred = temp->left;
		while(tempPred->right != NULL)
		{
			tempPred = tempPred->right;
		}
		temp->val = tempPred->val;
		deleteFromBinaryTreeRef(root,tempPred);
		return;
	}
	free(temp);
}

void deleteFromBinaryTree(struct biNode **root,int priVal)
{
        struct biNode *temp = searchInBinaryTree(*root,priVal);
        deleteFromBinaryTreeRef(root,temp);
}
