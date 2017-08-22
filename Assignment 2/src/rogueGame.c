#include "rogueGame.h"
#include "parse.h"
#include "draw.h"

int randNumber(int max)
{
    int random;

    srand(time(NULL));
    random = rand() % max;
    return random;
}

void playGame(int maxRows, struct Room *rooms)
{
    int xPos = 2; //starting positions for the game
    int yPos = 2;
    int c;
    int goldCount = 0;
    int gold;
    int floorCount = 1;
    
    if((rooms[1].hero[1] != 0) && (rooms[1].hero[2] != 0))
    {
        yPos = rooms[1].hero[1] + 1;
        xPos = rooms[1].hero[2] + 1;    
        floorCount = 1;
    }
    else if((rooms[2].hero[1] != 0) && (rooms[2].hero[2] != 0))
    {
        yPos = rooms[2].hero[1] + 1;
        xPos = rooms[2].hero[2] + rooms[1].columns + 5;    
        floorCount = 2;
    }
    else if((rooms[3].hero[1] != 0) && (rooms[3].hero[2] != 0))
    {
        yPos = rooms[3].hero[1] + 1;
        xPos = rooms[3].hero[2]+ rooms[1].columns + rooms[2].columns + 9;  
        floorCount = 3;  
    }
    else if((rooms[4].hero[1] != 0) && (rooms[4].hero[2] != 0))
    {
        yPos = rooms[4].hero[1] + maxRows + 2;
        xPos = rooms[4].hero[2] + 2; 
        floorCount = 4;   
    }
    else if((rooms[5].hero[1] != 0) && (rooms[5].hero[2] != 0))
    {
        yPos = rooms[5].hero[1] + maxRows + 3;
        xPos = rooms[5].hero[2] + rooms[4].columns + 5; 
        floorCount = 5;   
    }
    else if((rooms[6].hero[1] != 0) && (rooms[6].hero[2] != 0))
    {
        yPos = rooms[6].hero[1] + maxRows + 3;
        xPos = rooms[6].hero[2] + rooms[5].columns + rooms[4].columns + 9;
        floorCount = 6;    
    }
    else
    {
        yPos = 3;
        xPos = 3;
        floorCount = 1;
    }

    mvaddch(yPos,xPos,'@');
    move(yPos,xPos);
    refresh();
    while((c = getch()) != 'q')
    {
        int xPosOld;
        int yPosOld;
        char atPos;
        
        atPos = mvinch(yPos,xPos);
        yPosOld = yPos;
        xPosOld = xPos;
        switch (c)
        {
            case 'a': //left
            xPos--;
            break;
            case 'w': //up
            yPos--;
            break;
            case 's': //down
            yPos++;
            break;
            case 'd': //right
            xPos++;
            break;
        }

        atPos = mvinch(yPos,xPos);

        if (atPos == '|')
        {
            mvaddch(yPosOld,xPosOld, '@');
            move(yPosOld,xPosOld);
            xPos = xPosOld;
            yPos = yPosOld; //vertical wall
        }
        else if (atPos == '-')
        {
            mvaddch(yPosOld,xPosOld, '@');
            move(yPosOld,xPosOld);
            xPos = xPosOld;
            yPos = yPosOld; //horizontal wall
        }
        else if (atPos == ' ')
        {
            mvaddch(yPosOld,xPosOld, '@');
            move(yPosOld,xPosOld);
            xPos = xPosOld;
            yPos = yPosOld; //horizontal wall
        }
        else if (atPos == '*')
        {
            
            mvprintw(yPosOld,xPosOld, "."); //gold - pick up, leave behind a '.'
            mvprintw(yPos,xPos, "@");
            gold = randNumber(50);
            goldCount = goldCount+gold;
        }
        else if (atPos == '8')
        {
            
            mvprintw(yPosOld,xPosOld, "."); //gold - pick up, leave behind a '.'
            mvprintw(yPos,xPos, "@");
            gold = randNumber(200) + 50;
            goldCount = goldCount+gold;
        }
        else if ((atPos == ')') || (atPos == '('))
        {
            mvprintw(yPosOld,xPosOld, ".");//Weapon - pick up, leave behind a '.'
            mvprintw(yPos,xPos, "@");
        }
        else if (atPos == ']')
        {
            mvprintw(yPosOld,xPosOld, ".");//equipment -pick up, leave behind a '.'
            mvprintw(yPos,xPos, "@");
        }
        else if (atPos == '!')
        {
            mvprintw(yPosOld,xPosOld, ".");//potion -pick up, leave behind a '.'
            mvprintw(yPos,xPos, "@");
        }
        else if ((atPos == 'A') || (atPos == 'B') || (atPos == 'S') || (atPos == 'T') || (atPos == 'Z'))
        {
            mvaddch(yPosOld,xPosOld, '@');
            move(yPosOld,xPosOld);
            xPos = xPosOld;
            yPos = yPosOld; //horizontal wall
        }
        else if ((atPos == '<') || (atPos == '>'))
        {
            endwin();
            printf("\nGold count: %d\n",goldCount);
            return;
        }
        else if (atPos == '+')
        {
            yPos = yTeleport(maxRows, floorCount, rooms);
            xPos = xTeleport(floorCount, rooms);
            mvprintw(yPos,xPos, "@");
             //move to next hero position
            if (floorCount == 6)
            {
               floorCount = 1;
            }
            else
            {
                floorCount++;
            }
            mvprintw(yPosOld,xPosOld, ".");
        }
        else
        {
            mvprintw(yPos,xPos,"@");
            mvprintw(yPosOld,xPosOld, "."); //print cursor
        }
        move(yPos,xPos);
        refresh();
    }   
    endwin();
    printf("\nGold count: %d\n",goldCount);
}

