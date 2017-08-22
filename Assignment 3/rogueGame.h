
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
    int gold[11][3];
    int goldBig[3];
    int hero[3];
    int stairsDown[11][3];
    int stairsUp[11][3];
    int weapon[11][3];
    int weaponRare[3];
    int equipment[11][3];
    int potion[11][3];
    int monster[11][4];
    int monsterBig[4];
    int randomShit[2];
};

/*
* This struct contains all information about the hero
* Used for combat and displaying the information
*/
struct Items
{
    int health;
    int potion;
    int inventory;
    int attack;
    int defence;
};

/* This struct is used to contain all
* enemy information for speed, attack and defence
*/
struct Enemies
{
    int aquator[3];
    int bat[3];
    int snake[3];
    int zombie[3];
    int troll[3];
};

/*
*combat
* Combat between hero and monster
* IN: char what the enemy is attacking, struct Items, struct rooms, struct enemies, int maximumRows, int yPos, int xPos, int maxRows
* OUT: int deadEnemy: if the enemy is dead
* POST: none
* ERROR: none
*/
int combat(char position, struct Items *items, struct Room *rooms, struct Enemies *enemies, int maximumRows, int yPos, int xPos, int maxRows);

/*
* patrol
* Depending on the cycle between 1-4,
* patrols each monster by moving the struct
* Also avoids any items
* Plays game, avoids monsters, picks up weapons
* IN: struct rooms, int cycle, int maximumRows, int maxRows
* OUT: none
* POST: none
* ERROR: none
*/
void patrol(int maximumRows, int maxRows, int cycle, struct Room *rooms);

/*
*playGame
* Plays game, avoids monsters, picks up weapons
* IN: rooms, maxRows. Uses the information from the 
* structs to avoid monsters
* OUT: none
* POST: none
* ERROR: none
*/
void bigPatrol(int maximumRows, int maxRows, int cycle, struct Room *rooms); 

/*
*playGame
* Plays game, avoids monsters, picks up weapons
* IN: rooms, maxRows. Uses the information from the 
* structs to avoid monsters
* OUT: none
* POST: none
* ERROR: none
*/
void playGame(int maximumRows, int maxRows, struct Room *rooms);

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

#endif
/* defined __SKO01_ROGUEGAME__ */
