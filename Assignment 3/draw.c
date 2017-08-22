#include "rogueGame.h"
#include "parse.h"
#include "draw.h"



void drawHallways(int maxRows, struct Room *rooms)
{
    int yCoordinate = 2;
    int xCoordinate = 2;
    
    move(yCoordinate,xCoordinate);
    vline('#', maxRows+6);

    move(yCoordinate, xCoordinate+rooms[1].columns+4);
    vline('#', maxRows+6);

    move(yCoordinate, xCoordinate+rooms[2].columns+rooms[1].columns+8);
    vline('#', maxRows+6);

    for (int i = 1; i<4; i++)
    {
        move(yCoordinate,xCoordinate); 
        vline('#',rooms[i].rows+4);  //West wall
       
        move(yCoordinate,xCoordinate+rooms[i].columns+3);
        vline('#',rooms[i].rows+4);    //East wall
        
        move(yCoordinate,xCoordinate); 
        hline('#',rooms[i].columns+4);   //North wall
        
        move(yCoordinate+rooms[i].rows+3,xCoordinate);
        hline('#',rooms[i].columns+4);     //South wall

        xCoordinate = xCoordinate + rooms[i].columns + 4; //making space for between rooms

    }

    yCoordinate = yCoordinate + maxRows + 5;
    xCoordinate = 2;

    for (int i =4; i<7;i++)
    {

    move(yCoordinate,xCoordinate); 
    vline('#',rooms[i].rows+4);  //West wall
   
    move(yCoordinate,xCoordinate+rooms[i].columns+3);
    vline('#',rooms[i].rows+4);    //East wall
    
    move(yCoordinate,xCoordinate); 
    hline('#',rooms[i].columns+4);   //North wall
    
    move(yCoordinate+rooms[i].rows+3,xCoordinate);
    hline('#',rooms[i].columns+4);     //South wall

    xCoordinate = xCoordinate + rooms[i].columns + 4; //making space for between rooms
    }

    return;
}

void drawFloors(int maxRows, struct Room *rooms)
{
    int yCoordinate = 4;
    int xCoordinate = 4;

    for (int k = 1; k<4;k++)
    {
        for(int i=yCoordinate; i<=yCoordinate+rooms[k].rows; i++)
        {
            for(int j = xCoordinate; j < xCoordinate+rooms[k].columns; j++)
            {
                mvprintw(i,j,".");
            }
        }
    xCoordinate = xCoordinate + rooms[k].columns + 4;
    }

    yCoordinate = yCoordinate + maxRows + 4;
    xCoordinate = 4;

    for (int k = 4; k<7;k++)
    {
        for(int i=yCoordinate; i<=yCoordinate+rooms[k].rows; i++)
        {
            for(int j = xCoordinate; j < xCoordinate+rooms[k].columns; j++)
            {
                mvprintw(i,j,".");
            }
        }
    xCoordinate = xCoordinate + rooms[k].columns + 4;
    }
    return;
}

