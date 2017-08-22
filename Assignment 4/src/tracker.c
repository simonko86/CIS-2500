#include "linkedList.h"
#include "count.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>



int main(int argc, char **argv)
{
	FILE * file;
	char word[255];
	char * type; //pointer when tokenizing
	int caloriesCount = 0;
	int length = 0;
	Food * item;
	Food * theList;


	int vegCount = 0;
	int meatCount = 0;
	int grainCount = 0;
	int dairyCount = 0;
	int fatCount = 0;
	float vegcaloryCount = 0.00;
	float meatcaloryCount = 0.00;
	float graincaloryCount = 0.00;
	float dairycaloryCount = 0.00;
	float fatcaloryCount = 0.00;

	float averageVegCalory = 0.00;
	float averageMeatCalory = 0.00;
	float averageGrainCalory = 0.00;
	float averageDairyCalory = 0.00;
	float averageFatCalory = 0.00;



	if ((argc > 2) || (argc < 2))
	{
		printf("Incorrect arguments\n");
		return 1;
	}

	file = fopen(argv[1],"r");

		while(	fgets(word, 255, file) != NULL)
		{
			char * name;
			char * foodGroup;
			char * calories;
			char caloryChar;
			int caloryInt; //converted calory to int
				char * printPtr = NULL;

			name = strtok(word, " , ");
			foodGroup = strtok(NULL, " , ");
			calories = strtok(NULL, " , ");
			type = strtok(NULL," , ");
			caloryInt = atoi(calories);
			caloryChar = type[0];

			item = createRecord(name,foodGroup,caloryInt,caloryChar);
			if (caloryChar == 'j')
			{
				theList = addToBack(theList,item);
			}
			else
			{
				theList = addToFront(theList, item);
			}

			if ((foodGroup[0] == 'v') || (foodGroup[0] == 'V'))
			{
				vegCount++;
				vegcaloryCount = vegcaloryCount + caloryInt;
			}
			else if ((foodGroup[0] == 'm') || (foodGroup[0] == 'M'))
			{
				meatCount++;
				meatcaloryCount = meatcaloryCount + caloryInt;
			}
			else if ((foodGroup[0] == 'g') || (foodGroup[0] == 'G'))
			{
				grainCount++;
				graincaloryCount = graincaloryCount + caloryInt;
			}
			else if ((foodGroup[0] == 'd') || (foodGroup[0] == 'D'))
			{
				dairyCount++;
				dairycaloryCount = dairycaloryCount + caloryInt;
			}
			else
			{
				fatCount++;
				fatcaloryCount = fatcaloryCount + caloryInt;
			}
		}

	fclose(file);
	caloriesCount = caloryCount(theList);
	printf("%d\n", caloriesCount);

	averageVegCalory = vegcaloryCount / vegCount;
	averageMeatCalory = meatcaloryCount / meatCount;
	averageGrainCalory = graincaloryCount / grainCount;
	averageDairyCalory = dairycaloryCount / dairyCount;
	averageFatCalory = fatcaloryCount / fatCount;

	printf("%.2f\n", averageVegCalory);
	printf("%.2f\n", averageMeatCalory);
	printf("%.2f\n", averageDairyCalory);
	printf("%.2f\n", averageGrainCalory);
	printf("%.2f\n", averageFatCalory);

	length = countList(theList);
	printf("%d\n", length);
	
	printList(theList);
	destroyRecord(item);
	destroyList(theList);
	return 0;
}

