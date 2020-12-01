#include<stdio.h>
#include<stdlib.h>

#define boolean int
#define true 1
#define false 0

#define initial_size 4


struct minHeap
{
	int nextInsertionPoint,length,*values;
};

struct minHeap* createMinHeap()
{
	struct minHeap* minHeapObj = calloc(sizeof(struct minHeap),1);
	minHeapObj->values = calloc(sizeof(int),initial_size);
	minHeapObj->length = initial_size;
	return minHeapObj;
}

void reAllocateMemory(struct minHeap *minHeapObj,float changeSize)
{
	int *newValues = calloc(sizeof(int),minHeapObj->length * changeSize),*freePt,itr;

	for(itr = 0; itr < minHeapObj->nextInsertionPoint; ++itr)
	{
		*(newValues + itr) = minHeapObj->values[itr];
	}

	freePt = minHeapObj->values;
	minHeapObj->values = newValues;
	minHeapObj->length *= changeSize;

	free(freePt);
}

void insertToMinHeap(struct minHeap *minHeapObj,int priVal)
{
	int position = minHeapObj->nextInsertionPoint,swapVal;
	minHeapObj->values[minHeapObj->nextInsertionPoint++] = priVal;

	while(position != 0)
	{
		if(minHeapObj->values[position] < minHeapObj->values[position>>1])
		{
			swapVal = minHeapObj->values[position];
			minHeapObj->values[position] = minHeapObj->values[position>>1];
			minHeapObj->values[position>>1] = swapVal;
		}
		position >>= 1;
	}

	if( ((float)minHeapObj->length)*0.75 <= minHeapObj->nextInsertionPoint)
	{
		reAllocateMemory(minHeapObj,1.5);
	}
}

int deleteFromMinHeap(struct minHeap *minHeapObj)
{
	int returnVal = minHeapObj->values[0],position = 0,temp,swapVal;
	minHeapObj->values[0] = minHeapObj->values[--minHeapObj->nextInsertionPoint];
	minHeapObj->values[minHeapObj->nextInsertionPoint] = 0;

	while(position < minHeapObj->nextInsertionPoint)
	{
		temp = position*2;
		if(temp + 1 < minHeapObj->nextInsertionPoint)
		{
			if(minHeapObj->values[temp] <= minHeapObj->values[temp+1] && minHeapObj->values[temp] < minHeapObj->values[position])
			{
				swapVal = minHeapObj->values[temp];
				minHeapObj->values[temp] = minHeapObj->values[position];
				minHeapObj->values[position] = swapVal;
				position = temp;
			}
			else if(minHeapObj->values[temp+1] <= minHeapObj->values[temp] && minHeapObj->values[temp+1] < minHeapObj->values[position])
			{
				swapVal = minHeapObj->values[temp + 1];
				minHeapObj->values[temp + 1] = minHeapObj->values[position];
				minHeapObj->values[position] = swapVal;
				position = temp + 1;
			}
		}
		else if(temp < minHeapObj->nextInsertionPoint && minHeapObj->values[temp] < minHeapObj->values[position])
		{
			swapVal = minHeapObj->values[temp];
			minHeapObj->values[temp] = minHeapObj->values[position];
			minHeapObj->values[position] = swapVal;
			position = temp;
		}
		else
		{
			break;
		}
	}

	if(minHeapObj->length != initial_size && ((float)minHeapObj->length)*0.5 > minHeapObj->nextInsertionPoint)
	{
		reAllocateMemory(minHeapObj,0.75);
	}

	return returnVal;
}

boolean minHeapSearcher(struct minHeap *minHeapObj,int priVal,int index)
{
	if(index >= minHeapObj->nextInsertionPoint)
	{
		return false;
	}
	else if(minHeapObj->values[index] == priVal)
	{
		return true;
	}

	if(minHeapSearcher(minHeapObj,priVal,index*2))
	{
		return true;
	}

	return minHeapSearcher(minHeapObj,priVal,index*2 + 1);
}

boolean searchMinHeap(struct minHeap *minHeapObj,int priVal)
{
	return minHeapSearcher(minHeapObj,priVal,0);
}

void printMinHeap(struct minHeap *minHeapObj)
{
	int itr;
	for(itr = 0; itr < minHeapObj->nextInsertionPoint; ++itr)
	{
		printf("%d\n",minHeapObj->values[itr]);
	}
}

int getMinValueFromMinHeap(struct minHeap *minHeapObj)
{
	return minHeapObj->values[0];
}