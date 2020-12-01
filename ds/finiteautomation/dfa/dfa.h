#include<stdio.h>
#include<stdlib.h>

#define boolean int
#define true 1
#define false 0

int** getDFAObj(char *source,int length)
{
	int** dfaObj = calloc(sizeof(int*),26),itr1,itr2,itr3,c;

	for(itr1 = 0; itr1 < 26; ++itr1)
	{
		*(dfaObj + itr1) = calloc(sizeof(int),length);
	}

	for(itr2 = 0, itr1 = 0; itr2 < length; ++itr2)
	{
		c = *(source + itr2) - 'a';
		for(itr3 = 0; itr3 < 26; ++itr3)
		{
				*( *(dfaObj + itr3) + itr2) = *( *(dfaObj + itr3) + itr1);
		}
		itr1 = *(*(dfaObj + c) + itr1);
		*(*(dfaObj + c) + itr2) = itr2 + 1;
	}

	return dfaObj;
}

boolean searchUsingDFA(int **dfaObj,char *search,int length)
{
	int itr1,itr2,c;

	for(itr1 = 0, itr2 = 0; *(search + itr1) != '\0'; ++itr1)
	{
		c = *(search + itr1) - 'a';
		itr2 = *(*(dfaObj + c) + itr2);
		if(itr2 == length)
		{
			return true;
		}
	}

	return false;
}