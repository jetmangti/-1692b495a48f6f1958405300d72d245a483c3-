#ifndef CELL_H
#define CELL_H
#include "enumm.h"
#include "runnable.h"
#include <vector>
using namespace std;
/***********************************************************************************7
 * Martin Hlipala xhlipa00
 * Adam Bak xbakad00
 *
 * All rights reserved
 *
*/
class Cell
{
private:
    bool isFreezed; //isFreezed flag
    int x;  // x coord
    int y;  // y coord
    int posX; // posX X coord used in GUI
    int posY;   // posY Y coord used in GUI
    int price=0; // value used by AI
    vector<enum Team> history; // stack used for undo action
public:
    enum Team lastTeam; // last team cell was belonging to
    enum Team team; // actual team cell belongs to
    Cell(int, int, int, int, int); // constructor
    void resetHistory(); //...
    void recordStatus(); //make "snapshot" of actual team belonging of actual cell
    void setWhite(); //...
    void setBlack(); //...
    void setFreezed();//...
    bool getFreezed();//checks if Cell is freezed
    void unsetFreezed(); // unfreeze
    void setGhost();// not used
    void setBlank();//makes cell empty  witho no team belonging
    void undo();// undo
    void swapTeam(bool); //change team of cell (from white to black or vice versa)
    enum Team getTeam(); //returns actual cell team
    void setTeam(int); //sets cell team
    bool getTeamBool(); // gets actual cell team returned as bool (true black false white)
    int getXPos(); // get ui x pos
    int getYPos(); // get ui y pos
    void setPrice(int); //sets value used by AI
    int getPrice(); // returns value stored for AI
};

#endif // CELL_H
