#include<stdio.h>
struct biNode
{
	int val;
	struct biNode *parent,*left,*right;
};
struct biNode* searchInBinaryTree(struct biNode *root,int secVal);
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

void deleteFromBinaryTree(struct biNode **root,int priVal)
{
	struct biNode *temp = searchInBinaryTree(*root,priVal);
	struct biNode **tempRef;
	if(temp == NULL)
	{
		return;
	}

	tempRef = &temp;

	if(temp->left == NULL)
	{
		*tempRef = (*tempRef)->right;
	}
	else if(temp->right == NULL)
	{
		*tempRef = (*tempRef)->left;	
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
		deleteFromBinaryTree(root,temp->val);
		return;
	}
	free(temp);
}
int main()
{
	int priVal,secVal,choice;
	struct biNode *root = NULL;
	while(1)
	{
		printf("\n1.Insert a number\n2.Search for a number\n3.Delete a number\n4.Print\n5.Exit:");
		scanf(" %d",&choice);
		switch(choice)
		{
			case 1: printf("\nEnter the number: ");
				scanf(" %d",&priVal);
				printf("\nEnter the search value: ");
				scanf(" %d",&secVal);
				insertToBinaryTree(&root,priVal,secVal);
				break;
			case 2: printf("\nEnter the number: ");
				scanf(" %d",&priVal);
				if(searchInBinaryTree(root,priVal) == NULL)
				{
					printf("\nMiss\n");
				}
				else
				{
					printf("\nHIT\n");
				}
				break;
			case 3: printf("\nEnter the number: ");
				scanf(" %d",&priVal);
				deleteFromBinaryTree(&root,priVal);
				break;
			case 4: printBinaryTree(root);
				break;
			case 5: printf("Good bye..\n\n");
				return;
			default:printf("\nEnter a proper value!!\n");
		}
	}
}