int yTeleport(int maxRows, int floor, struct Room *rooms)
{
    int yPos = 1;

    if ((floor == 1)  && (rooms[2].doorNorth != 0))
    {
        yPos++;
    }
    else if ((floor == 1) && (rooms[2].doorSouth != 0))
    {
        yPos = yPos + rooms[2].rows;
    }
    else if ((floor == 1) && (rooms[2].doorWest != 0))
    {
        yPos = yPos+rooms[2].doorWest;
    }
    else if ((floor == 1) && (rooms[2].doorEast != 0))
    {
        yPos = yPos+rooms[2].doorEast;
    }  

    if ((floor == 2)  && (rooms[3].doorNorth != 0))
    {
        yPos++;
    }
    else if ((floor == 2) && (rooms[3].doorSouth != 0))
    {
        yPos = yPos + rooms[3].rows;
    }
    else if ((floor == 2) && (rooms[3].doorWest != 0))
    {
        yPos = yPos+rooms[3].doorWest;
    }
    else if ((floor == 2) && (rooms[3].doorEast != 0))
    {
        yPos = yPos+rooms[3].doorEast;
    }     

    if ((floor == 3)  && (rooms[4].doorNorth != 0))
    {
        yPos = yPos + maxRows + 3;
    }
    else if ((floor == 3) && (rooms[4].doorSouth != 0))
    {
        yPos = yPos + maxRows + rooms[4].rows + 2;
    }
    else if ((floor == 3) && (rooms[4].doorWest != 0))
    {
        yPos = yPos + maxRows+rooms[4].doorWest + 2;
    }
    else if ((floor == 3) && (rooms[4].doorEast != 0))
    {
        yPos = yPos + maxRows + rooms[4].doorEast + 2;
    }

    if ((floor == 4)  && (rooms[5].doorNorth != 0))
    {
        yPos = yPos + maxRows + 3;
    }
    else if ((floor == 4) && (rooms[5].doorSouth != 0))
    {
        yPos = yPos + maxRows + rooms[5].rows + 2;
    }
    else if ((floor == 4) && (rooms[5].doorWest != 0))
    {
        yPos = yPos + maxRows + rooms[5].doorWest + 2;
    }
    else if ((floor == 4) && (rooms[5].doorEast != 0))
    {
        yPos = yPos+ maxRows + rooms[5].doorEast + 2;
    }
    else

    if ((floor == 5)  && (rooms[6].doorNorth != 0))
    {
        yPos = yPos + maxRows + 3;
    }
    else if ((floor == 5) && (rooms[6].doorSouth != 0))
    {
        yPos = yPos + maxRows + rooms[6].rows + 2;
    }
    else if ((floor == 5) && (rooms[6].doorWest != 0))
    {
        yPos = yPos + maxRows+rooms[6].doorWest + 2;
    }
    else if ((floor == 5) && (rooms[6].doorEast != 0))
    {
        yPos = yPos + maxRows + rooms[6].doorEast + 2;
    }


    if ((floor == 6)  && (rooms[1].doorNorth != 0))
    {
        yPos++;
    }
    else if ((floor == 6) && (rooms[1].doorSouth != 0))
    {
        yPos = yPos + rooms[1].rows;
    }
    else if ((floor == 6) && (rooms[1].doorWest != 0))
    {
        yPos = yPos+rooms[1].doorWest;
    }
    else if ((floor == 6) && (rooms[1].doorEast != 0))
    {
        yPos = yPos+rooms[1].doorEast;
    }
    return yPos;
}

