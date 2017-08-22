#include "rogueGame.h"
#include "parse.h"
#include "draw.h"



int randNumber(int max)
{
    int random;
    random = rand() % max + 1;
    return random;
}

void playGame(int maximumRows, int maxRows, struct Room *rooms)
{
    int xPos = 4; //starting positions for the game
    int yPos = 4;
    int c;
    int goldCount = 0;
    int randomNumber;
    int patrolCount = 1;
    int deadEnemy = 0;
    int weapon[10] = {0};
    int equipment[10] = {0};
    int rareWeapon[6] = {0};
    int weaponCount = 0;
    int equipmentCount = 0;
    int rareWeaponCount = 0;

    struct Items *items;

    items = malloc(sizeof(struct Items));

    items->health = 50;
    items->inventory = 0;
    items->potion = 1;
    items->attack = 5;
    items->defence = 0;

    struct Enemies * enemies;

    enemies = malloc(sizeof(struct Enemies));

    enemies->aquator[0] = 5;
    enemies->aquator[1] = 1;
    enemies->aquator[2] = 2;

    enemies->bat[0] = 2;
    enemies->bat[1] = 5;
    enemies->bat[2] = 4;
    
    enemies->snake[0] = 5;
    enemies->snake[1] = 5;
    enemies->snake[2] = 4;

    enemies->zombie[0] = 15;
    enemies->zombie[1] = 5;
    enemies->zombie[2] = 2;

    enemies->troll[0] = 50;
    enemies->troll[1] = 5;
    enemies->troll[2] = 3;
    
    if((rooms[1].hero[1] != 0) && (rooms[1].hero[2] != 0))
    {
        yPos = rooms[1].hero[1] + 3;
        xPos = rooms[1].hero[2] + 3;    
    }
    else if((rooms[2].hero[1] != 0) && (rooms[2].hero[2] != 0))
    {
        yPos = rooms[2].hero[1] + 1;
        xPos = rooms[2].hero[2] + rooms[1].columns + 5;    
    }
    else if((rooms[3].hero[1] != 0) && (rooms[3].hero[2] != 0))
    {
        yPos = rooms[3].hero[1] + 1;
        xPos = rooms[3].hero[2]+ rooms[1].columns + rooms[2].columns + 9;  
    }
    else if((rooms[4].hero[1] != 0) && (rooms[4].hero[2] != 0))
    {
        yPos = rooms[4].hero[1] + maxRows + 7;
        xPos = rooms[4].hero[2] + 2; 
    }
    else if((rooms[5].hero[1] != 0) && (rooms[5].hero[2] != 0))
    {
        yPos = rooms[5].hero[1] + maxRows + 8;
        xPos = rooms[5].hero[2] + rooms[4].columns + 7;    
    }
    else if((rooms[6].hero[1] != 0) && (rooms[6].hero[2] != 0))
    {
        yPos = rooms[6].hero[1] + maxRows + 8;
        xPos = rooms[6].hero[2] + rooms[5].columns + rooms[4].columns + 11;  
    }
    else
    {
        yPos = 5;
        xPos = 5;
    }


    move(1,1);
    clrtoeol(); //clear notification bar
    mvprintw(1,1,"Gold: %d, Health: %d, Potions: %d, Attack: %d, Inv %d",goldCount, items->health, items->potion, items->attack, items->inventory);   //status bar 
    mvaddch(yPos,xPos,'@');
    move(yPos,xPos);
    refresh();


    while((c = getch()) != 'q')
    {
        int xPosOld;
        int yPosOld;
        char atPos;
             
        if (patrolCount < 4)
        {
            patrolCount++;
        }
        else
        {
            patrolCount = 1;
        }

        move(maximumRows + 11,1);
        clrtoeol(); //clear notification bar
        move(maximumRows + 12,1);
        clrtoeol(); //clear notification bar
        mvprintw(1,1,"Gold: %d, Health: %d, Potions: %d, Attack: %d, Inv %d",goldCount, items->health, items->potion, items->attack, items->inventory);   //status bar 

        move(yPos,xPos);

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
            case 'p':
            if (items->potion > 0)  //potionUse
            {
                items->potion--;
                items->health = 50;
                mvprintw(maximumRows + 11, 1, "Pot used");
            }
            else
            {
                mvprintw(maximumRows + 11,1,"Potion empty"); //Notification
            }
            break;

        }
        patrol(maximumRows, maxRows, patrolCount, rooms); //patrol each monster 
        bigPatrol(maximumRows, maxRows, patrolCount, rooms);
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
            yPos = yPosOld; //space
        }
        else if (atPos == '*')
        {
            
            mvprintw(yPosOld,xPosOld, "."); //gold - pick up, leave behind a '.'
            mvprintw(yPos,xPos, "@");
            randomNumber = randNumber(50);
            goldCount = goldCount+randomNumber;
            mvprintw(maximumRows + 11,1,"Pickup, gold"); //Notification
        }
        else if (atPos == '8')
        {
            
            mvprintw(yPosOld,xPosOld, "."); //gold - pick up, leave behind a '.'
            mvprintw(yPos,xPos, "@");
            randomNumber = randNumber(200) + 50;
            goldCount = goldCount+randomNumber;
            mvprintw(maximumRows + 11,1,"Pickup LOTS OF gold"); //Notification
        }
        else if (atPos == ')') // )= common weapon
        {
            mvprintw(yPosOld,xPosOld, ".");//Weapon - pick up, leave behind a '.'
            mvprintw(yPos,xPos, "@");

            randomNumber = randNumber(9);
            weapon[weaponCount] = randomNumber;
            weaponCount++;

            if (items->inventory == 5)
            {
                mvprintw(maximumRows + 11,1,"BagFull, common weapon"); //Notification
            }
            else
            {
                items->inventory++;
                items->attack = items->attack + randomNumber;
                mvprintw(maximumRows + 11,1,"Pickup, common weapon"); //Notification
            }
        }
        else if (atPos == '(') // ( = rare weapon
        {
            mvprintw(yPosOld,xPosOld, ".");//Weapon - pick up, leave behind a '.'
            mvprintw(yPos,xPos, "@");

            randomNumber = randNumber(5) + 10;
            rareWeapon[rareWeaponCount] = randomNumber;
            rareWeaponCount++;

            if (items->inventory == 5)
            {
                mvprintw(maximumRows + 11,1,"BagFull, rare weapon"); //Notification
            }
            else
            {
                items->inventory++;
                items->attack = items->attack + randomNumber;
                mvprintw(maximumRows + 11,1,"Pickup, rare weapon"); //Notification
            }
        }
        else if (atPos == ']') // equipment
        {
            mvprintw(yPosOld,xPosOld, ".");//equipment -pick up, leave behind a '.'
            mvprintw(yPos,xPos, "@");

            randomNumber = randNumber(20);
            equipment[equipmentCount] = randomNumber;
            equipmentCount++;

            if (items->inventory == 5)
            {
                mvprintw(maximumRows + 11,1,"BagFull, equipment"); //Notification
            }
            else
            {
                items->inventory++;
                items->defence = items->defence + randomNumber;
                mvprintw(maximumRows + 11,1,"Pickup, equipment"); //Notification
            }
        }
        else if (atPos == '!')
        {
            mvprintw(yPosOld,xPosOld, ".");//potion -pick up, leave behind a '.'
            mvprintw(yPos,xPos, "@");

            items->potion++;
            mvprintw(maximumRows + 11,1,"Pickup, potion"); //Notification

        }
        else if (atPos == 'A')
        {
            deadEnemy = combat('A', items, rooms, enemies, maximumRows, yPos, xPos, maxRows); //

            if (deadEnemy == 0)
            {
                mvaddch(yPosOld,xPosOld, '@');
                move(yPosOld,xPosOld);
                xPos = xPosOld;
                yPos = yPosOld; 
            }
            else //enemy is dead
            {
                mvprintw(yPosOld,xPosOld, ".");//leave behind a '.'
                mvprintw(yPos,xPos, "@");
                mvprintw(maximumRows + 12,1,"Kill, Aquator"); //Notification
            }

        }
        else if (atPos == 'B')
        {
            deadEnemy = combat('B',items, rooms, enemies, maximumRows, yPos, xPos, maxRows); //

            if (deadEnemy == 0)
            {
                mvaddch(yPosOld,xPosOld, '@');
                move(yPosOld,xPosOld);
                xPos = xPosOld;
                yPos = yPosOld; 
            }
            else //enemy is dead
            {
                mvprintw(yPosOld,xPosOld, ".");//leave behind a '.'
                mvprintw(yPos,xPos, "@");
                mvprintw(maximumRows + 12,1,"Kill, Bat"); //Notification
            }

        }
        else if (atPos == 'S')
        {
            deadEnemy = combat('S',items, rooms, enemies, maximumRows, yPos, xPos, maxRows); //

            if (deadEnemy == 0)
            {
                mvaddch(yPosOld,xPosOld, '@');
                move(yPosOld,xPosOld);
                xPos = xPosOld;
                yPos = yPosOld; 
            }
            else //enemy is dead
            {
                mvprintw(yPosOld,xPosOld, ".");//leave behind a '.'
                mvprintw(yPos,xPos, "@");
                mvprintw(maximumRows + 12,1,"Kill, Snake"); //Notification
            }

        }
        else if (atPos == 'T')
        {
            deadEnemy = combat('T',items, rooms, enemies, maximumRows, yPos, xPos, maxRows); //

            if (deadEnemy == 0)
            {
                mvaddch(yPosOld,xPosOld, '@');
                move(yPosOld,xPosOld);
                xPos = xPosOld;
                yPos = yPosOld; 
            }
            else //enemy is dead
            {
                mvprintw(yPosOld,xPosOld, ".");//leave behind a '.'
                mvprintw(yPos,xPos, "@");
                mvprintw(maximumRows + 12,1,"Kill, Troll"); //Notification
            }
        }
        else if (atPos == 'Z')
        {
            deadEnemy = combat('Z',items, rooms, enemies, maximumRows, yPos, xPos, maxRows); //

            if (deadEnemy == 0)
            {
                mvaddch(yPosOld,xPosOld, '@');
                move(yPosOld,xPosOld);
                xPos = xPosOld;
                yPos = yPosOld; 
            }
            else //enemy is dead
            {
                mvprintw(yPosOld,xPosOld, ".");//leave behind a '.'
                mvprintw(yPos,xPos, "@");
                mvprintw(maximumRows + 12,1,"Kill, Zombie"); //Notification
            }
        }
        else if ((atPos == '<') || (atPos == '>'))
        {
            endwin();
            printf("You went on some stairs\n");
            printf("Items: inventory: %d, potion: %d\nRatings: health: %d, attack: %d, defence: %d\n",items->inventory,items->potion, items->health,items->attack,items->defence);

            for (int i = 0; i < weaponCount; i++)
            {
                printf("Weapon value: %d\n", weapon[i]);
            }

            for (int i = 0; i < rareWeaponCount; i++)
            {
                printf("Rare Weapon value: %d\n", rareWeapon[i]);
            }

            for (int i = 0; i < equipmentCount; i++)
            {
                printf("Equipment value: %d\n", equipment[i]);
            }
            printf("Gold count: %d\n",goldCount);

            return;
        }
        else if (atPos == '+') //door
        {
            mvprintw(yPosOld,xPosOld, ".");
            mvprintw(yPos,xPos, "@");
            mvprintw(maximumRows + 11,1,"Door %c",atPos); //Notification            
        }
        else if (atPos == '#') //hallway
        {   
            mvprintw(yPosOld,xPosOld, "#");//door -pick up, leave behind a or '#'
            mvprintw(yPos,xPos, "@");
            mvprintw(maximumRows + 11, 1, "hallway");
        }
        else
        {
            mvprintw(yPos,xPos,"@");
            mvaddch(yPosOld,xPosOld, '.'); //print cursor
        }

        if(items->health < 1)
        {
            endwin();
            printf("You died\n");
            printf("Items: inventory: %d, potion: %d\nRatings: health: %d, attack: %d, defence: %d\n",items->inventory,items->potion, items->health,items->attack,items->defence);
            
            for (int i = 0; i < weaponCount; i++)
            {
                printf("Weapon value: %d\n", weapon[i]);
            }

            for (int i = 0; i < rareWeaponCount; i++)
            {
                printf("Rare Weapon value: %d\n", rareWeapon[i]);
            }

            for (int i = 0; i < equipmentCount; i++)
            {
                printf("Equipment value: %d\n", equipment[i]);
            }

            printf("Gold count: %d\n",goldCount);
            return;
        }
        move(yPos,xPos);    
        refresh();
    }   
    endwin();
    printf("Game ended\n");
    printf("Items: inventory: %d, potion: %d\nRatings: health: %d, attack: %d, defence: %d\n",items->inventory,items->potion, items->health,items->attack,items->defence);

    for (int i = 0; i < weaponCount; i++)
    {
        printf("Weapon value: %d\n", weapon[i]);
    }

    for (int i = 0; i < rareWeaponCount; i++)
    {
        printf("Rare Weapon value: %d\n", rareWeapon[i]);
    }

    for (int i = 0; i < equipmentCount; i++)
    {
        printf("Equipment value: %d\n", equipment[i]);
    }


    printf("Gold count: %d\n",goldCount);
}

