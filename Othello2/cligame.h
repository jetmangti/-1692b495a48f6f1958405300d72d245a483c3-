#ifndef CLIGAME_H
#define CLIGAME_H

#include "game.h"
#include "cellfinder.h"
#include "gamecontroller.h"
#include "gamesetting.h"
#include "aiselector.h"
/***********************************************************************************7
 * Martin Hlipala xhlipa00
 * Adam Bak xbakad00
 *
 * All rights reserved
 *
*/

class cliGame
{
private:
    Game* game;
    GameSetting* gs;
    vector< vector< bool>>* selectionPads;
    vector< vector< Cell*>>* board;

public:
    cliGame();
    void render();
    void run();
};

#endif // CLIGAME_H
