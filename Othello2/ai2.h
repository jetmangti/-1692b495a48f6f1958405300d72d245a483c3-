#ifndef AI2_H
#define AI2_H
/***********************************************************************************7
 * Martin Hlipala xhlipa00
 * Adam Bak xbakad00
 *
 * All rights reserved
 *
*/
#include "includes.h"
#include "cellfinder.h"
#include "gamecontroller.h"
#include "aiselector.h"
using namespace std;

class AI2 : public AISelector
{
private:
    int team;   //team id
    Cell* last; //last cell pointer
    CellFinder* cf; //cell finder pointer
    GameController* gc; //game controller pointer
    vector< vector< int>> tactic; // vector for tactic computing
    vector<Cell*>* st; // vector of possible placements
public:
    AI2(CellFinder*,GameController*,int,int,vector<vector<Cell*>>*); // AI2 constructor
    bool getTeam(); // get team utility returns in bool
    int getPriceModifier(int,int); // compute price of the cell
    Cell* doJob();// ai routine
};

#endif // AI2_H
