#include "cell.h"

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
    else
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
    else
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
void Cell::recordStatus()
{
    if(this->team == BLACK)
    {
        this->history.push_back(BLACK);
    }
    else if(this->team == WHITE)
    {
        this->history.push_back(WHITE);
    }
    else
    {
        this->history.push_back(EMPTY);
    }

}
void Cell::undo()
{
    if(!this->history.empty())
    {
        this->team = this->history.back();
        this->history.pop_back();
    }
}

void Cell::swapTeam(bool team)
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
enum Team Cell::getTeam()
{
   return this->team;
}
bool Cell::getTeamBool()
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
int Cell::getXPos()
{
    return this->x;
}
int Cell::getYPos()
{
    return this->y;
}
void Cell::setPrice(int price)
{
    this->price = price;
}
int Cell::getPrice()
{
    return this->price;
}