int xTeleport(int floor, struct Room *rooms)
{
    int xPos=1;

    if ((floor == 1)  && (rooms[2].doorNorth != 0))
    {
        xPos = xPos + rooms[1].columns + rooms[2].doorNorth + 4;
    }
    else if ((floor == 1) && (rooms[2].doorSouth != 0))
    {
        xPos = xPos + rooms[1].columns + rooms[2].doorSouth + 4;
    }
    else if ((floor == 1) && (rooms[2].doorWest != 0))
    {
        xPos = xPos+rooms[1].columns + 5;
    }
    else if ((floor == 1) && (rooms[2].doorEast != 0))
    {
        xPos = xPos+rooms[1].columns+rooms[2].columns + 4;
    }

    if ((floor == 2)  && (rooms[3].doorNorth != 0))
    {
        xPos = xPos + rooms[1].columns + rooms[2].columns +rooms[3].doorNorth + 8;
    }
    else if ((floor == 2) && (rooms[3].doorSouth != 0))
    {
        xPos = xPos + rooms[1].columns + rooms[2].columns +rooms[3].doorSouth + 8;
    }
    else if ((floor == 2) && (rooms[3].doorWest != 0))
    {
        xPos = xPos + rooms[1].columns + rooms[2].columns + 9;
    }
    else if ((floor == 2) && (rooms[3].doorEast != 0))
    {
        xPos = xPos+rooms[1].columns+rooms[2].columns+rooms[3].columns + 8;
    }

    if ((floor == 3)  && (rooms[4].doorNorth != 0))
    {
        xPos = xPos + rooms[4].doorNorth;
    }
    else if ((floor == 3) && (rooms[4].doorSouth != 0))
    {
        xPos = xPos + rooms[4].doorSouth;
    }
    else if ((floor == 3) && (rooms[4].doorWest != 0))
    {
        xPos++;
    }
    else if ((floor == 3) && (rooms[4].doorEast != 0))
    {
        xPos = xPos+rooms[4].columns;
    }

    if ((floor == 4)  && (rooms[5].doorNorth != 0))
    {
        xPos = xPos + rooms[4].columns + rooms[5].doorNorth + 4;
    }
    else if ((floor == 4) && (rooms[5].doorSouth != 0))
    {
        xPos = xPos + rooms[4].columns + rooms[5].doorSouth + 4;
    }
    else if ((floor == 4) && (rooms[5].doorWest != 0))
    {
        xPos = xPos+rooms[4].columns + 5;
    }
    else if ((floor == 4) && (rooms[5].doorEast != 0))
    {
        xPos = xPos+rooms[4].columns + rooms[5].columns + 4;
    }

    if ((floor == 5)  && (rooms[6].doorNorth != 0))
    {
        xPos = xPos + rooms[4].columns + rooms[5].columns + rooms[6].doorNorth + 8;
    }
    else if ((floor == 5) && (rooms[6].doorSouth != 0))
    {
        xPos = xPos + rooms[4].columns + rooms[5].columns + rooms[6].doorSouth + 8;
    }
    else if ((floor == 5) && (rooms[6].doorWest != 0))
    {
        xPos = xPos+rooms[4].columns + rooms[5].columns + 9;
    }
    else if ((floor == 5) && (rooms[6].doorEast != 0))
    {
        xPos = xPos+rooms[4].columns + rooms[5].columns + rooms[6].columns + 8;
    }

    if ((floor == 6)  && (rooms[1].doorNorth != 0))
    {
        xPos = xPos + rooms[1].doorNorth;
    }
    else if ((floor == 6) && (rooms[1].doorSouth != 0))
    {
        xPos = xPos + rooms[1].doorSouth;
    }
    else if ((floor == 6) && (rooms[1].doorWest != 0))
    {
        xPos++;
    }
    else if ((floor == 6) && (rooms[1].doorEast != 0))
    {
        xPos = xPos+rooms[1].columns;
    }
    return xPos;
}