void patrol(int maximumRows, int maxRows, int cycle, struct Room *rooms)
{   
    int yPos = 3;
    int xPos = 3;
    int randomNumber = rand()%4 + 1;
    char monster;
    int yPosOld;
    int xPosOld;
    char avoid;

    for (int i = 1; i < 4; i++)
    {
        for(int j = 1; j < 11; j++)
        {

            if (rooms[i].monster[j][1] != 0)
            {
                if (rooms[i].monster[j][3] == 1)
                {
                    monster = 'A';
                    yPosOld = rooms[i].monster[j][1];
                    xPosOld = rooms[i].monster[j][2];
                }
                
                else if (rooms[i].monster[j][3] == 2) //Bat random directions
                {
                    monster = 'B';
                    if (randomNumber == 1)
                    {
                    yPosOld = rooms[i].monster[j][1];
                    xPosOld = rooms[i].monster[j][2];
                    rooms[i].monster[j][2]++;  
                    }
                    else if (randomNumber == 2)
                    {
                    yPosOld = rooms[i].monster[j][1];
                    xPosOld = rooms[i].monster[j][2];
                    rooms[i].monster[j][1]++;    
                    }
                    else if (randomNumber == 3)
                    {
                    yPosOld = rooms[i].monster[j][1];
                    xPosOld = rooms[i].monster[j][2];
                    rooms[i].monster[j][2]--;    
                    }
                    else
                    {
                    yPosOld = rooms[i].monster[j][1];
                    xPosOld = rooms[i].monster[j][2];
                    rooms[i].monster[j][1]--;    
                    }
                }

                else if (rooms[i].monster[j][3] == 3) //Snake:right,right,left,left
                {
                    monster = 'S';
                    if (cycle == 1)
                    {
                    yPosOld = rooms[i].monster[j][1];
                    xPosOld = rooms[i].monster[j][2];
                    rooms[i].monster[j][2]++;    
                    }
                    else if (cycle == 2)
                    {
                    yPosOld = rooms[i].monster[j][1];
                    xPosOld = rooms[i].monster[j][2];
                    rooms[i].monster[j][2]++;  
                    }
                    else if (cycle == 3)
                    {
                    yPosOld = rooms[i].monster[j][1];
                    xPosOld = rooms[i].monster[j][2];
                    rooms[i].monster[j][2]--;  
                    }
                    else
                    {
                    yPosOld = rooms[i].monster[j][1];
                    xPosOld = rooms[i].monster[j][2];
                    rooms[i].monster[j][2]--;  
                    }

                }

                else if (rooms[i].monster[j][3] == 4) //Zombie up down up down
                {
                    monster = 'Z';
                    if (cycle == 1)
                    {
                    yPosOld = rooms[i].monster[j][1];
                    xPosOld = rooms[i].monster[j][2];
                    rooms[i].monster[j][1]--;    
                    }
                    else if (cycle == 2)
                    {
                    yPosOld = rooms[i].monster[j][1];
                    xPosOld = rooms[i].monster[j][2];
                    rooms[i].monster[j][1]++;
                    }
                    else if (cycle == 3)
                    {
                    yPosOld = rooms[i].monster[j][1];
                    xPosOld = rooms[i].monster[j][2];
                    rooms[i].monster[j][1]--;
                    }
                    else
                    {
                    yPosOld = rooms[i].monster[j][1];
                    xPosOld = rooms[i].monster[j][2];
                    rooms[i].monster[j][1]++;
                    }

                }
                else
                {
                    monster = 'A';
                }

                avoid = mvinch(yPos+rooms[i].monster[j][1],xPos+rooms[i].monster[j][2]);
                if (avoid == '.')
                {
                    mvprintw(yPos+yPosOld,xPos+xPosOld,".");
                    mvprintw(yPos+rooms[i].monster[j][1],xPos+rooms[i].monster[j][2],"%c",monster);
                }
                else
                {
                    mvprintw(yPos+yPosOld,xPos+xPosOld,"%c",monster);
                    rooms[i].monster[j][1] = yPosOld;
                    rooms[i].monster[j][2] = xPosOld;    
                }
                refresh();
            }
        }
        xPos = xPos + rooms[i].columns + 4;
    }


    yPos = yPos + maxRows + 5;
    xPos = 3;
    
    for (int i = 4; i < 7; i++)
    {
        for(int j = 1; j < 11; j++)
        {

            if (rooms[i].monster[j][1] != 0)
            {
                if (rooms[i].monster[j][3] == 1)
                {
                    monster = 'A';
                    yPosOld = rooms[i].monster[j][1];
                    xPosOld = rooms[i].monster[j][2];
                }
                
                else if (rooms[i].monster[j][3] == 2) //Bat random directions
                {
                    monster = 'B';
                    if (randomNumber == 1)
                    {
                    yPosOld = rooms[i].monster[j][1];
                    xPosOld = rooms[i].monster[j][2];
                    rooms[i].monster[j][2]++;  
                    }
                    else if (randomNumber == 2)
                    {
                    yPosOld = rooms[i].monster[j][1];
                    xPosOld = rooms[i].monster[j][2];
                    rooms[i].monster[j][1]++;    
                    }
                    else if (randomNumber == 3)
                    {
                    yPosOld = rooms[i].monster[j][1];
                    xPosOld = rooms[i].monster[j][2];
                    rooms[i].monster[j][2]--;    
                    }
                    else
                    {
                    yPosOld = rooms[i].monster[j][1];
                    xPosOld = rooms[i].monster[j][2];
                    rooms[i].monster[j][1]--;    
                    }
                }

                else if (rooms[i].monster[j][3] == 3) //Snake:right,right,left,left
                {
                    monster = 'S';
                    if (cycle == 1)
                    {
                    yPosOld = rooms[i].monster[j][1];
                    xPosOld = rooms[i].monster[j][2];
                    rooms[i].monster[j][2]++;    
                    }
                    else if (cycle == 2)
                    {
                    yPosOld = rooms[i].monster[j][1];
                    xPosOld = rooms[i].monster[j][2];
                    rooms[i].monster[j][2]++;  
                    }
                    else if (cycle == 3)
                    {
                    yPosOld = rooms[i].monster[j][1];
                    xPosOld = rooms[i].monster[j][2];
                    rooms[i].monster[j][2]--;  
                    }
                    else
                    {
                    yPosOld = rooms[i].monster[j][1];
                    xPosOld = rooms[i].monster[j][2];
                    rooms[i].monster[j][2]--;  
                    }

                }

                else if (rooms[i].monster[j][3] == 4) //Zombie up down up down
                {
                    monster = 'Z';
                    if (cycle == 1)
                    {
                    yPosOld = rooms[i].monster[j][1];
                    xPosOld = rooms[i].monster[j][2];
                    rooms[i].monster[j][1]--;    
                    }
                    else if (cycle == 2)
                    {
                    yPosOld = rooms[i].monster[j][1];
                    xPosOld = rooms[i].monster[j][2];
                    rooms[i].monster[j][1]++;
                    }
                    else if (cycle == 3)
                    {
                    yPosOld = rooms[i].monster[j][1];
                    xPosOld = rooms[i].monster[j][2];
                    rooms[i].monster[j][1]--;
                    }
                    else
                    {
                    yPosOld = rooms[i].monster[j][1];
                    xPosOld = rooms[i].monster[j][2];
                    rooms[i].monster[j][1]++;
                    }

                }
                else
                {
                    monster = 'A';
                }
                
                avoid = mvinch(yPos+rooms[i].monster[j][1],xPos+rooms[i].monster[j][2]);
                if (avoid == '.')
                {
                    mvprintw(yPos+yPosOld,xPos+xPosOld,".");
                    mvprintw(yPos+rooms[i].monster[j][1],xPos+rooms[i].monster[j][2],"%c",monster);
                }
                else
                {
                    mvprintw(yPos+yPosOld,xPos+xPosOld,"%c",monster);
                    rooms[i].monster[j][1] = yPosOld;
                    rooms[i].monster[j][2] = xPosOld;    
                }
                refresh();
            }
        }
        xPos = xPos + rooms[i].columns + 4;
    }
    return;

}

