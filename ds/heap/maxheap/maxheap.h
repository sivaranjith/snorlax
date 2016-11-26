#include<stdio.h>
#include<stdlib.h>

#define boolean int
#define true 1
#define false 0

struct maxHeap
{
	int nextInsertionPoint;
	struct maxHeapNode
	{
		int val;
		struct maxHeapNode *left,*right;
	}*head;
};

struct maxHeap* createMaxHeap()
{
	struct maxHeap *maxHeapObj = calloc(sizeof(struct maxHeap),1);
	maxHeapObj->nextInsertionPoint = 1;
}

struct maxHeapNode* maxHeapInsertor(struct maxHeapNode *head,struct maxHeapNode *newNode,int position)
{
	int swapVal;

	if(position == 1)
	{
		if(head == NULL)
		{
			return newNode;
		}
		return head;
	}

	struct maxHeapNode *temp = maxHeapInsertor(head,newNode,position>>1);
	if(newNode->val > temp->val)
	{

		swapVal = newNode->val;
		newNode->val = temp->val;
		temp->val = swapVal;
	}

	if(position&1)
	{
		if(temp->right == NULL)
		{
			temp->right = newNode;
		}
		return temp->right;
	}
	else
	{
		if(temp->left == NULL)
		{
			temp->left = newNode;
		}
		return temp->left;
	}
}

void insertToMaxHeap(struct maxHeap *maxHeapObj,int priVal)
{
	struct maxHeapNode *temp,*newNode =calloc(sizeof(struct maxHeapNode),1);
	newNode->val = priVal;
	temp = maxHeapInsertor(maxHeapObj->head,newNode,maxHeapObj->nextInsertionPoint);
	if(maxHeapObj->head == NULL)
	{
		maxHeapObj->head = temp;
	}
	++(maxHeapObj->nextInsertionPoint);
}

struct maxHeapNode* getLastInsertedNodeParent(struct maxHeapNode *head,int position)
{
	if(position == 1)
	{
		return head;
	}

	struct maxHeapNode *temp = getLastInsertedNodeParent(head,position>>1);
	
	if(position&1)
	{
		return temp->right;
	}
	else
	{
		return temp->left;
	}
}

void orderMaxHeap(struct maxHeapNode *head)
{
	if(head == NULL)
	{
		return;
	}

	int swapVal;

	if(head->right != NULL)
	{
		if(head->left->val >= head->right->val && head->left->val > head->val)
		{
			swapVal = head->left->val;
			head->left->val = head->val;
			head->val = swapVal;
			orderMaxHeap(head->left);
		}
		else if(head->right->val >= head->left->val && head->right->val > head->val)
		{
			swapVal = head->right->val;
			head->right->val = head->val;
			head->val = swapVal;
			orderMaxHeap(head->right);
		}
	}
	else if(head->left != NULL && head->left->val > head->val)
	{
		swapVal = head->left->val;
		head->left->val = head->val;
		head->val = swapVal;
		orderMaxHeap(head->left);
	}
}

int deleteFromMaxHeap(struct maxHeap *maxHeapObj)
{
	if(maxHeapObj == NULL || maxHeapObj->head == NULL)
	{
		return -1;
	}
	int returnVal;
	struct maxHeapNode *lastInsertedNodeParent;
	
	--(maxHeapObj->nextInsertionPoint);
	
	returnVal = maxHeapObj->head->val;
	
	if(maxHeapObj->nextInsertionPoint == 1)
	{
		free(maxHeapObj->head);
		maxHeapObj->head = NULL;
		return returnVal;
	}

	lastInsertedNodeParent = getLastInsertedNodeParent(maxHeapObj->head,(maxHeapObj->nextInsertionPoint)>>1);

	if((maxHeapObj->nextInsertionPoint)&1)
	{
		maxHeapObj->head->val = lastInsertedNodeParent->right->val;
		free(lastInsertedNodeParent->right);
		lastInsertedNodeParent->right = NULL;
	}
	else
	{
		maxHeapObj->head->val = lastInsertedNodeParent->left->val;
		free(lastInsertedNodeParent->left);
		lastInsertedNodeParent->left = NULL;
	}

	orderMaxHeap(maxHeapObj->head);

	return returnVal;
}

void maxHeapPrinter(struct maxHeapNode *head)
{
	if(head == NULL)
	{
		return;
	}

	printf("%d\n",head->val);

	maxHeapPrinter(head->left);
	maxHeapPrinter(head->right);
}

void printMaxHeap(struct maxHeap *maxHeapObj)
{
	maxHeapPrinter(maxHeapObj->head);
}

boolean maxHeapSearcher(struct maxHeapNode *head,int priVal)
{
	if(head == NULL)
	{
		return false;
	}
	else if(head->val == priVal)
	{
		return true;
	}

	if(head->left != NULL && head->left->val >= priVal)
	{
		if(maxHeapSearcher(head->left,priVal))
		{
			return true;
		}
	}

	if(head->right != NULL && head->right->val >= priVal)
	{
		return maxHeapSearcher(head->right,priVal);
	}

	return false;
}

boolean searchMaxHeap(struct maxHeap *maxHeapObj,int priVal)
{
	if(maxHeapObj == NULL || maxHeapObj->head == NULL)
	{
		return false;
	}

	return maxHeapSearcher(maxHeapObj->head,priVal);
}

int getMaxValueFromMaxHeap(struct maxHeap* maxHeapObj)
{
	if(maxHeapObj == NULL || maxHeapObj->head == NULL)
	{
		return 0;
	}
	return maxHeapObj->head->val;
}