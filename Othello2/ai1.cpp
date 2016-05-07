#include "ai1.h"
/***********************************************************************************7
 * Martin Hlipala xhlipa00
 * Adam Bak xbakad00
 *
 * All rights reserved
 *
*/

AI1::AI1(CellFinder* cf,GameController* gc,int size,int team,vector< vector< Cell*>>* matrix) //AI1 constructor
{
    this->gc = gc;
    this->cf = cf;
    st = this->cf->getCellList();
    this->team = team;
    this->tactic.resize((size), vector<int>(size));
    for(int i=0; i<size; i++)       //compute tactic values (based on real life tactics developed by real othello players)
    {
        for(int j=0; j<size; j++)
        {
            if((i==0 || i==1))
            {
                this->tactic[i][j] = 75;
            }
            else if(j==0 || j==1)
            {
                 this->tactic[i][j] = 75;
            }
            else if((i==size-1 || i==size-2))
            {
                 this->tactic[i][j] = 75;
            }
            else if((j==size-1 || j==size-2))
            {
                 this->tactic[i][j] = 75;
            }
            else
            {
                 this->tactic[i][j] = 100;
            }
            if((i==0 && j==0)||(i==size-1 &&j==size-1)||(i==0 && j==size-1)||(i==size-1 && j==0))
            {
                 this->tactic[i][j] = 100;
            }
            if((i==2 && j==0)||(i==size-3 &&j==size-1)||(i==2 && j==size-1)||(i==size-1 && j==size-3)||(i==size-1 && j==2)||(i==0 && j==2)||(i==0 && j==size-3)||(i==size-3 && j==0))
            {
                 this->tactic[i][j] = 100;
            }
            if((i==1 && j==1)||(i==size-2 && j==size-2)||(i==1 && j==size-2)||(i==size-2 && j==1) )
            {
                 this->tactic[i][j] = 25;
            }
            if((i==1 && j==0)||(i==0 && j==1)||(i==size-2 && j==size-1)||(i==size-1 && j==size-2)||(i==1 && j==size-1)||(i==size-2 && j==0)||(i==size-1 && j==1)||(i==0 && j==size-2) )
            {
                 this->tactic[i][j] = 50;
            }
            ///System.out.print(tactic[i][j]+"\t");
        }
        ///System.out.print("\n");
    }
}
bool AI1::getTeam() //utility
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

int AI1::getPriceModifier(int x,int y)  //get price computed before for a cell
{
    return this->tactic[y][x];
}
Cell* AI1::doJob()  //routine
{
    Cell* max;
    int maxPrice;

    //this->cf->resetEmpty();
    //this->cf->setPadsVisibility(false);
   /* if( this->cf->recalculateAndMark(this->team)==0)
    {
        return NULL;
    }*/
    if(!this->st->empty())
    {
        max = st->back();
        maxPrice = max->getPrice()*this->getPriceModifier(max->getXPos(), max->getYPos());
        for(Cell* choice: (*st))    //find the best solution according to heuristics
        {
            if(choice->getPrice()*this->getPriceModifier(choice->getXPos(), choice->getYPos()) > maxPrice)
            {
                maxPrice = choice->getPrice()*this->getPriceModifier(choice->getXPos(), choice->getYPos());
                max = choice;
            }
           /// System.out.print(choice.getPrice()*this.getPriceModifier(choice.getXPos(), choice.getYPos())+" : ");
        }
       /// System.out.println("SELECTED: "+max.getPrice()*this.getPriceModifier(max.getXPos(), max.getYPos()));
       /// System.out.println("DONE");
        this->gc->placeStone(max);
        //cf.turnStones(max.getXPos(),max.getYPos(),gc.getActualPlayer());
        //gc.changeTeam();
        if(this->last!=NULL)
        {
            ///AIPlay1->last->setBackground(Color.white);
        }
        this->last = max;//save
        ///max->setBackground(Color->magenta);
        return max;//return
    }
    else
    {
        //System.out.println("EMPTY STACK");
        //return new Cell(-1,-1,-1,-1,-1);
        return NULL; // else null
    }
}
