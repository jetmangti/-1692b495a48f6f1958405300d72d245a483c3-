#include "ai2.h"

/***********************************************************************************7
 * Martin Hlipala xhlipa00
 * Adam Bak xbakad00
 *
 * All rights reserved
 *
*/

AI2::AI2(CellFinder* cf,GameController* gc,int size,int team,vector< vector< Cell*>>* matrix) //construct AI2 object
{
    this->gc = gc;
    this->cf = cf;
    this->team = team;
}
bool AI2::getTeam() //utility function
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
int AI2::getPriceModifier(int a, int b) // return price modifier (in this case its constant 1, for AI1 its something else
{
    return 1;
}

Cell* AI2::doJob()  //AI routine
{
    vector<Cell*>* st;
    Cell* max;
    int maxPrice;


    this->cf->setPadsVisibility(false);
    st = this->cf->getCellList();
    if(!st->empty())    //if some steps are possible
    {
        max = st->back();   //find the best solution according to heuristics
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
        this->gc->placeStone(max); // take the best and use it
        //cf.turnStones(max.getXPos(),max.getYPos(),gc.getActualPlayer());
        //gc.changeTeam();
        if(this->last!=NULL)
        {
            ///AIPlay1->last->setBackground(Color.white);
        }
        this->last = max; //save last solution
        ///max->setBackground(Color->magenta);
        return max; //return it to the main body
    }
    else
    {
        //System.out.println("EMPTY STACK");
        //return new Cell(-1,-1,-1,-1,-1);
        return NULL; // return NULL - no possible solution found
    }
}
