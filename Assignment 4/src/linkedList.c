
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedList.h"
#include "count.h"

Food * createRecord(char * name, char * group, int calories, char theType)
{
   Food* tempPtr;
   int length;

   tempPtr = malloc(sizeof(Food));

   if (tempPtr == NULL)
   {	
   		free(tempPtr);
   		return NULL;
   }
   
   length = strlen(name);
   
   if (length > 50)
   {
   	   	free(tempPtr);
   		return NULL;
   }
   else
   {
   tempPtr->name = malloc(sizeof(char)*(strlen(name)+1));
   }

   if (tempPtr->name == NULL)
   {
   	   	free(tempPtr);
        return NULL;
   }
   
   tempPtr->foodGroup = malloc(sizeof(char)*(strlen(group)+1));
   
   if (tempPtr->foodGroup == NULL)
   {
   		free(tempPtr);
   		return NULL;
   }

   strcpy(tempPtr->name,name);
   strcpy(tempPtr->foodGroup,group);
   tempPtr->calories = calories;
   tempPtr->type = theType;
   tempPtr->next = NULL;

   return tempPtr;
}

char * printRecord(Food * toPrint)
{
	Food *tempPtr = toPrint;
	char * line = NULL;
	line = malloc(sizeof (char) * 100);

	while(tempPtr != NULL)
	{
		if (toPrint == NULL)
		{
		}
		else
		{
			printf("%s(%s):%d[%c]\n", toPrint->name, toPrint->foodGroup,toPrint->calories,toPrint->type );
			tempPtr = tempPtr->next;
		}
	}
	return line;
}

void destroyRecord(Food * toDie)
{
	free(toDie->name);
	free(toDie->foodGroup);
	return;
}

/*************************/

Food * addToFront(Food * theList, Food * toBeAdded)
{
	Food * tempPtr = toBeAdded;

	if (theList == NULL)
	{
		theList = toBeAdded ;
		return theList;
	}

	tempPtr->next = theList; //pointer of tobeadded->next goes to head of the current list
	theList = toBeAdded; 
	return theList;
}


Food * addToBack(Food * theList, Food * toBeAdded)
{
	Food *tempPtr = theList;

	if (theList == NULL) //if the first item
	{
		theList = addToFront(theList,toBeAdded);
		return theList;
	}

	while (tempPtr->next != NULL) //next is not null then move on until last list
	{
		tempPtr = tempPtr->next;
	}

	tempPtr->next = toBeAdded;
	toBeAdded->next = NULL;
	return theList;
}


Food * removeFromFront(Food * theList)
{
    if (theList != NULL) {
        theList = theList->next;
    }
    return (theList);
}


Food * removeFromBack(Food * theList)
{

     Food * tempPtr;
     Food * newLast;
     newLast = tempPtr = theList;

     
    if (isEmpty(theList))
    {
    	free(tempPtr);
    	free(newLast);
       return NULL;
    }
    while (tempPtr->next != NULL)
    {
        newLast = tempPtr;
        tempPtr = tempPtr->next;
    }

    newLast->next = NULL;
    tempPtr->next = NULL;

    return theList;
}


Food * getLastItem(Food * theList)
{
	Food *lastItem = theList;
	
	if (theList == NULL)
	{
		free(lastItem);
		return NULL;
	}

	while (theList->next != NULL)
	{
		theList = theList->next;
	}

	lastItem->name = theList->name;
	lastItem->foodGroup = theList->foodGroup;
	lastItem->calories = theList->calories;
	lastItem->type = theList->type;
	lastItem->next = NULL;
	return lastItem;

}



Food * getFirstItem(Food * theList)
{
	Food *firstItem = malloc(sizeof(Food));

	if (theList == NULL)
	{
		free(firstItem);
		return NULL;
	}

	firstItem->name = theList->name;
	firstItem->foodGroup = theList->foodGroup;
	firstItem->calories = theList->calories;
	firstItem->type = theList->type;
	firstItem->next = NULL;
	return firstItem;
}

int isEmpty(Food * theList)
{
	if (theList == NULL)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void printList(Food * theList)
{
	while (theList != NULL)
	{
		printf("%s(%s):%d[%c]\n", theList->name, theList->foodGroup,theList->calories,theList->type );
		theList = theList->next;
	}

	return;
}

void destroyList(Food * theList)
{
	free(theList);
	return;
}
