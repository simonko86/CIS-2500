
#ifndef __SKO01_ROGUEGAME__ //Header guards incase header is already read
#define __SKO01_ROGUEGAME__

/*This struct contains all the information, and arrays for multiple items
 * It is relevant because it helps store information about each room
 */
struct Room
{
    int rows;
    int columns;
    int doorNorth;
    int doorEast;
    int doorWest;
    int doorSouth;
    int gold[10][2];
    int goldBig[2];
    int hero[2];
    int stairsDown[10][2];
    int stairsUp[10][2];
    int weapon[10][2];
    int weaponRare[2];
    int equipment[10][2];
    int potion[10][2];
    int monster[10][2];
    int monsterBig[2];
    int randomShit[2];
};

/*
*playGame
* Plays game, avoids monsters, picks up weapons
* IN: rooms, maxRows. Uses the information from the 
* structs to avoid monsters
* OUT: none
* POST: none
* ERROR: none
*/
void playGame(int maxRows, struct Room *rooms);

/*
*randNumer
* Takes in a number to create a randomly assigned
* number using time.h and srand.
* IN: min. Upper limit of random number.
* OUT: 
* POST: none
* ERROR: none
*/
int randNumber(int min);

/*
*yTeleport
* Finds out the rooms the cursor is in, and the
* yPosition to a door in the next room.
* IN: maxRows, rooms, floor.
* OUT: yPos
* POST: none
* ERROR: none
*/
int yTeleport(int maxRows, int floor, struct Room *rooms);

/*
*xTeleport
*Finds out the rooms the cursor is in, and the
*xPosition to a door in the next room.
* IN: maxRows, rooms, floor.
* OUT: xPos
* POST: none
* ERROR: none
*/
int xTeleport(int floor, struct Room *rooms);

#endif
/* defined __SKO01_ROGUEGAME__ */
