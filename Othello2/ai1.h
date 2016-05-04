#ifndef AI1_H
#define AI1_H

#include "includes.h"
#include "cellfinder.h"
#include "gamecontroller.h"
#include "aiselector.h"
using namespace std;

class AI1 : public AISelector
{
private:
    int team;
    Cell* last;
    CellFinder* cf;
    GameController* gc;
    vector< vector< int>> tactic;
public:
    AI1(CellFinder*,GameController*,int,int,vector<vector<Cell*>>*);
    bool getTeam();
    int getPriceModifier(int,int);
    Cell* doJob();
};

#endif // AI1_H
