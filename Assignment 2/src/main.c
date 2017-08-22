#include "rogueGame.h"
#include "parse.h"
#include "draw.h"

/*
*main
* Game to play Rogue. Avoid monsters. Pick up weapons
* and gold.
* Calls functions to play the game.
* Also does error checking, making sure enough arguments
* to play the game, making sure there is a correct data
* file. Also checks window size is correct
* IN: argc,argv
* OUT: Returns 0 when game is correct
* POST: none
* ERROR: none
*/

int main (int argc, char **argv)
{
    struct Room *rooms;// = {0}; //initialize with 0
    rooms = malloc(sizeof(struct Room)*7); //create a pointer to rooms of size array of 7 structs (from 0-6)
    FILE* input;    //file pointer called input
    int maxx,maxy; 
    int maximumRowsTop, maximumRowsBottom; //calculated minimum screensize
    int maximumRows;

    if (argc != 2)
    {   
        free(rooms);   //freeMalloc
		printf("Incorrect arguments\n");
		return 1;
    }
    
	input = openFile(argv[1],"r"); //input points to argv[1]
    
	if (input == NULL)
    {
        free(rooms);   //freeMalloc
		printf("File not found\n");
		return 1;
    }

    initCurses();
    parseFile(input,rooms); //parse file pointer into struct arrays

    getmaxyx(stdscr,maxy,maxx); //screen size check to make sure the game can be played
    maximumRowsTop = maxRowsTop(rooms);
    maximumRowsBottom = maxRowsBottom(rooms);
    maximumRows = maximumRowsBottom + maximumRowsTop;
    if ((maxx < rooms[1].columns + rooms[2].columns + rooms[3].columns + 11) || (maxy < maximumRows + 6))
    {
		free(rooms);
        endwin();
        printf("Screen size too small\n");
        return 1;       
    }

    drawFloors(maximumRowsTop,rooms);  //draw floors with '.'
    drawRoom(maximumRowsTop,rooms);    //draw rooms using structs
    closeFile(input);    //close file
    playGame(maximumRowsTop,rooms);    //play the game
    free(rooms);   //freeMalloc
    return 0;
}
