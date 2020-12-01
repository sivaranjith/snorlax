#include<stdio.h>
struct node
{
	int val;
	struct node *next;
};
void insertAtBegining(struct node **head, int priVal)
{
	struct node *temp = (struct node*)malloc(sizeof(struct node));
	temp->val = priVal;
	temp->next = *head;
	*head = temp;
}
void insertAtEnd(struct node **head, int priVal)
{
	struct node *temp = (struct node*)malloc(sizeof(struct node));
	temp->val = priVal;
	temp->next = NULL;
	if(*head == NULL)
	{
		*head = temp;
	}
	else
	{
		struct node *itr = *head;
		while(itr->next != NULL)
		{
			itr = itr->next;
		}
		itr->next = temp;
	}
}
void insertAtIndex(struct node **head, int priVal, int secVal)
{
	struct node *temp = (struct node*)malloc(sizeof(struct node));
	temp->val = priVal;
	if(*head == NULL || secVal == 0)
	{
		temp->next = *head;
		*head = temp;
	}
	else
	{
		struct node *itr = *head;
		while(itr->next != NULL && --secVal != 0)
		{
			itr = itr->next;
		}
		temp->next = itr->next;
		itr->next = temp;
	}
}
void insertAfter(struct node **head, int priVal, int secVal)
{
	struct node *temp = (struct node*)malloc(sizeof(struct node));
	temp->val = priVal;
	if(*head == NULL || secVal == 0)
	{
		temp->next = *head;
		*head = temp;
	}
	else
	{
		struct node* itr = *head;
		while(itr-> next != NULL && itr->val != secVal)
		{
			itr = itr->next;
		}
		temp->next = itr->next;
		itr->next = temp;
	}
}
void insertBefore(struct node **head,int priVal,int secVal)
{
	struct node *temp = (struct node*)malloc(sizeof(struct node));
	temp->val = priVal;
	if(*head == NULL || (*head)->val == secVal)
	{
		temp->next = *head;
		*head = temp;
	}
	else
	{
		struct node *itr = *head;
		while(itr->next != NULL && itr->next->val != secVal)
		{
			itr = itr->next;
		}
		temp->next = itr->next;
		itr->next = temp;
	}
}
int deleteVal(struct node **itr,int priVal)
{
	struct node *freePt;
	while(*itr != NULL && (*itr)->val != priVal)
	{
		itr = &(*itr)->next;
	}
	if(*itr != NULL)
	{
		freePt = *itr;
		*itr = (*itr)->next;
		free(freePt);
		return priVal;
	}
	return 0;
}
int deleteFirstVal(struct node **head)
{
	struct node *freePt;
	int val = 0;
	if(*head != NULL)
	{
		freePt = *head;
		*head = (*head)->next;
		val = freePt->val;
		free(freePt);
	}
	return val;
}
int deleteLastVal(struct node **itr)
{
	struct node *freePt;
	int val = 0;
	if(*itr == NULL)
	{
		return 0;
	}
	while((*itr)->next != NULL)
	{
		itr = &(*itr)->next;
	}
	freePt = *itr;
	*itr = (*itr)->next;
	val = freePt->val;
	free(freePt);
	return val;
}
int deletePreVal(struct node **itr,int priVal)
{
	struct node **itrSlow = itr, *freePt;
	int val = 0;
	if(*itr == NULL || (*itr)->val == priVal)
	{
		return 0;
	}
	itr = &(*itr)->next;
	while(*itr != NULL && (*itr)->val != priVal)
	{
		itrSlow = itr;
		itr = &(*itr)->next;
	}
	if(*itr != NULL && (*itr)->val == priVal)
	{
		freePt = *itrSlow;
		*itrSlow = (*itrSlow)->next;
		val = freePt->val;
		free(freePt);
	}
	return val;
}
int deleteAfterVal(struct node **itr,int priVal)
{
	struct node *freePt;
	int val = 0;
	while(*itr != NULL && (*itr)->val != priVal)
	{
		itr = &(*itr)->next;
	}
	if(*itr != NULL && (*itr)->next != NULL)
	{
		itr = &(*itr)->next;
		freePt = *itr;
		*itr = (*itr)->next;
		val = freePt->val;
		free(freePt);
	}
	return val;
}
int valueAt(struct node *itr,int priVal)
{
	int returnVal = 0;
	while(itr != NULL &&  --priVal > 0)
	{
		itr = itr->next;
	}
	if(itr != NULL && priVal == 0)
	{
		returnVal = itr->val;
	}
	return returnVal;
}
int lastValue(struct node *itr)
{
	if(itr == NULL)
	{
		return 0;
	}
	while(itr->next != NULL)
	{
		itr = itr->next;
	}
	return itr->val;
}
void printAll(struct node *head)
{
	while(head != NULL)
	{
		printf("%d  ",head->val);
		head = head->next;
	}
}
