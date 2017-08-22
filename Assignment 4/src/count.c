#include "count.h"
#include "linkedList.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int countList(Food* theList)
{
	int count = 0;
	Food *tempPtr = theList;

	if (theList != NULL)
	{
		while(tempPtr->next != NULL)
		{
			tempPtr = tempPtr->next;
			count++;
		}
		count++;
	}

	return count;
}

int caloryCount(Food* theList)
{
	int count = 0;
	int caloryCount = 0;
	Food *tempPtr = theList;

	caloryCount = tempPtr->calories;
	count = caloryCount + count;	

	while(tempPtr->next != NULL)
	{
		tempPtr = tempPtr->next;
		caloryCount = tempPtr->calories;
		count = caloryCount + count;
	}
	return count;
}