void bigPatrol(int maximumRows, int maxRows, int cycle, struct Room *rooms) 
{
    int yPos = 3;
    int xPos = 3;
    int yPosOld;
    int xPosOld;
    char avoid;

    for (int i = 1; i < 4; i++)
    {
        if (rooms[i].monsterBig[1] != 0)
        {
            if (cycle == 1)
            {
                yPosOld = rooms[i].monsterBig[1];
                xPosOld = rooms[i].monsterBig[2];
                rooms[i].monsterBig[1]--;
            }
            else if (cycle == 2)
            {
                yPosOld = rooms[i].monsterBig[1];
                xPosOld = rooms[i].monsterBig[2];
                rooms[i].monsterBig[2]++;
            }
            else if (cycle == 3)
            {
                yPosOld = rooms[i].monsterBig[1];
                xPosOld = rooms[i].monsterBig[2];
                rooms[i].monsterBig[1]++;
            }
            else
            {
                yPosOld = rooms[i].monsterBig[1];
                xPosOld = rooms[i].monsterBig[2];
                rooms[i].monsterBig[2]--;
            }

            avoid = mvinch(yPos+rooms[i].monsterBig[1],xPos+rooms[i].monsterBig[2]);
            if (avoid == '.')
            {
                mvprintw(yPos+yPosOld,xPos+xPosOld,".");
                mvprintw(yPos+rooms[i].monsterBig[1],xPos+rooms[i].monsterBig[2],"T");
            }
            else
            {
                mvprintw(yPos+yPosOld,xPos+xPosOld,"T");
                rooms[i].monsterBig[1] = yPosOld;
                rooms[i].monsterBig[2] = xPosOld;    
            }
        }

        xPos = xPos + rooms[i].columns + 4;
    }

    yPos = yPos + maxRows + 5;
    xPos = 3;

    for (int i = 4; i < 7; i++)
    {
        if (rooms[i].monsterBig[1] != 0)
        {
            if (cycle == 1)
            {
                yPosOld = rooms[i].monsterBig[1];
                xPosOld = rooms[i].monsterBig[2];
                rooms[i].monsterBig[1]--;
            }
            else if (cycle == 2)
            {
                yPosOld = rooms[i].monsterBig[1];
                xPosOld = rooms[i].monsterBig[2];
                rooms[i].monsterBig[2]++;
            }
            else if (cycle == 3)
            {
                yPosOld = rooms[i].monsterBig[1];
                xPosOld = rooms[i].monsterBig[2];
                rooms[i].monsterBig[1]++;
            }
            else
            {
                yPosOld = rooms[i].monsterBig[1];
                xPosOld = rooms[i].monsterBig[2];
                rooms[i].monsterBig[2]--;
            }

            avoid = mvinch(yPos+rooms[i].monsterBig[1],xPos+rooms[i].monsterBig[2]);
            if (avoid == '.')
            {
                mvprintw(yPos+yPosOld,xPos+xPosOld,".");
                mvprintw(yPos+rooms[i].monsterBig[1],xPos+rooms[i].monsterBig[2],"T");
            }
            else
            {
                mvprintw(yPos+yPosOld,xPos+xPosOld,"T");
                rooms[i].monsterBig[1] = yPosOld;
                rooms[i].monsterBig[2] = xPosOld;    
            }
        }

        xPos = xPos + rooms[i].columns + 4;
    }

    return;
}

