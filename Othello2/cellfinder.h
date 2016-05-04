#ifndef CELLFINDER_H
#define CELLFINDER_H
#include "includes.h"
#include "cell.h"

using namespace std;
class CellFinder
{
private:
    vector <Cell*> st;
    vector <Cell*> lastState;
    int size;
    vector <vector <Cell*>>* matrix;
    int priceCounter = 0;
    bool visibility = true;
    int counter=0;
public:
    CellFinder();
    CellFinder(int,vector<vector<Cell *>>*);
    Cell* getNextCell(int,int,int);
    void rayCast(int,int,int);
    void clearStack();
    vector<Cell*>* getCellList();
    void resetEmpty();
    void hidePads();
    void resetEmptyAll();
    int recalculateAndMark(int);
    void setPadsVisibility(bool);
    void turnStones(int,int,bool);

};

#endif // CELLFINDER_H
