#ifndef AISELECTOR_H
#define AISELECTOR_H
/***********************************************************************************7
 * Martin Hlipala xhlipa00
 * Adam Bak xbakad00
 *
 * All rights reserved
 *
*/
#include "cell.h"
//not used yet
class AISelector
{
private:

public:
    virtual bool getTeam();
    virtual int getPriceModifier(int,int);
    virtual Cell* doJob();
};

#endif // AISELECTOR_H
