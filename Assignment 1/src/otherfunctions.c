#include <stdio.h>


/*File operation function*/
/*Does the function of whatever the filename provided is*/
FILE * openFile(char* fileName, char* operation)
{
    FILE * f = fopen(fileName, operation);
    return f;
}

/*Reads the file and outputs to the corresponding output*/
void readFile(FILE * input, FILE * output, char * buff)
{

	fprintf(output,"%s",buff);
	return;
}

/*Closes the file to whatever is provided*/
void closeFile (FILE* file)
{
	fclose(file);
	return;
}

/*Variables counter*/
void variables(int countVariables,int changedVariables, int unchangedVariables)
{
	printf("\nThere are %d number of input variables found\n",countVariables);	
	printf("The number of successful variables changed are: %d\n",changedVariables);
	printf("The amount of unchanged variables are: %d\n",unchangedVariables);
	return;
}