void drawRoom(int maxRows, struct Room *rooms)
{
    int yCoordinate = 3; //startpositions for the grid
    int xCoordinate = 3;
    char monsterMade;

    //first 3 rooms
    for (int i =1; i<4;i++)
    {    
		attron(COLOR_PAIR(1));

        move(yCoordinate,xCoordinate); 
        vline('|',rooms[i].rows+2);  //West wall
       
        move(yCoordinate,xCoordinate+rooms[i].columns+1);
        vline('|',rooms[i].rows+2);    //East wall
        
        move(yCoordinate,xCoordinate); 
        hline('-',rooms[i].columns+2);   //North wall
        
        move(yCoordinate+rooms[i].rows+1,xCoordinate);
        hline('-',rooms[i].columns+2);     //South wall
     
        attroff(COLOR_PAIR(1));
        //draw the doors
        if (rooms[i].doorNorth != 0)
        {
           mvprintw(yCoordinate, xCoordinate+rooms[i].doorNorth, "+");
        }
        if (rooms[i].doorWest != 0)
        {
            mvprintw(yCoordinate+rooms[i].doorWest, xCoordinate, "+");
        }
        if (rooms[i].doorEast != 0)
        {
            mvprintw(yCoordinate+rooms[i].doorEast, xCoordinate+rooms[i].columns+1, "+");
        }
        if (rooms[i].doorSouth != 0)
        {
            mvprintw(yCoordinate+rooms[i].rows+1, xCoordinate+rooms[i].doorSouth, "+");
        }
        attron(COLOR_PAIR(3));
        for (int j = 1; j < 11; j++)
        {
        
            if (rooms[i].gold[j][1] != 0)
            {
                mvprintw(yCoordinate+rooms[i].gold[j][1], xCoordinate+rooms[i].gold[j][2], "*");
            }   
        }
        if (rooms[i].goldBig[1] != 0)
        {
            mvprintw(yCoordinate+rooms[i].goldBig[1], xCoordinate+rooms[i].goldBig[2], "8");
        }
        attroff(COLOR_PAIR(3));
        for (int j = 1; j < 11; j++)
        {
            if (rooms[i].monster[j][1] != 0)
            {
                monsterMade = createdMonster(i, j, rooms);
                
                mvprintw(yCoordinate+rooms[i].monster[j][1], xCoordinate+rooms[i].monster[j][2], "%c",monsterMade);
            }
        }
        if (rooms[i].monsterBig[1] != 0)
        {
            rooms[i].monsterBig[3] = 1;
            mvprintw(yCoordinate+rooms[i].monsterBig[1], xCoordinate+rooms[i].monsterBig[2], "T");
        }
        attron(COLOR_PAIR(6));
        for (int j = 1; j < 11; j++)
        {
            if (rooms[i].equipment[j][1] != 0)
            {
                mvprintw(yCoordinate+rooms[i].equipment[j][1], xCoordinate+rooms[i].equipment[j][2], "]");
            }
        }
        attroff(COLOR_PAIR(6));
        attron(COLOR_PAIR(4));
        for (int j = 1; j < 11; j++)
        {
            if (rooms[i].potion[j][1] != 0)
            {
                mvprintw(yCoordinate+rooms[i].potion[j][1], xCoordinate+rooms[i].potion[j][2], "!");
            }
        }
        attroff(COLOR_PAIR(4));
        attron(COLOR_PAIR(5));
        for (int j = 1; j < 11; j++)
        {
            if (rooms[i].weapon[j][1] != 0)
            {
                mvprintw(yCoordinate+rooms[i].weapon[j][1], xCoordinate+rooms[i].weapon[j][2], ")");
            }
        }
        if (rooms[i].weaponRare[1] != 0)
        {
            mvprintw(yCoordinate+rooms[i].weaponRare[1], xCoordinate+rooms[i].weaponRare[2], "(");
        }
        attroff(COLOR_PAIR(5));
        for (int j = 1; j < 11; j++)
        {
            if (rooms[i].stairsUp[j][1] != 0)
            {
                mvprintw(yCoordinate+rooms[i].stairsUp[j][1], xCoordinate+rooms[i].stairsUp[j][2], ">");
            }
        }
        for (int j = 1; j < 11; j++)
        {
            if (rooms[i].stairsDown[j][1] != 0)
            {
                mvprintw(yCoordinate+rooms[i].stairsDown[j][1], xCoordinate+rooms[i].stairsDown[j][2], "<");
            }
        }

        xCoordinate = xCoordinate + rooms[i].columns + 4; //making space for between rooms
    }
    //final 3 rooms
    yCoordinate = yCoordinate + maxRows + 5;
    xCoordinate = 3;

    for (int i =4; i<7;i++)
    {
	attron(COLOR_PAIR(1));

    move(yCoordinate,xCoordinate); 
    vline('|',rooms[i].rows+2);  //West wall
   
    move(yCoordinate,xCoordinate+rooms[i].columns+1);
    vline('|',rooms[i].rows+2);    //East wall
    
    move(yCoordinate,xCoordinate); 
    hline('-',rooms[i].columns+2);   //North wall
    
    move(yCoordinate+rooms[i].rows+1,xCoordinate);
    hline('-',rooms[i].columns+2);     //South wall
    
    attroff(COLOR_PAIR(1));    
    //draw the doors
        if (rooms[i].doorNorth != 0)
        {
           mvprintw(yCoordinate, xCoordinate+rooms[i].doorNorth, "+");
        }
        if (rooms[i].doorWest != 0)
        {
            mvprintw(yCoordinate+rooms[i].doorWest, xCoordinate, "+");
        }
        if (rooms[i].doorEast != 0)
        {
            mvprintw(yCoordinate+rooms[i].doorEast, xCoordinate+rooms[i].columns+1, "+");
        }
        if (rooms[i].doorSouth != 0)
        {
            mvprintw(yCoordinate+rooms[i].rows+1, xCoordinate+rooms[i].doorSouth, "+");
        }
        attron(COLOR_PAIR(3));
        for (int j = 1; j <11; ++j)
        {
            if (rooms[i].gold[j][1] != 0)
            {
                mvprintw(yCoordinate+rooms[i].gold[j][1], xCoordinate+rooms[i].gold[j][2], "*");
            }
        }
        if (rooms[i].goldBig[1] != 0)
        {
            mvprintw(yCoordinate+rooms[i].goldBig[1], xCoordinate+rooms[i].goldBig[2], "8");
        }
        attroff(COLOR_PAIR(3));
        for (int j = 1; j <11; j++)
        {
            if (rooms[i].monster[j][1] != 0)
            {
                monsterMade = createdMonster(i, j, rooms);                
                mvprintw(yCoordinate+rooms[i].monster[j][1], xCoordinate+rooms[i].monster[j][2], "%c",monsterMade);
            }
        }
        if (rooms[i].monsterBig[1] != 0)
        {
            rooms[i].monsterBig[3] = 1;
            mvprintw(yCoordinate+rooms[i].monsterBig[1], xCoordinate+rooms[i].monsterBig[2], "T");
        }
        attron(COLOR_PAIR(6));
        for (int j = 1; j < 11; j++)
        {
            if (rooms[i].equipment[j][1] != 0)
            {
                mvprintw(yCoordinate+rooms[i].equipment[j][1], xCoordinate+rooms[i].equipment[j][2], "]");
            }
        }
        attroff(COLOR_PAIR(6));
        attron(COLOR_PAIR(4));
        for (int j = 1; j < 11; j++)
        {
            if (rooms[i].potion[j][1] != 0)
            {
                mvprintw(yCoordinate+rooms[i].potion[j][1], xCoordinate+rooms[i].potion[j][2], "!");
            }
        }
        attroff(COLOR_PAIR(4));
        attron(COLOR_PAIR(5));
        for (int j = 1; j < 11; j++)
        {
            if (rooms[i].weapon[j][1] != 0)
            {
                mvprintw(yCoordinate+rooms[i].weapon[j][1], xCoordinate+rooms[i].weapon[j][2], ")");
            }
        }
        if (rooms[i].weaponRare[1] != 0)
        {
            mvprintw(yCoordinate+rooms[i].weaponRare[1], xCoordinate+rooms[i].weaponRare[2], "(");
        }
        attroff(COLOR_PAIR(5));
        for (int j = 1; j < 11; j++)
        {
            if (rooms[i].stairsUp[j][1] != 0)
            {
                mvprintw(yCoordinate+rooms[i].stairsUp[j][1], xCoordinate+rooms[i].stairsUp[j][2], ">");
            }
        }
        for (int j = 1; j < 11; j++)
        {        
            if (rooms[i].stairsDown[j][1] != 0)
            {
                mvprintw(yCoordinate+rooms[i].stairsDown[j][1], xCoordinate+rooms[i].stairsDown[j][2], "<");
            }
        }
        xCoordinate = xCoordinate + rooms[i].columns + 4; //making space for between rooms

    }
    refresh();
}

