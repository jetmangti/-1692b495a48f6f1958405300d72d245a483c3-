#ifndef AISELECTOR_H
#define AISELECTOR_H

#include "cell.h"

class AISelector
{
private:

public:
    virtual bool getTeam();
    virtual int getPriceModifier(int,int);
    virtual Cell* doJob();
};

#endif // AISELECTOR_H
