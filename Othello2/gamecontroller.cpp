#include "gamecontroller.h"
/***********************************************************************************7
 * Martin Hlipala xhlipa00
 * Adam Bak xbakad00
 *
 * All rights reserved
 *
*/
GameController::GameController()
{
    this->player = true;
    this->scoreBlack = 2;
    this->scoreWhite = 2;
}
bool GameController::getActualPlayer() // get actual player
{
    bool player;
    player = this->player;
    this->player = !this->player;
    return player;
}
int GameController::getTeamID() //get actual team id
{
    if(this->player==true)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}
void GameController::changeTeam() // change team
{
    this->player = !this->player;
}
void GameController::setTeamID(int id) //set teamId (used for init)
{
    if(id == 0)
    {
        this->player = true;
    }
    else
    {
        this->player = false;
    }
}

void GameController::removeStone(Cell* btn) //removeStone from board
{
    btn->setBlank();
}
void GameController::placeStone(Cell* btn) //place stone to board
{
    ///this.undo.push(
    /*		new Runnable()
            {
                public void run()
                {
                    removeStone(btn);
                }
            }
            );*/
    if(!this->player)
    {
        btn->setBlack();
    }
    else
    {
        btn->setWhite();
    }
}
