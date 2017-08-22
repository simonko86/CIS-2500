
#ifndef __SKO01_OTHERFUNCTIONS__ //Header guards incase header is already read
#define __SKO01_OTHERFUNCTIONS__

/**
 * 
 *Function name:
 *Short description 
 * 
 *IN:
 *OUT:
 *POST: Side effects of being run
 *ERROR: Error cases if any 
 *  
 */

FILE *openFile(char* fileName, char* operation);


void readFile(FILE* input, FILE* output, char* buff);

void closeFile (FILE* file);

void variables(int countVariables,int changedVariables, int unchangedVariables);

#endif
/* defined __SKO01_OTHERFUNCTIONS__ */
