#include "gamecontroller.h"

GameController::GameController()
{
    this->player = true;
    this->scoreBlack = 2;
    this->scoreWhite = 2;
}
bool GameController::getActualPlayer()
{
    bool player;
    player = this->player;
    this->player = !this->player;
    return player;
}
int GameController::getTeamID()
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
void GameController::changeTeam()
{
    this->player = !this->player;
}
void GameController::setTeamID(int id)
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

void GameController::removeStone(Cell* btn)
{
    btn->setBlank();
}
void GameController::placeStone(Cell* btn)
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
