#include "linkedList.h"
#include <stdio.h>
#include <stdlib.h>


int main()
{
	Food *theList = NULL;
	char *printPtr;
	theList = NULL;
	Food *icecream;
	Food *chips;
	Food *milk;
	int emptyList;
	Food *lastItem = NULL;
	
	emptyList = isEmpty(theList);
	if (emptyList == 1)
	{
		//printf("Yes, list is empty\n");
	}
	else
	{
		//printf("No, not empty\n");
	}

	icecream = createRecord("Ice Cream", "dairy", 141,'j');
	theList = addToFront(theList, icecream);
	emptyList = isEmpty(theList);
	if (emptyList == 1)
	{
		//printf("Yes, list is empty\n");
	}
	else
	{
		//printf("No, not empty\n");
	}

	chips = createRecord("Chips", "potatoe", 200, 'j');
	milk = createRecord("Milk", "dairy", 200, 'j');

	printPtr = (printRecord(icecream));
	if (printPtr == NULL)
	{
		//printf("error\n");
	}
	//printf("Prints a record of icecream\n");


	theList = NULL;
	theList = addToFront(theList, icecream);
	theList = addToFront(theList, chips);
	theList = addToFront(theList, milk);
	printList(theList);
	//printf("Should print in milk, chips, icecream ^\n");

	theList = getFirstItem(theList);
	printPtr = (printRecord(theList));
	//printf("Should print first item in list^\n");

	lastItem = getLastItem(theList);
	printPtr = (printRecord(lastItem));
	//printf("Should print last item in list^\n");

	theList = NULL;
	theList = addToFront(theList, icecream);
	theList = addToFront(theList, chips);
	theList = addToFront(theList, milk);
	printList(theList);
	//printf("Should print in milk, chips, icecream ^\n");

	theList = removeFromFront(theList);
	printList(theList);
	//printf("Should remove the front of the list\n");
	theList = removeFromBack(theList);
	printList(theList);
	//printf("Should remove the back of the list\n");


	destroyList(theList);






	return 0;
}