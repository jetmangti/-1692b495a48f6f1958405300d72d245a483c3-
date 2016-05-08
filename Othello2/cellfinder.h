#ifndef CELLFINDER_H
#define CELLFINDER_H
#include "includes.h"
#include "cell.h"

/***********************************************************************************7
 * Martin Hlipala xhlipa00
 * Adam Bak xbakad00
 *
 * All rights reserved
 *
*/

//class declaration, description of each function is stored in cpp file
using namespace std;
class CellFinder
{
private:
    vector <Cell*> st;  //vector of pointers to cell objects
    vector <Cell*> lastState;   // the same as st, but used for back check
    int size;   // size of game
    vector <vector <Cell*>>* matrix; //pointer to game board
    int priceCounter = 0;   // used to compute value used by AI
    int counter=0; //utility counter
public:
     bool visibility = true; // visibility flag
    CellFinder();
    CellFinder(int,vector<vector<Cell *>>*);
    Cell* getNextCell(int,int,int);
    int rayCast(int,int,int);
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
