#ifndef AI1_H
#define AI1_H
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

class AI1 : public AISelector
{
private:
    int team;   //team id
    Cell* last; //last cell pointer
    CellFinder* cf; //cell finder pointer
    GameController* gc; //game controller pointer
    vector< vector< int>> tactic; // vector for tactic computing
    vector<Cell*>* st; // vector of possible placements
public:
    AI1(CellFinder*,GameController*,int,int,vector<vector<Cell*>>*); //AI1 constructor
    bool getTeam(); // get team utility returns in bool
    int getPriceModifier(int,int); // compute price of the cell
    Cell* doJob();// ai routine
};

#endif // AI1_H
