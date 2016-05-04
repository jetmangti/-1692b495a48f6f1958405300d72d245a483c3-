#ifndef AI2_H
#define AI2_H

#include "includes.h"
#include "cellfinder.h"
#include "gamecontroller.h"
#include "aiselector.h"
using namespace std;

class AI2 : public AISelector
{
private:
    int team;
    Cell* last;
    CellFinder* cf;
    GameController* gc;
    vector< vector< int>> tactic;
public:
    AI2(CellFinder*,GameController*,int,int,vector<vector<Cell*>>*);
    bool getTeam();
    int getPriceModifier(int,int);
    Cell* doJob();
};

#endif // AI2_H
