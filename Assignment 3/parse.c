#include "rogueGame.h"
#include "parse.h"
#include "draw.h"

FILE * openFile(char* fileName, char* operation)
{
    FILE * f = fopen(fileName, operation);
    return f;
}

void closeFile(FILE* fileName)
{
    fclose(fileName);
    return;
}

void initCurses(void)
{
    initscr();
    start_color();
    init_pair(1, COLOR_BLUE, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
    init_pair(4, COLOR_GREEN, COLOR_BLACK);
    init_pair(5, COLOR_CYAN, COLOR_BLACK);
    init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
    attron(COLOR_PAIR(2));
    mvprintw(1,1,"This is Rogue. Collect money, avoid monsters");
    mvprintw(2,1,"a=left, s=down, d=right,w=up, q=quit");
    mvprintw(4,1,"Press a key to start the game");  
    attroff(COLOR_PAIR(2));
    cbreak();
    noecho();
    getch();
    clear();
    keypad(stdscr, TRUE);
}

struct Room * parseFile(FILE* fileName, struct Room *rooms)
{
    char sentence[255];
    int line = 0;
    int counter = 0;
    char parsed[50];
    int conversion = 0;
    int conversionTwo = 0;
    int parsedLength;
    int countGold = 1;
    int countStairsDown = 1;
    int countStairsUp = 1;
    int countWeapon = 1;
    int countEquipment = 1;
    int countPotion = 1;
    int countMonster = 1;

    while (fgets(sentence, 255,fileName) != NULL)
    {
        char *ptr;
        
        refresh();
        line++; //counts each line
        ptr = strtok(sentence, "X ");
        while(ptr != NULL)
        {
            strcpy(parsed,ptr);
            parsedLength = strlen(parsed);
            counter++;
            ptr = strtok(NULL, "X ");
            
            if (counter == 1) //room row
            {
                conversion = atoi(parsed);
                rooms[line].rows = conversion;                
            }
            else if (counter == 2) //room column
            {
                conversion = atoi(parsed);
                rooms[line].columns = conversion;
            }
            else
            {
                if (parsed[0] == 'd')
                {
                    if (parsed[1] == 'e')
                    {
                        if ((parsedLength == 3) || (parsed[3] == '\n'))
                        {
                            conversion = parsed[2] - 48; //convert from ascii to int
                            rooms[line].doorEast = conversion; //depending on if the number is 1 digit or 2
                        }
                        else 
                        {
                            conversion = parsed[2] - 48;
                            conversion = conversion * 10;
                            conversionTwo = parsed[3] - 48;
                            conversion = conversionTwo + conversion;
                            rooms[line].doorEast = conversion;
                        }
                    }
                    else if (parsed[1] == 'w')
                    {
                        if ((parsedLength == 3) || (parsed[3] == '\n'))
                        {
                            conversion = parsed[2] - 48; //convert from ascii to int
                            rooms[line].doorWest = conversion; //depending on if the number is 1 digit or 2
                        }
                        else 
                        {
                            conversion = parsed[2] - 48;
                            conversion = conversion * 10;
                            conversionTwo = parsed[3] - 48;
                            conversion = conversionTwo + conversion;
                            rooms[line].doorWest = conversion;
                        }
                    }
                    else if (parsed[1] == 'n')
                    {
                        if ((parsedLength == 3) || (parsed[3] == '\n'))
                        {
                            conversion = parsed[2] - 48; //convert from ascii to int
                            rooms[line].doorNorth = conversion; //depending on if the number is 1 digit or 2
                        }
                        else 
                        {
                            conversion = parsed[2] - 48;
                            conversion = conversion * 10;
                            conversionTwo = parsed[3] - 48;
                            conversion = conversionTwo + conversion;
                            rooms[line].doorNorth = conversion;
                        }
                    }
                    else if (parsed[1] == 's')
                    {
                        if ((parsedLength == 3) || (parsed[3] == '\n'))
                        {
                            conversion = parsed[2] - 48; //convert from ascii to int
                            rooms[line].doorSouth = conversion; //depending on if the number is 1 digit or 2
                        }
                        else 
                        {
                            conversion = parsed[2] - 48;
                            conversion = conversion * 10;
                            conversionTwo = parsed[3] - 48;
                            conversion = conversionTwo + conversion;
                            rooms[line].doorSouth = conversion;
                        }
                    }
                }
                else if (parsed[0] == 'g') 
                {
                    if (parsed[2] == ',')
                    {
                        if (parsedLength == 4)
                        {
                            conversion = parsed[1] - 48;
                            rooms[line].gold[countGold][1] = conversion;
                            conversion = parsed[3] - 48;
                            rooms[line].gold[countGold][2] = conversion;
                        }
                        else if(parsedLength == 5)
                        {
                            if (parsed[4] == '\n')
                            {
                            conversion = parsed[1] - 48;
                            rooms[line].gold[countGold][1] = conversion;
                            conversion = parsed[3] - 48;   
                            rooms[line].gold[countGold][2] = conversion;//conversionTwo + conversion;
                            }
                            else
                            {
                                conversion = parsed[1] - 48;
                                rooms[line].gold[countGold][1] = conversion;
                                conversion = parsed[3] - 48;   
                                conversion = conversion * 10;
                                conversionTwo = parsed[4] - 48;
                                rooms[line].gold[countGold][2] = conversionTwo + conversion;                                 
                            }  
                        }
                        else
                        {  
                            conversion = parsed[1] - 48;
                            rooms[line].gold[countGold][1] = conversion;
                            conversion = parsed[3] - 48;   
                            conversion = conversion * 10;
                            conversionTwo = parsed[4] - 48;
                            rooms[line].gold[countGold][2] = conversionTwo + conversion;         
                        }
                    }
                    else if (parsed[3]  == ',')
                    {
                        if (parsedLength == 5)
                        {
                            conversion = parsed[1] - 48;
                            conversion = conversion * 10;
                            conversionTwo = parsed[2] - 48;
                            rooms[line].gold[countGold][1] = conversion + conversionTwo;
                            conversion = parsed[4] - 48;
                            rooms[line].gold[countGold][2] = conversion;
                        }
                        else if (parsedLength == 6)
                        {
                            if (parsed[5] == '\n')
                            {
                                conversion = parsed[1] - 48;
                                conversion = conversion * 10;
                                conversionTwo = parsed[2] - 48;
                                rooms[line].gold[countGold][1] = conversion + conversionTwo;
                                conversion = parsed[4] - 48;
                                rooms[line].gold[countGold][2] = conversion;
                            }
                            else
                            {
                                conversion = parsed[1] - 48;
                                conversion = conversion * 10;
                                conversionTwo = parsed[2] - 48;
                                rooms[line].gold[countGold][1] = conversion + conversionTwo;
                                conversion = parsed[4] - 48;
                                conversion = conversion * 10;
                                conversionTwo = parsed[5] - 48;
                                rooms[line].gold[countGold][2] = conversion + conversionTwo;
                            }
                        }
                        else
                        {
                            conversion = parsed[1] - 48;
                            conversion = conversion * 10;
                            conversionTwo = parsed[2] - 48;
                            rooms[line].gold[countGold][1] = conversion + conversionTwo;
                            conversion = parsed[4] - 48;
                            conversion = conversion * 10;
                            conversionTwo = parsed[5] - 48;
                            rooms[line].gold[countGold][2] = conversion + conversionTwo;

                        }
                    }
                    else
                    {
                    }
                    countGold++;
                }
                else if (parsed[0] == 'G')
                {
                    if (parsed[2] == ',')
                    {
                        if (parsedLength == 4)
                        {
                            conversion = parsed[1] - 48;
                            rooms[line].goldBig[1] = conversion;
                            conversion = parsed[3] - 48;
                            rooms[line].goldBig[2] = conversion;
                        }
                        else if(parsedLength == 5)
                        {
                            if (parsed[4] == '\n')
                            {
                            conversion = parsed[1] - 48;
                            rooms[line].goldBig[1] = conversion;
                            conversion = parsed[3] - 48;   
                            rooms[line].goldBig[2] = conversion;//conversionTwo + conversion;
                            }
                            else
                            {
                                conversion = parsed[1] - 48;
                                rooms[line].goldBig[1] = conversion;
                                conversion = parsed[3] - 48;   
                                conversion = conversion * 10;
                                conversionTwo = parsed[4] - 48;
                                rooms[line].goldBig[2] = conversionTwo + conversion;                                 
                            }  
                        }
                        else
                        {  
                            conversion = parsed[1] - 48;
                            rooms[line].goldBig[1] = conversion;
                            conversion = parsed[3] - 48;   
                            conversion = conversion * 10;
                            conversionTwo = parsed[4] - 48;
                            rooms[line].goldBig[2] = conversionTwo + conversion;         
                        }
                    }
                    else if (parsed[3]  == ',')
                    {
                        if (parsedLength == 5)
                        {
                            conversion = parsed[1] - 48;
                            conversion = conversion * 10;
                            conversionTwo = parsed[2] - 48;
                            rooms[line].goldBig[1] = conversion + conversionTwo;
                            conversion = parsed[4] - 48;
                            rooms[line].goldBig[2] = conversion;
                        }
                        else if (parsedLength == 6)
                        {
                            if (parsed[5] == '\n')
                            {
                                conversion = parsed[1] - 48;
                                conversion = conversion * 10;
                                conversionTwo = parsed[2] - 48;
                                rooms[line].goldBig[1] = conversion + conversionTwo;
                                conversion = parsed[4] - 48;
                                rooms[line].goldBig[2] = conversion;
                            }
                            else
                            {
                                conversion = parsed[1] - 48;
                                conversion = conversion * 10;
                                conversionTwo = parsed[2] - 48;
                                rooms[line].goldBig[1] = conversion + conversionTwo;
                                conversion = parsed[4] - 48;
                                conversion = conversion * 10;
                                conversionTwo = parsed[5] - 48;
                                rooms[line].goldBig[2] = conversion + conversionTwo;
                            }
                        }
                        else
                        {
                            conversion = parsed[1] - 48;
                            conversion = conversion * 10;
                            conversionTwo = parsed[2] - 48;
                            rooms[line].goldBig[1] = conversion + conversionTwo;
                            conversion = parsed[4] - 48;
                            conversion = conversion * 10;
                            conversionTwo = parsed[5] - 48;
                            rooms[line].goldBig[2] = conversion + conversionTwo;

                        }
                    }
                    else
                    {
                    }                    
                }
                else if (parsed[0] == 'm')
                {
                    if (parsed[2] == ',')
                    {
                        if (parsedLength == 4)
                        {
                            conversion = parsed[1] - 48;
                            rooms[line].monster[countMonster][1] = conversion;
                            conversion = parsed[3] - 48;
                            rooms[line].monster[countMonster][2] = conversion;
                        }
                        else if(parsedLength == 5)
                        {
                            if (parsed[4] == '\n')
                            {
                            conversion = parsed[1] - 48;
                            rooms[line].monster[countMonster][1] = conversion;
                            conversion = parsed[3] - 48;   
                            rooms[line].monster[countMonster][2] = conversion;//conversionTwo + conversion;
                            }
                            else
                            {
                                    conversion = parsed[1] - 48;
                                    rooms[line].monster[countMonster][1] = conversion;
                                    conversion = parsed[3] - 48;   
                                    conversion = conversion * 10;
                                    conversionTwo = parsed[4] - 48;
                                    rooms[line].monster[countMonster][2] = conversionTwo + conversion;                                 
                            }  
                        }
                        else
                        {  
                            conversion = parsed[1] - 48;
                            rooms[line].monster[countMonster][1] = conversion;
                            conversion = parsed[3] - 48;   
                            conversion = conversion * 10;
                            conversionTwo = parsed[4] - 48;
                            rooms[line].monster[countMonster][2] = conversionTwo + conversion;         
                        }
                    }
                    else if (parsed[3]  == ',')
                    {
                        if (parsedLength == 5)
                        {
                            conversion = parsed[1] - 48;
                            conversion = conversion * 10;
                            conversionTwo = parsed[2] - 48;
                            rooms[line].monster[countMonster][1] = conversion + conversionTwo;
                            conversion = parsed[4] - 48;
                            rooms[line].monster[countMonster][2] = conversion;
                        }
                        else if (parsedLength == 6)
                        {
                            if (parsed[5] == '\n')
                            {
                            conversion = parsed[1] - 48;
                            conversion = conversion * 10;
                            conversionTwo = parsed[2] - 48;
                            rooms[line].monster[countMonster][1] = conversion + conversionTwo;
                            conversion = parsed[4] - 48;
                            rooms[line].monster[countMonster][2] = conversion;
                            }
                            else
                            {
                            conversion = parsed[1] - 48;
                            conversion = conversion * 10;
                            conversionTwo = parsed[2] - 48;
                            rooms[line].monster[countMonster][1] = conversion + conversionTwo;
                            conversion = parsed[4] - 48;
                            conversion = conversion * 10;
                            conversionTwo = parsed[5] - 48;
                            rooms[line].monster[countMonster][2] = conversion + conversionTwo;
                            }
                        }
                        else
                        {
                            conversion = parsed[1] - 48;
                            conversion = conversion * 10;
                            conversionTwo = parsed[2] - 48;
                            rooms[line].monster[countMonster][1] = conversion + conversionTwo;
                            conversion = parsed[4] - 48;
                            conversion = conversion * 10;
                            conversionTwo = parsed[5] - 48;
                            rooms[line].monster[countMonster][2] = conversion + conversionTwo;

                        }
                    }
                    else
                    {
                    }
                    countMonster++;
                }
                else if (parsed[0] == 'M')
                {
                    if (parsed[2] == ',')
                    {
                        if (parsedLength == 4)
                        {
                            conversion = parsed[1] - 48;
                            rooms[line].monsterBig[1] = conversion;
                            conversion = parsed[3] - 48;
                            rooms[line].monsterBig[2] = conversion;
                        }
                        else if(parsedLength == 5)
                        {
                            if (parsed[4] == '\n')
                            {
                            conversion = parsed[1] - 48;
                            rooms[line].monsterBig[1] = conversion;
                            conversion = parsed[3] - 48;   
                            rooms[line].monsterBig[2] = conversion;//conversionTwo + conversion;
                            }
                            else
                            {
                                conversion = parsed[1] - 48;
                                rooms[line].monsterBig[1] = conversion;
                                conversion = parsed[3] - 48;   
                                conversion = conversion * 10;
                                conversionTwo = parsed[4] - 48;
                                rooms[line].monsterBig[2] = conversionTwo + conversion;                                 
                            }  
                        }
                        else
                        {  
                            conversion = parsed[1] - 48;
                            rooms[line].monsterBig[1] = conversion;
                            conversion = parsed[3] - 48;   
                            conversion = conversion * 10;
                            conversionTwo = parsed[4] - 48;
                            rooms[line].monsterBig[2] = conversionTwo + conversion;         
                        }
                    }
                    else if (parsed[3]  == ',')
                    {
                        if (parsedLength == 5)
                        {
                            conversion = parsed[1] - 48;
                            conversion = conversion * 10;
                            conversionTwo = parsed[2] - 48;
                            rooms[line].monsterBig[1] = conversion + conversionTwo;
                            conversion = parsed[4] - 48;
                            rooms[line].monsterBig[2] = conversion;
                        }
                        else if (parsedLength == 6)
                        {
                            if (parsed[5] == '\n')
                            {
                                conversion = parsed[1] - 48;
                                conversion = conversion * 10;
                                conversionTwo = parsed[2] - 48;
                                rooms[line].monsterBig[1] = conversion + conversionTwo;
                                conversion = parsed[4] - 48;
                                rooms[line].monsterBig[2] = conversion;
                            }
                            else
                            {
                                conversion = parsed[1] - 48;
                                conversion = conversion * 10;
                                conversionTwo = parsed[2] - 48;
                                rooms[line].monsterBig[1] = conversion + conversionTwo;
                                conversion = parsed[4] - 48;
                                conversion = conversion * 10;
                                conversionTwo = parsed[5] - 48;
                                rooms[line].monsterBig[2] = conversion + conversionTwo;
                            }
                        }
                        else
                        {
                            conversion = parsed[1] - 48;
                            conversion = conversion * 10;
                            conversionTwo = parsed[2] - 48;
                            rooms[line].monsterBig[1] = conversion + conversionTwo;
                            conversion = parsed[4] - 48;
                            conversion = conversion * 10;
                            conversionTwo = parsed[5] - 48;
                            rooms[line].monsterBig[2] = conversion + conversionTwo;

                        }
                    }
                    else
                    {
                    }  
                }
                else if (parsed[0] == 'e')
                {
                    if (parsed[2] == ',')
                    {
                        if (parsedLength == 4)
                        {
                            conversion = parsed[1] - 48;
                            rooms[line].equipment[countEquipment][1] = conversion;
                            conversion = parsed[3] - 48;
                            rooms[line].equipment[countEquipment][2] = conversion;
                        }
                        else if(parsedLength == 5)
                        {
                            if (parsed[4] == '\n')
                            {
                            conversion = parsed[1] - 48;
                            rooms[line].equipment[countEquipment][1] = conversion;
                            conversion = parsed[3] - 48;   
                            rooms[line].equipment[countEquipment][2] = conversion;//conversionTwo + conversion;
                            }
                            else
                            {
                                    conversion = parsed[1] - 48;
                                    rooms[line].equipment[countEquipment][1] = conversion;
                                    conversion = parsed[3] - 48;   
                                    conversion = conversion * 10;
                                    conversionTwo = parsed[4] - 48;
                                    rooms[line].equipment[countEquipment][2] = conversionTwo + conversion;                                 
                            }  
                        }
                        else
                        {  
                            conversion = parsed[1] - 48;
                            rooms[line].equipment[countEquipment][1] = conversion;
                            conversion = parsed[3] - 48;   
                            conversion = conversion * 10;
                            conversionTwo = parsed[4] - 48;
                            rooms[line].equipment[countEquipment][2] = conversionTwo + conversion;         
                        }
                    }
                    else if (parsed[3]  == ',')
                    {
                        if (parsedLength == 5)
                        {
                            conversion = parsed[1] - 48;
                            conversion = conversion * 10;
                            conversionTwo = parsed[2] - 48;
                            rooms[line].equipment[countEquipment][1] = conversion + conversionTwo;
                            conversion = parsed[4] - 48;
                            rooms[line].equipment[countEquipment][2] = conversion;
                        }
                        else if (parsedLength == 6)
                        {
                            if (parsed[5] == '\n')
                            {
                            conversion = parsed[1] - 48;
                            conversion = conversion * 10;
                            conversionTwo = parsed[2] - 48;
                            rooms[line].equipment[countEquipment][1] = conversion + conversionTwo;
                            conversion = parsed[4] - 48;
                            rooms[line].equipment[countEquipment][2] = conversion;
                            }
                            else
                            {
                            conversion = parsed[1] - 48;
                            conversion = conversion * 10;
                            conversionTwo = parsed[2] - 48;
                            rooms[line].equipment[countEquipment][1] = conversion + conversionTwo;
                            conversion = parsed[4] - 48;
                            conversion = conversion * 10;
                            conversionTwo = parsed[5] - 48;
                            rooms[line].equipment[countEquipment][2] = conversion + conversionTwo;
                            }
                        }
                        else
                        {
                            conversion = parsed[1] - 48;
                            conversion = conversion * 10;
                            conversionTwo = parsed[2] - 48;
                            rooms[line].equipment[countEquipment][1] = conversion + conversionTwo;
                            conversion = parsed[4] - 48;
                            conversion = conversion * 10;
                            conversionTwo = parsed[5] - 48;
                            rooms[line].equipment[countEquipment][2] = conversion + conversionTwo;

                        }
                    }
                    else
                    {
                    }
                    countEquipment++;
                }
                else if (parsed[0] == 'p')
                {
                    if (parsed[2] == ',')
                    {
                        if (parsedLength == 4)
                        {
                            conversion = parsed[1] - 48;
                            rooms[line].potion[countPotion][1] = conversion;
                            conversion = parsed[3] - 48;
                            rooms[line].potion[countPotion][2] = conversion;
                        }
                        else if(parsedLength == 5)
                        {
                            if (parsed[4] == '\n')
                            {
                            conversion = parsed[1] - 48;
                            rooms[line].potion[countPotion][1] = conversion;
                            conversion = parsed[3] - 48;   
                            rooms[line].potion[countPotion][2] = conversion;//conversionTwo + conversion;
                            }
                            else
                            {
                                    conversion = parsed[1] - 48;
                                    rooms[line].potion[countPotion][1] = conversion;
                                    conversion = parsed[3] - 48;   
                                    conversion = conversion * 10;
                                    conversionTwo = parsed[4] - 48;
                                    rooms[line].potion[countPotion][2] = conversionTwo + conversion;                                 
                            }  
                        }
                        else
                        {  
                            conversion = parsed[1] - 48;
                            rooms[line].potion[countPotion][1] = conversion;
                            conversion = parsed[3] - 48;   
                            conversion = conversion * 10;
                            conversionTwo = parsed[4] - 48;
                            rooms[line].potion[countPotion][2] = conversionTwo + conversion;         
                        }
                    }
                    else if (parsed[3]  == ',')
                    {
                        if (parsedLength == 5)
                        {
                            conversion = parsed[1] - 48;
                            conversion = conversion * 10;
                            conversionTwo = parsed[2] - 48;
                            rooms[line].potion[countPotion][1] = conversion + conversionTwo;
                            conversion = parsed[4] - 48;
                            rooms[line].potion[countPotion][2] = conversion;
                        }
                        else if (parsedLength == 6)
                        {
                            if (parsed[5] == '\n')
                            {
                            conversion = parsed[1] - 48;
                            conversion = conversion * 10;
                            conversionTwo = parsed[2] - 48;
                            rooms[line].potion[countPotion][1] = conversion + conversionTwo;
                            conversion = parsed[4] - 48;
                            rooms[line].potion[countPotion][2] = conversion;
                            }
                            else
                            {
                            conversion = parsed[1] - 48;
                            conversion = conversion * 10;
                            conversionTwo = parsed[2] - 48;
                            rooms[line].potion[countPotion][1] = conversion + conversionTwo;
                            conversion = parsed[4] - 48;
                            conversion = conversion * 10;
                            conversionTwo = parsed[5] - 48;
                            rooms[line].potion[countPotion][2] = conversion + conversionTwo;
                            }
                        }
                        else
                        {
                            conversion = parsed[1] - 48;
                            conversion = conversion * 10;
                            conversionTwo = parsed[2] - 48;
                            rooms[line].potion[countPotion][1] = conversion + conversionTwo;
                            conversion = parsed[4] - 48;
                            conversion = conversion * 10;
                            conversionTwo = parsed[5] - 48;
                            rooms[line].potion[countPotion][2] = conversion + conversionTwo;

                        }
                    }
                    else
                    {
                    }
                    countPotion++;
                }
                else if (parsed[0] == 'w')
                {
                    if (parsed[2] == ',')
                    {
                        if (parsedLength == 4)
                        {
                            conversion = parsed[1] - 48;
                            rooms[line].weapon[countWeapon][1] = conversion;
                            conversion = parsed[3] - 48;
                            rooms[line].weapon[countWeapon][2] = conversion;
                        }
                        else if(parsedLength == 5)
                        {
                            if (parsed[4] == '\n')
                            {
                            conversion = parsed[1] - 48;
                            rooms[line].weapon[countWeapon][1] = conversion;
                            conversion = parsed[3] - 48;   
                            rooms[line].weapon[countWeapon][2] = conversion;//conversionTwo + conversion;
                            }
                            else
                            {
                                    conversion = parsed[1] - 48;
                                    rooms[line].weapon[countWeapon][1] = conversion;
                                    conversion = parsed[3] - 48;   
                                    conversion = conversion * 10;
                                    conversionTwo = parsed[4] - 48;
                                    rooms[line].weapon[countWeapon][2] = conversionTwo + conversion;                                 
                            }  
                        }
                        else
                        {  
                            conversion = parsed[1] - 48;
                            rooms[line].weapon[countWeapon][1] = conversion;
                            conversion = parsed[3] - 48;   
                            conversion = conversion * 10;
                            conversionTwo = parsed[4] - 48;
                            rooms[line].weapon[countWeapon][2] = conversionTwo + conversion;         
                        }
                    }
                    else if (parsed[3]  == ',')
                    {
                        if (parsedLength == 5)
                        {
                            conversion = parsed[1] - 48;
                            conversion = conversion * 10;
                            conversionTwo = parsed[2] - 48;
                            rooms[line].weapon[countWeapon][1] = conversion + conversionTwo;
                            conversion = parsed[4] - 48;
                            rooms[line].weapon[countWeapon][2] = conversion;
                        }
                        else if (parsedLength == 6)
                        {
                            if (parsed[5] == '\n')
                            {
                            conversion = parsed[1] - 48;
                            conversion = conversion * 10;
                            conversionTwo = parsed[2] - 48;
                            rooms[line].weapon[countWeapon][1] = conversion + conversionTwo;
                            conversion = parsed[4] - 48;
                            rooms[line].weapon[countWeapon][2] = conversion;
                            }
                            else
                            {
                            conversion = parsed[1] - 48;
                            conversion = conversion * 10;
                            conversionTwo = parsed[2] - 48;
                            rooms[line].weapon[countWeapon][1] = conversion + conversionTwo;
                            conversion = parsed[4] - 48;
                            conversion = conversion * 10;
                            conversionTwo = parsed[5] - 48;
                            rooms[line].weapon[countWeapon][2] = conversion + conversionTwo;
                            }
                        }
                        else
                        {
                            conversion = parsed[1] - 48;
                            conversion = conversion * 10;
                            conversionTwo = parsed[2] - 48;
                            rooms[line].weapon[countWeapon][1] = conversion + conversionTwo;
                            conversion = parsed[4] - 48;
                            conversion = conversion * 10;
                            conversionTwo = parsed[5] - 48;
                            rooms[line].weapon[countWeapon][2] = conversion + conversionTwo;

                        }
                    }
                    else
                    {
                    }
                    countWeapon++;
                } 
                else if (parsed[0] == 'W')
                {
                    if (parsed[2] == ',')
                    {
                        if (parsedLength == 4)
                        {
                            conversion = parsed[1] - 48;
                            rooms[line].weaponRare[1] = conversion;
                            conversion = parsed[3] - 48;
                            rooms[line].weaponRare[2] = conversion;
                        }
                        else if(parsedLength == 5)
                        {
                            if (parsed[4] == '\n')
                            {
                            conversion = parsed[1] - 48;
                            rooms[line].weaponRare[1] = conversion;
                            conversion = parsed[3] - 48;   
                            rooms[line].weaponRare[2] = conversion;//conversionTwo + conversion;
                            }
                            else
                            {
                                conversion = parsed[1] - 48;
                                rooms[line].weaponRare[1] = conversion;
                                conversion = parsed[3] - 48;   
                                conversion = conversion * 10;
                                conversionTwo = parsed[4] - 48;
                                rooms[line].weaponRare[2] = conversionTwo + conversion;                                 
                            }  
                        }
                        else
                        {  
                            conversion = parsed[1] - 48;
                            rooms[line].weaponRare[1] = conversion;
                            conversion = parsed[3] - 48;   
                            conversion = conversion * 10;
                            conversionTwo = parsed[4] - 48;
                            rooms[line].weaponRare[2] = conversionTwo + conversion;         
                        }
                    }
                    else if (parsed[3]  == ',')
                    {
                        if (parsedLength == 5)
                        {
                            conversion = parsed[1] - 48;
                            conversion = conversion * 10;
                            conversionTwo = parsed[2] - 48;
                            rooms[line].weaponRare[1] = conversion + conversionTwo;
                            conversion = parsed[4] - 48;
                            rooms[line].weaponRare[2] = conversion;
                        }
                        else if (parsedLength == 6)
                        {
                            if (parsed[5] == '\n')
                            {
                                conversion = parsed[1] - 48;
                                conversion = conversion * 10;
                                conversionTwo = parsed[2] - 48;
                                rooms[line].weaponRare[1] = conversion + conversionTwo;
                                conversion = parsed[4] - 48;
                                rooms[line].weaponRare[2] = conversion;
                            }
                            else
                            {
                                conversion = parsed[1] - 48;
                                conversion = conversion * 10;
                                conversionTwo = parsed[2] - 48;
                                rooms[line].weaponRare[1] = conversion + conversionTwo;
                                conversion = parsed[4] - 48;
                                conversion = conversion * 10;
                                conversionTwo = parsed[5] - 48;
                                rooms[line].weaponRare[2] = conversion + conversionTwo;
                            }
                        }
                        else
                        {
                            conversion = parsed[1] - 48;
                            conversion = conversion * 10;
                            conversionTwo = parsed[2] - 48;
                            rooms[line].weaponRare[1] = conversion + conversionTwo;
                            conversion = parsed[4] - 48;
                            conversion = conversion * 10;
                            conversionTwo = parsed[5] - 48;
                            rooms[line].weaponRare[2] = conversion + conversionTwo;

                        }
                    }
                    else
                    {
                    }  
                } 
                else if (parsed[0] == 'h')
                {
                    if (parsed[2] == ',')
                    {
                        if (parsedLength == 4)
                        {
                            conversion = parsed[1] - 48;
                            rooms[line].hero[1] = conversion;
                            conversion = parsed[3] - 48;
                            rooms[line].hero[2] = conversion;
                        }
                        else if(parsedLength == 5)
                        {
                            if (parsed[4] == '\n')
                            {
                            conversion = parsed[1] - 48;
                            rooms[line].hero[1] = conversion;
                            conversion = parsed[3] - 48;   
                            rooms[line].hero[2] = conversion;//conversionTwo + conversion;
                            }
                            else
                            {
                                conversion = parsed[1] - 48;
                                rooms[line].hero[1] = conversion;
                                conversion = parsed[3] - 48;   
                                conversion = conversion * 10;
                                conversionTwo = parsed[4] - 48;
                                rooms[line].hero[2] = conversionTwo + conversion;                                 
                            }  
                        }
                        else
                        {  
                            conversion = parsed[1] - 48;
                            rooms[line].hero[1] = conversion;
                            conversion = parsed[3] - 48;   
                            conversion = conversion * 10;
                            conversionTwo = parsed[4] - 48;
                            rooms[line].hero[2] = conversionTwo + conversion;         
                        }
                    }
                    else if (parsed[3]  == ',')
                    {
                        if (parsedLength == 5)
                        {
                            conversion = parsed[1] - 48;
                            conversion = conversion * 10;
                            conversionTwo = parsed[2] - 48;
                            rooms[line].hero[1] = conversion + conversionTwo;
                            conversion = parsed[4] - 48;
                            rooms[line].hero[2] = conversion;
                        }
                        else if (parsedLength == 6)
                        {
                            if (parsed[5] == '\n')
                            {
                                conversion = parsed[1] - 48;
                                conversion = conversion * 10;
                                conversionTwo = parsed[2] - 48;
                                rooms[line].hero[1] = conversion + conversionTwo;
                                conversion = parsed[4] - 48;
                                rooms[line].hero[2] = conversion;
                            }
                            else
                            {
                                conversion = parsed[1] - 48;
                                conversion = conversion * 10;
                                conversionTwo = parsed[2] - 48;
                                rooms[line].hero[1] = conversion + conversionTwo;
                                conversion = parsed[4] - 48;
                                conversion = conversion * 10;
                                conversionTwo = parsed[5] - 48;
                                rooms[line].hero[2] = conversion + conversionTwo;
                            }
                        }
                        else
                        {
                            conversion = parsed[1] - 48;
                            conversion = conversion * 10;
                            conversionTwo = parsed[2] - 48;
                            rooms[line].hero[1] = conversion + conversionTwo;
                            conversion = parsed[4] - 48;
                            conversion = conversion * 10;
                            conversionTwo = parsed[5] - 48;
                            rooms[line].hero[2] = conversion + conversionTwo;

                        }
                    }
                    else
                    {
                    }  
                }
                else if (parsed[0] == 'z')
                {
                    if (parsed[2] == ',')
                    {
                        if (parsedLength == 4)
                        {
                            conversion = parsed[1] - 48;
                            rooms[line].stairsDown[countStairsDown][1] = conversion;
                            conversion = parsed[3] - 48;
                            rooms[line].stairsDown[countStairsDown][2] = conversion;
                        }
                        else if(parsedLength == 5)
                        {
                            if (parsed[4] == '\n')
                            {
                            conversion = parsed[1] - 48;
                            rooms[line].stairsDown[countStairsDown][1] = conversion;
                            conversion = parsed[3] - 48;   
                            rooms[line].stairsDown[countStairsDown][2] = conversion;//conversionTwo + conversion;
                            }
                            else
                            {
                                    conversion = parsed[1] - 48;
                                    rooms[line].stairsDown[countStairsDown][1] = conversion;
                                    conversion = parsed[3] - 48;   
                                    conversion = conversion * 10;
                                    conversionTwo = parsed[4] - 48;
                                    rooms[line].stairsDown[countStairsDown][2] = conversionTwo + conversion;                                 
                            }  
                        }
                        else
                        {  
                            conversion = parsed[1] - 48;
                            rooms[line].stairsDown[countStairsDown][1] = conversion;
                            conversion = parsed[3] - 48;   
                            conversion = conversion * 10;
                            conversionTwo = parsed[4] - 48;
                            rooms[line].stairsDown[countStairsDown][2] = conversionTwo + conversion;         
                        }
                    }
                    else if (parsed[3]  == ',')
                    {
                        if (parsedLength == 5)
                        {
                            conversion = parsed[1] - 48;
                            conversion = conversion * 10;
                            conversionTwo = parsed[2] - 48;
                            rooms[line].stairsDown[countStairsDown][1] = conversion + conversionTwo;
                            conversion = parsed[4] - 48;
                            rooms[line].stairsDown[countStairsDown][2] = conversion;
                        }
                        else if (parsedLength == 6)
                        {
                            if (parsed[5] == '\n')
                            {
                            conversion = parsed[1] - 48;
                            conversion = conversion * 10;
                            conversionTwo = parsed[2] - 48;
                            rooms[line].stairsDown[countStairsDown][1] = conversion + conversionTwo;
                            conversion = parsed[4] - 48;
                            rooms[line].stairsDown[countStairsDown][2] = conversion;
                            }
                            else
                            {
                            conversion = parsed[1] - 48;
                            conversion = conversion * 10;
                            conversionTwo = parsed[2] - 48;
                            rooms[line].stairsDown[countStairsDown][1] = conversion + conversionTwo;
                            conversion = parsed[4] - 48;
                            conversion = conversion * 10;
                            conversionTwo = parsed[5] - 48;
                            rooms[line].stairsDown[countStairsDown][2] = conversion + conversionTwo;
                            }
                        }
                        else
                        {
                            conversion = parsed[1] - 48;
                            conversion = conversion * 10;
                            conversionTwo = parsed[2] - 48;
                            rooms[line].stairsDown[countStairsDown][1] = conversion + conversionTwo;
                            conversion = parsed[4] - 48;
                            conversion = conversion * 10;
                            conversionTwo = parsed[5] - 48;
                            rooms[line].stairsDown[countStairsDown][2] = conversion + conversionTwo;

                        }
                    }
                    else
                    {
                    }
                    countStairsDown++;
                }
                else if (parsed[0] == 'a')
                {
                    if (parsed[2] == ',')
                    {
                        if (parsedLength == 4)
                        {
                            conversion = parsed[1] - 48;
                            rooms[line].stairsUp[countStairsUp][1] = conversion;
                            conversion = parsed[3] - 48;
                            rooms[line].stairsUp[countStairsUp][2] = conversion;
                        }
                        else if(parsedLength == 5)
                        {
                            if (parsed[4] == '\n')
                            {
                            conversion = parsed[1] - 48;
                            rooms[line].stairsUp[countStairsUp][1] = conversion;
                            conversion = parsed[3] - 48;   
                            rooms[line].stairsUp[countStairsUp][2] = conversion;//conversionTwo + conversion;
                            }
                            else
                            {
                                    conversion = parsed[1] - 48;
                                    rooms[line].stairsUp[countStairsUp][1] = conversion;
                                    conversion = parsed[3] - 48;   
                                    conversion = conversion * 10;
                                    conversionTwo = parsed[4] - 48;
                                    rooms[line].stairsUp[countStairsUp][2] = conversionTwo + conversion;                                 
                            }  
                        }
                        else
                        {  
                            conversion = parsed[1] - 48;
                            rooms[line].stairsUp[countStairsUp][1] = conversion;
                            conversion = parsed[3] - 48;   
                            conversion = conversion * 10;
                            conversionTwo = parsed[4] - 48;
                            rooms[line].stairsUp[countStairsUp][2] = conversionTwo + conversion;         
                        }
                    }
                    else if (parsed[3]  == ',')
                    {
                        if (parsedLength == 5)
                        {
                            conversion = parsed[1] - 48;
                            conversion = conversion * 10;
                            conversionTwo = parsed[2] - 48;
                            rooms[line].stairsUp[countStairsUp][1] = conversion + conversionTwo;
                            conversion = parsed[4] - 48;
                            rooms[line].stairsUp[countStairsUp][2] = conversion;
                        }
                        else if (parsedLength == 6)
                        {
                            if (parsed[5] == '\n')
                            {
                            conversion = parsed[1] - 48;
                            conversion = conversion * 10;
                            conversionTwo = parsed[2] - 48;
                            rooms[line].stairsUp[countStairsUp][1] = conversion + conversionTwo;
                            conversion = parsed[4] - 48;
                            rooms[line].stairsUp[countStairsUp][2] = conversion;
                            }
                            else
                            {
                            conversion = parsed[1] - 48;
                            conversion = conversion * 10;
                            conversionTwo = parsed[2] - 48;
                            rooms[line].stairsUp[countStairsUp][1] = conversion + conversionTwo;
                            conversion = parsed[4] - 48;
                            conversion = conversion * 10;
                            conversionTwo = parsed[5] - 48;
                            rooms[line].stairsUp[countStairsUp][2] = conversion + conversionTwo;
                            }
                        }
                        else
                        {
                            conversion = parsed[1] - 48;
                            conversion = conversion * 10;
                            conversionTwo = parsed[2] - 48;
                            rooms[line].stairsUp[countStairsUp][1] = conversion + conversionTwo;
                            conversion = parsed[4] - 48;
                            conversion = conversion * 10;
                            conversionTwo = parsed[5] - 48;
                            rooms[line].stairsUp[countStairsUp][2] = conversion + conversionTwo;

                        }
                    }
                    else
                    {
                    }
                    countStairsUp++;
                }
            }
        }
        refresh();
        counter = 0; //restart counterS at beginning of new line
        countGold = 1;
        countStairsDown = 1;
        countStairsUp = 1;
        countWeapon = 1;
        countEquipment = 1;
        countPotion = 1;
        countMonster = 1;
    }
    return rooms;//return structs of rooms
}
