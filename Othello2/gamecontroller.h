#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "includes.h"
#include "cell.h"
/***********************************************************************************7
 * Martin Hlipala xhlipa00
 * Adam Bak xbakad00
 *
 * All rights reserved
 *
*/
//description in cpp file
class GameController
{
private:
    bool player; //false = black true = white;
    bool human;
    int scoreBlack;
    int scoreWhite;
public:
    GameController();
    bool getActualPlayer();
    int getTeamID();
    void setActualPlayer();
    void setTeamID(int);
    void changeTeam();
    void removeStone(Cell* btn);
    void placeStone(Cell* btn);
};

#endif // GAMECONTROLLER_H
