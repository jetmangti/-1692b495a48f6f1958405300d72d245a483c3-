#include "ai2.h"


AI2::AI2(CellFinder* cf,GameController* gc,int size,int team,vector< vector< Cell*>>* matrix)
{
    this->gc = gc;
    this->cf = cf;
    this->team = team;
}
bool AI2::getTeam()
{
    if(team == 0)
        {
            return true;
        }
    else
        {
            return false;
        }
}
int AI2::getPriceModifier(int a, int b)
{
    return 1;
}

Cell* AI2::doJob()
{
    vector<Cell*>* st;
    Cell* max;
    int maxPrice;

    this->cf->resetEmpty();
    this->cf->setPadsVisibility(false);
    if( this->cf->recalculateAndMark(this->team)==0)
    {
        return NULL;
    }
    st = this->cf->getCellList();
    if(!st->empty())
    {
        max = st->back();
        maxPrice = max->getPrice();
        for(Cell* choice: (*st))
        {
            if(choice->getPrice() > maxPrice)
            {
                maxPrice = choice->getPrice();
                max = choice;
            }
           /// System.out.print(choice.getPrice()+" : ");
        }
       /// System.out.println("SELECTED: "+max.getPrice());
       /// System.out.println("DONE");
        this->gc->placeStone(max);
        //cf.turnStones(max.getXPos(),max.getYPos(),gc.getActualPlayer());
        //gc.changeTeam();
        if(this->last!=NULL)
        {
            ///AIPlay1->last->setBackground(Color.white);
        }
        this->last = max;
        ///max->setBackground(Color->magenta);
        return max;
    }
    else
    {
        //System.out.println("EMPTY STACK");
        return new Cell(-1,-1,-1,-1,-1);
    }
}