int maxRowsTop(struct Room * rooms)
{
    int maxRowstop;

    if ((rooms[1].rows > rooms[2].rows) && (rooms[1].rows > rooms[3].rows))
    {
        maxRowstop = rooms[1].rows;
    }
    else if ((rooms[2].rows > rooms[1].rows) && (rooms[2].rows > rooms[3].rows))
    {
        maxRowstop = rooms[2].rows;
    }
    else
    {
        maxRowstop = rooms[3].rows;
    }
    return maxRowstop;
}

int maxRowsBottom(struct Room * rooms)
{
    int maxRowsbottom;

    if ((rooms[4].rows > rooms[5].rows) && (rooms[4].rows > rooms[6].rows))
    {
        maxRowsbottom = rooms[4].rows;
    }
    else if ((rooms[5].rows > rooms[4].rows) && (rooms[5].rows > rooms[6].rows))
    {
        maxRowsbottom = rooms[5].rows;
    }
    else
    {
        maxRowsbottom = rooms[6].rows;
    }
    return maxRowsbottom;
}

char createdMonster(int i, int j, struct Room *rooms)
{
    int createMonster = rand() % 4 + 1;
    char monsterMade;

    if (createMonster == 1)
    {
        rooms[i].monster[j][3] = 1;
        monsterMade = 'A';
    }
    else if (createMonster == 2)
    {
        rooms[i].monster[j][3] = 2;
        monsterMade = 'B';
    } 
    else if (createMonster == 3)
    {
        rooms[i].monster[j][3] = 3;
        monsterMade = 'S';
    }  
    else
    {
        rooms[i].monster[j][3] = 4;
        monsterMade = 'Z';
    } 

    return monsterMade;
}