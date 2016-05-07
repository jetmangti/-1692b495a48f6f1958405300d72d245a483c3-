#include "cell.h"
/***********************************************************************************7
 * Martin Hlipala xhlipa00
 * Adam Bak xbakad00
 *
 * All rights reserved
 *
*/
Cell::Cell(int size,int x, int y, int posX, int posY)       //build it
{
    this->x = x;
    this->y = y;
    this->posX = posX;
    this->posY = posY;
    this->team = EMPTY;
}
void Cell::setWhite()           //set white
{
    this->team = WHITE;
}
void Cell::setTeam(int team)
{
    this->team = static_cast<Team>(team);
}
void Cell::setBlack()           //set black
{
    this->team = BLACK;
}
void Cell::setFreezed()         //freeze the pawn
{
    this->isFreezed = true;
    if(this->team == BLACK)
    {
        this->team=BLACK_FR;
    }
    else  if(this->team ==WHITE)
    {
        this->team=WHITE_FR;
    }
}
void Cell::unsetFreezed()       //unfreeze the pawn
{
    this->isFreezed = false;
    if(this->team == BLACK_FR)
    {
        this->team=BLACK;
    }
    else if(this->team == WHITE_FR)
    {
        this->team=WHITE;
    }
}
void Cell::setBlank()           //set no team
{
    this->team = EMPTY;
}
bool Cell::getFreezed()               //is pawn freezed ?
{
    return this->isFreezed;
}
void Cell::resetHistory()
{
    this->history.clear();
}
void Cell::recordStatus()   // store actual team to history stack
{
    if(this->team == BLACK)
    {
        this->history.push_back(BLACK);
    }
    else if(this->team == WHITE)
    {
        this->history.push_back(WHITE);
    }
    else if(this->team == WHITE_FR)
    {
        this->history.push_back(WHITE);
    }
    else if(this->team == BLACK_FR)
    {
        this->history.push_back(BLACK);
    }
    else
    {
        this->history.push_back(EMPTY);
    }


}
void Cell::undo()   // pop one from the history, and set the team that is on the peak
{
    if(!this->history.empty())
    {
        this->team = this->history.back();
        this->history.pop_back();
    }
}

void Cell::swapTeam(bool team)  // swap between teams
{
    if(team)
    {
        this->setBlack();
    }
    else
    {
        this->setWhite();
    }
}
enum Team Cell::getTeam()   //...
{
   return this->team;
}
bool Cell::getTeamBool() // returns team as boolean, true-white false-black
{
    if(this->team==WHITE)
    {
        return true;
    }
    else
    {
        return false;
    }
}
int Cell::getXPos() // get x coord
{
    return this->x;
}
int Cell::getYPos() // get y coord
{
    return this->y;
}
void Cell::setPrice(int price) // set value used by AI
{
    this->price = price;
}
int Cell::getPrice() // returns value used by AI
{
    return this->price;
}
