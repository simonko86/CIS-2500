/*compile with gcc src/a1.c src/storeval.c src/otherfunctions.c -Wall -std=c99 -Iinclude */
/*run with ./a.out assets/template assets/data assets/output */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include  "storeval.h"
#include "otherfunctions.h"

int main (int argc, char **argv)
{

	char* tokenPtr;
	char word[255];
	char* first_part;
	char* second_part;
	char* printed_switch;
	int countVariables = 0;
	int changedVariables = 0;
	int unchangedVariables = 0;
	char dataKey[10][26];
	int i,j = 0;
	int checker=0;
	int length;
	int secondPartlength;
	

	
    if (argc < 3 || argc > 4)
    {
    printf("Incorrect number of arguments\n");
    return(1);
    }
    FILE * in = openFile(argv[1], "r");   
    /*read the template file*/
    if (in == NULL)
    {
		printf("File could not be found\n");
		return(1);
	}
    
    FILE * change = openFile(argv[2], "r");
    /*read the data text file*/
    if (change == NULL)
    {
		printf("File could not be found\n");
		return(1);
	}
	     
    
    while(!feof(change)) //while not end of file
    {
		while(fgets(word, 255, change) != NULL) //read a line
		{
			first_part = strtok(word, "="); //tokennize at =
			strcpy (dataKey[countVariables],first_part);
			second_part = strtok(NULL, "=");//tokennize at end of line
			secondPartlength = strlen(second_part);
			if (secondPartlength == 1)
			{
			printf("Variable not included with key\n");
			printf("Please check data file\n");
			return(1);
			}
			
			setValue(first_part,second_part);//use setValue here
			countVariables++; //counter for variables
		}
	}
	
	closeFile(change); //close data file

    FILE * out = openFile(argv[3], "w");
        if (out == NULL)
    	{
		printf("File could not be written");
		return(1);
	}


    while(!feof(in)) //while not end of file
    {
		while(fgets(word, 255, in) != NULL) //read a line from template file
		{
			tokenPtr = strtok(word, "{}"); //tokenize between curly brackets
			
			while(tokenPtr != NULL)
			{
				for(i=0;i<=countVariables;i++)
					{
						if(strcmp(tokenPtr,dataKey[i]) == 0) //if token matches the key, then switch
						{
							printed_switch = getValue(tokenPtr);	//remove null terminals
							length = strlen(printed_switch);
							length--;

							for(j=0;j<length;j++)
							{
								printf("%c",printed_switch[j]);
								fprintf(out,"%c",printed_switch[j]);
							}
				//readFile(in,out, printed_switch);
							changedVariables++;
							checker = 1;						
						}
	
					}	
				if (checker == 1)
				{
					checker = 0; //this prevents both the key and other word from being printed
				}
				else
				{
					printf("%s",tokenPtr);
					readFile(in,out,tokenPtr);	
				}
				tokenPtr = strtok(NULL, "{}");		
			}
		}
	}
	
	variables(countVariables, changedVariables, unchangedVariables);	//calculate variables;
	
	printf("Execution sucessful!\n");
  
	closeFile(out);
	closeFile(in);

    return 0;
}
