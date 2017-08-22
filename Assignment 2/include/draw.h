
#ifndef __SKO01_DRAW__ //Header guards incase header is already read
#define __SKO01_DRAW__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ncurses.h>


/*
*maxRowsTop
*Caclulates the longest row of the 3 rooms
*Used for calculating minimum window size
* IN: struct rooms
* OUT: Length of the longest row from rooms 1-3
* POST: none
* ERROR: none
*/
int maxRowsTop(struct Room * rooms);

/*
*maxRowsBottom
*Caclulates the longest row of the 3 rooms
*Used for calculating minimum window size
* IN: struct rooms.
* OUT: Length of the longest row from rooms 4-6
* POST: none
* ERROR: none
*/
int maxRowsBottom(struct Room * rooms);


/*
*drawFloors
*Takes in struct dimensions and builds the floors
* IN: maxRows, rooms. rooms is the struct array, while
* maxRows is the maximum rows from rooms 1-3. Designed to
* place rooms 4-6
* OUT: none
* POST: none
* ERROR: none
*/
void drawFloors(int maxRows, struct Room *rooms);

/*
*drawRooms
*Takes in struct dimensions and builds the walls and parts
* IN: maxRows, rooms. rooms is the struct array, while
* maxRows is the maximum rows from rooms 1-3. Designed to
* place rooms 4-6
* OUT: none
* POST: none
* ERROR: none
*/
void drawRoom(int maxRows, struct Room *rooms);

#endif
/* defined __SKO01_DRAW__ */
