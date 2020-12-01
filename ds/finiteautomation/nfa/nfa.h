#include<stdio.h>
#include<stdlib.h>

#define boolean int
#define true 1
#define false 0

struct nfaList
{
	int val;
	struct nfaList *next;
};

struct nfaNode
{
	int** nfaDataObj;
	struct nfaList **epsilonList;
};

void insertAtBegining(struct nfaList **head, int priVal)
{
	struct nfaList *temp = (struct nfaList*)malloc(sizeof(struct nfaList));
	temp->val = priVal;
	temp->next = *head;
	*head = temp;
}

void insertAtEnd(struct nfaList **head, int priVal)
{
	struct nfaList *temp = (struct nfaList*)malloc(sizeof(struct nfaList));
	temp->val = priVal;
	temp->next = NULL;
	if(*head == NULL)
	{
		*head = temp;
	}
	else
	{
		struct nfaList *itr = *head;
		while(itr->next != NULL)
		{
			itr = itr->next;
		}
		itr->next = temp;
	}
}

int deleteFirstVal(struct nfaList **head)
{
	struct nfaList *freePt;
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

int deleteVal(struct nfaList **itr,int priVal)
{
	struct nfaList *freePt;
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

int charValue(char c)
{
	if(c >= 'a' && c <= 'z')
	{
		return c - 'a';
	}
	else if(c >= '0' && c<= '9')
	{
		return c - '0' + 26;
	}
	else if(c == '(')
	{
		return 36;
	}
	else if(c == ')')
	{
		return 37;
	}
	else if(c == '*')
	{
		return 38;
	}
	else if(c == '+')
	{
		return 39;
	}
	else if(c == '|')
	{
		return 40;
	}
	else if(c == '.')
	{
		return 41;
	}
}

int setEpsilonValuesForClosingBrackets(struct nfaList **bracesStack,struct nfaList **epsilonList,char *source,int closeBracketIndex)
{
	int stackElementIndex = deleteFirstVal(bracesStack),lastOpenParanthesisIndex;
	
	if(*(source + stackElementIndex) == '(')
	{
		return stackElementIndex;
	}

	lastOpenParanthesisIndex = setEpsilonValuesForClosingBrackets(bracesStack,epsilonList,source,closeBracketIndex);

	insertAtBegining((epsilonList + lastOpenParanthesisIndex),stackElementIndex + 1);
	insertAtBegining((epsilonList + stackElementIndex),closeBracketIndex);

	return lastOpenParanthesisIndex;
}

struct nfaNode* getNFAObj(char *source,int length)
{
	int **nfaObj = calloc(sizeof(int*),66),itr1,itr2,lastOpenParanthesisIndex;
	struct nfaList **epsilonList = calloc(sizeof(struct nfaList*),length),*bracesStack = NULL,*tempTraverser;
	struct nfaNode *nfaNodeObj = calloc(sizeof(struct nfaNode),1);
	char c;

	for(itr1 = 0; itr1 < 66; ++itr1)
	{
		*(nfaObj + itr1) = calloc(sizeof(int),length);
		for(itr2 = 0; itr2 < length; ++itr2)
		{
			*(*(nfaObj + itr1) + itr2) = -1;
		}
	}

	for(itr1 = 0; *(source + itr1) != '\0'; ++itr1)
	{
		c = *(source + itr1);
		if(c == '(' || c == '|')
		{
			insertAtBegining(&bracesStack,itr1);
			if(c == '(')
			{
				lastOpenParanthesisIndex = itr1;
				if(*(source + itr1 + 1) != '\0')
				{
					insertAtBegining((epsilonList + itr1),itr1 + 1);
				}
			}
		}
		else if(c == '*' || c == '+')
		{
			if(*(source + itr1 + 1) != '\0')
			{
				insertAtBegining((epsilonList + itr1),itr1 + 1);
			}

			if(*(source + itr1 - 1) == ')')
			{
				insertAtBegining((epsilonList + itr1),lastOpenParanthesisIndex);
				if(c == '*')
				{
					insertAtBegining((epsilonList + lastOpenParanthesisIndex),itr1);
				}
			}
			else
			{
				insertAtBegining((epsilonList + itr1),itr1 - 1);
				if(c == '*')
				{
					insertAtBegining((epsilonList + itr1 - 1),itr1);
				}
			}
		}
		else if(c == ')')
		{
			if(*(source + itr1 + 1) != '\0')
			{
				insertAtBegining((epsilonList + itr1),itr1 + 1);
			}

			lastOpenParanthesisIndex = setEpsilonValuesForClosingBrackets(&bracesStack,epsilonList,source,itr1);
		}
		else if(*(source + itr1 + 1) != '\0')
		{
			*(*(nfaObj + charValue(c)) + itr1) = itr1 + 1;
		}
	}

	nfaNodeObj->nfaDataObj = nfaObj;
	nfaNodeObj->epsilonList = epsilonList;
	return nfaNodeObj;
}

void getAllEpsilonTransition(struct nfaList **epsilonList,struct nfaList **queueRef)
{
	struct nfaList *temp1 = *queueRef,*temp2,*temp3;
	int queueVal,epislonVal;
	while(temp1 != NULL)
	{
		queueVal = temp1->val;

		temp2 = *(epsilonList + queueVal);
		while(temp2 != NULL)
		{
			epislonVal = temp2->val;
			temp3 = *queueRef;
			while(temp3 != NULL)
			{
				if(temp3->val == epislonVal)
				{
					break;
				}
				temp3 = temp3->next;
			}

			if(temp3 == NULL)
			{
				insertAtEnd(queueRef,epislonVal);
			}
			temp2 = temp2->next;
		}

		temp1 = temp1->next;
	}
}

struct nfaList* getAllCorrectState(int** nfaDataObj,struct nfaList **queueRef,char c)
{
	struct nfaList *temp1 = *queueRef,*temp2,*temp3;
	int queueVal,dataVal;
	while(temp1 != NULL)
	{
		queueVal = temp1->val;
		dataVal = *(*(nfaDataObj + charValue(c)) + queueVal);
		temp1 = temp1->next;
		if(dataVal == -1)
		{
			deleteVal(queueRef,queueVal);
		}
		else
		{
			insertAtBegining(&temp3,dataVal);
		}
	}
	return temp3;
}

boolean searchUsingNFA(struct nfaNode *nfaNodeObj,char *searchString,int regexLength)
{
	int itr1,length = 0;

	struct nfaList *queue,*temp1;
	insertAtBegining(&queue,0);

	for(; searchString[length] != '\0'; ++length);

	for(itr1 = 0; itr1 < length && queue != NULL; ++itr1)
	{
		getAllEpsilonTransition(nfaNodeObj->epsilonList,&queue);
		queue = getAllCorrectState(nfaNodeObj->nfaDataObj,&queue,*(searchString + itr1));
	}

	getAllEpsilonTransition(nfaNodeObj->epsilonList,&queue);

	while(queue != NULL)
	{
		if(queue->val == regexLength - 1)
		{
			return true;
		}
		queue = queue->next;
	}
	return false;
}