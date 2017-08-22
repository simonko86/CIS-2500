
#ifndef __SKO01_PARSE__ //Header guards incase header is already read
#define __SKO01_PARSE__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ncurses.h>


/*
*openFile
*Takes a pointer to the filename and does the operation
* IN: fileName, operation. fileName is 
* the name pointing to the file, operation
* is what needs to be done
* OUT: f. f is the pointer back to the filename.
* POST: none
* ERROR: none
*/
FILE * openFile(char* fileName, char* operation);

/*
*initCurses
*Sets up ncurses
* IN: none
* OUT: none
* POST: none
* ERROR: none
*/
void initCurses(void);

/*
*parseFile
*Reads data file and parses the information
*into the structs.
* IN: fileName, rooms. fileName is the pointer to 
* the text file, rooms is the dynamically allocated
* struct array
* OUT: rooms. rooms points back to the struct array.
* POST: none
* ERROR: none
*/
struct Room * parseFile(FILE* fileName, struct Room *rooms);

/*
*closeFile
*Closes the file that fileName is pointing to
* IN: Pointer to fileName
* OUT: none
* POST: none
* ERROR: none
*/
void closeFile(FILE* fileName);

#endif
/* defined __SKO01_PARSE__ */
