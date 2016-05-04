#ifndef CELL_H
#define CELL_H
#include "enumm.h"
#include "runnable.h"
#include <vector>
using namespace std;

class Cell
{
private:
    bool isFreezed;
    int x;
    int y;
    int posX;
    int posY;
    int price=0;
    vector<enum Team> history;
public:
    enum Team lastTeam;
    enum Team team;
    Cell(int, int, int, int, int);
    void resetHistory();
    void recordStatus();
    void setWhite();
    void setBlack();
    void setFreezed();
    bool getFreezed();
    void unsetFreezed();
    void setGhost();
    void setBlank();
    void undo();
    void swapTeam(bool);
    enum Team getTeam();
    void setTeam(int);
    bool getTeamBool();
    int getXPos();
    int getYPos();
    void setPrice(int);
    int getPrice();
};

#endif // CELL_H