int combat(char position, struct Items *items, struct Room *rooms, struct Enemies *enemies, int maximumRows, int yPos, int xPos, int maxRows) 
//make the enemy at that position rooms[i].monster[1-10][3] is 4, then zombie is dead and should be 0
{

    int random = rand()%10 + 1;
    int deadEnemy = 0;
    int yCoordinate = 3;
    int xCoordinate = 3;

    if (position == 'A')
    {
        if (random > enemies->aquator[2])
        {
            enemies->aquator[0] = enemies->aquator[0] - items->attack;
            mvprintw(maximumRows + 11,1,"GiveDamage, Aquator. Aquator health: %d", enemies->aquator[0]); //Notification

            if (enemies->aquator[0] < 1)
            {
                deadEnemy = 1;
                yCoordinate = 3;
                xCoordinate = 3;
                for (int i = 1; i < 4; i++)
                {                
                    for(int j = 1; j < 11; j++)
                    {
                        if ((yCoordinate + rooms[i].monster[j][1] == yPos) && (xCoordinate + rooms[i].monster[j][2] == xPos))
                        {
                            rooms[i].monster[j][1] = 0;
                            rooms[i].monster[j][3] = 0; //make it monster at that position never return
                        }
                    }
                    xCoordinate = xCoordinate + rooms[i].columns + 4;
                }
                yCoordinate = 3 + maxRows + 5;
                xCoordinate = 3;
                for (int i = 4; i < 7; i++)
                {
                    for(int j = 1; j < 11; j++)
                    {
                        if ((yCoordinate + rooms[i].monster[j][1] == yPos) && (xCoordinate + rooms[i].monster[j][2] == xPos))
                        {
                            rooms[i].monster[j][1] = 0;
                            rooms[i].monster[j][3] = 0; //make it monster at that position never return
                        }
                    }
                    xCoordinate = xCoordinate + rooms[i].columns + 4;
                }
            }
            refresh();
        }
        else
        {
            items->health = items->health - enemies->aquator[1];
            mvprintw(maximumRows + 11,1,"TakeDamage Aquator attacked. Your health: %d", items->health); //Notification
            refresh();
        }
    }
    if (position == 'B')
    {
        if (random > enemies->bat[2])
        {
            enemies->bat[0] = enemies->bat[0] - items->attack;
            mvprintw(maximumRows + 11,1,"GiveDamage, Bat. Bat health: %d", enemies->bat[0]); //Notification
            if (enemies->bat[0] < 1)
            {
                deadEnemy = 1;
                yCoordinate = 3;
                xCoordinate = 3;
                for (int i = 1; i < 4; i++)
                {                
                    for(int j = 1; j < 11; j++)
                    {
                        if ((yCoordinate + rooms[i].monster[j][1] == yPos) && (xCoordinate + rooms[i].monster[j][2] == xPos))
                        {
                            rooms[i].monster[j][1] = 0;
                            rooms[i].monster[j][3] = 0; //make it monster at that position never return
                        }
                    }
                    xCoordinate = xCoordinate + rooms[i].columns + 4;
                }
                yCoordinate = 3 + maxRows + 5;
                xCoordinate = 3;
                for (int i = 4; i <= 6; i++)
                {
                    for(int j = 1; j <= 10; j++)
                    {
                        if ((yCoordinate + rooms[i].monster[j][1] == yPos) && (xCoordinate + rooms[i].monster[j][2] == xPos))
                        {
                            rooms[i].monster[j][1] = 0;
                            rooms[i].monster[j][3] = 0; //make it monster at that position never return
                        }
                    }
                    xCoordinate = xCoordinate + rooms[i].columns + 4;
                }

            }            
            refresh();
        }
        else
        {
            items->health = items->health - enemies->bat[1];
            mvprintw(maximumRows + 11,1,"TakeDamage Bat attacked. Your health: %d", items->health); //Notification
            refresh();
        }
    }
    if (position == 'S')
    {
        if (random > enemies->snake[2])
        {
            enemies->snake[0] = enemies->snake[0] - items->attack;
            mvprintw(maximumRows + 11,1,"GiveDamage, Snake. Snake health: %d", enemies->snake[0]); //Notification
            if (enemies->snake[0] < 1)
            {
                deadEnemy = 1;
                yCoordinate = 3;
                xCoordinate = 3;
                for (int i = 1; i < 4; i++)
                {                
                    for(int j = 1; j < 11; j++)
                    {
                        if ((yCoordinate + rooms[i].monster[j][1] == yPos) && (xCoordinate + rooms[i].monster[j][2] == xPos))
                        {
                            rooms[i].monster[j][1] = 0;
                            rooms[i].monster[j][3] = 0; //make it monster at that position never return
                        }
                    }
                    xCoordinate = xCoordinate + rooms[i].columns + 4;
                }
                yCoordinate = 3 + maxRows + 5;
                xCoordinate = 3;
                for (int i = 4; i < 7; i++)
                {
                    for(int j = 1; j < 11; j++)
                    {
                        if ((yCoordinate + rooms[i].monster[j][1] == yPos) && (xCoordinate + rooms[i].monster[j][2] == xPos))
                        {
                            rooms[i].monster[j][1] = 0;
                            rooms[i].monster[j][3] = 0; //make it monster at that position never return
                        }
                    }
                    xCoordinate = xCoordinate + rooms[i].columns + 4;
                }
            }
            refresh();
        }
        else
        {
            items->health = items->health - enemies->snake[1];
            mvprintw(maximumRows + 11,1,"TakeDamage Snake attacked. Your health: %d", items->health); //Notification
            refresh();
        }
    }
    if (position == 'T')
    {
        if (random > enemies->troll[2])
        {
            enemies->troll[0] = enemies->troll[0] - items->attack;
            mvprintw(maximumRows + 11,1,"GiveDamage, Troll. Troll health: %d", enemies->troll[0]); //Notification
            if (enemies->troll[0] < 1)
            {

                deadEnemy = 1;

                yCoordinate = 3;
                xCoordinate = 3;
                for (int i = 1; i < 4; i++)
                {                
                    if ((yCoordinate + rooms[i].monsterBig[1] == yPos) && (xCoordinate + rooms[i].monsterBig[2] == xPos))
                        {
                            rooms[i].monsterBig[1] = 0;
                            rooms[i].monsterBig[3] = 0; //make it monster at that position never return
                        }
                    xCoordinate = xCoordinate + rooms[i].columns + 4;
                }

                yCoordinate = 3 + maxRows + 5;
                xCoordinate = 3;
                for (int i = 4; i < 7; i++)
                {
                        if ((yCoordinate + rooms[i].monsterBig[1] == yPos) && (xCoordinate + rooms[i].monsterBig[2] == xPos))
                        {
                            rooms[i].monsterBig[1] = 0;
                            rooms[i].monsterBig[3] = 0; //make it monster at that position never return
                        }
                    xCoordinate = xCoordinate + rooms[i].columns + 4;
                }
            }            
            refresh();
        }
        else
        {
            items->health = items->health - enemies->troll[1];
            mvprintw(maximumRows + 11,1,"TakeDamage Troll attacked. Your health: %d", items->health); //Notification
            refresh();
        }
    }
    if (position == 'Z')
    {
        if (random > enemies->zombie[2])
        {
            enemies->zombie[0] = enemies->zombie[0] - items->attack;
            mvprintw(maximumRows + 11,1,"GiveDamage, Zombie. Zombie health: %d", enemies->zombie[0]); //Notification
            if (enemies->zombie[0] < 1)
            {
                deadEnemy = 1;
                yCoordinate = 3;
                xCoordinate = 3;
                for (int i = 1; i < 4; i++)
                {                
                    for(int j = 1; j < 11; j++)
                    {
                        if ((yCoordinate + rooms[i].monster[j][1] == yPos) && (xCoordinate + rooms[i].monster[j][2] == xPos))
                        {
                            rooms[i].monster[j][1] = 0;
                            rooms[i].monster[j][3] = 0; //make it monster at that position never return
                        }
                    }
                    xCoordinate = xCoordinate + rooms[i].columns + 4;
                }
                yCoordinate = 3 + maxRows + 5;
                xCoordinate = 3;
                for (int i = 4; i < 7; i++)
                {
                    for(int j = 1; j < 11; j++)
                    {
                        if ((yCoordinate + rooms[i].monster[j][1] == yPos) && (xCoordinate + rooms[i].monster[j][2] == xPos))
                        {
                            rooms[i].monster[j][1] = 0;
                            rooms[i].monster[j][3] = 0; //make it monster at that position never return
                        }
                    }
                    xCoordinate = xCoordinate + rooms[i].columns + 4;
                }
            }            
            refresh();
        }
        else
        {
            items->health = items->health - enemies->zombie[1];
            mvprintw(maximumRows + 11,1,"TakeDamage Zombie attacked. Your health: %d", items->health); //Notification
            refresh();
        }
    }
    return deadEnemy;
}
