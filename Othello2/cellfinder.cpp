#include "cellfinder.h"

/***********************************************************************************7
 * Martin Hlipala xhlipa00
 * Adam Bak xbakad00
 *
 * All rights reserved
 *
*/

CellFinder::CellFinder()    //empty constructor...
{

}

CellFinder::CellFinder(int size,vector<vector<Cell *>>* matrix) //constructor sets references
{
    this->size = size;
    this->matrix = matrix;
}
void CellFinder::hidePads()
{
 //used for port issues
}

Cell* CellFinder::getNextCell(int x,int y,int dir)  //get neighbour cell
{
    //0=y_up 1=y_down 2=x_right 3=x_left 4=x_left_y_up 5=x_right_y_down 6=x_right_y_up 7=x_left_y_down
    switch(dir)     // do the same thing for different directions
    {
        case 0:
        {
            if(x>=0 && x<this->size && y-1>=0 && y-1 < this->size)  // check for bounds
                return matrix->at(x).at(y-1);   //return cell at x and y-1
            break;
        }
        case 1:
        {
            if(x>=0 && x<this->size && y+1>=0 && y+1 < this->size)  //...
                return matrix->at(x).at(y+1); //...
            break;
        }
        case 2:
        {
            if(x+1>=0 && x+1<this->size && y>=0 && y < this->size)//...
                return matrix->at(x+1).at(y);//...
            break;
        }
        case 3:
        {
            if(x-1>=0 && x-1<this->size && y>=0 && y < this->size)//...
                return matrix->at(x-1).at(y);//...
            break;
        }
        case 4:
        {
            if(x-1>=0 && x-1<this->size && y-1>=0 && y-1 < this->size)//....
                return matrix->at(x-1).at(y-1);//...
            break;
        }
        case 5:
        {
            if(x+1>=0 && x+1<this->size && y+1>=0 && y+1 < this->size)//...
                return matrix->at(x+1).at(y+1);//...
            break;
        }
        case 6:
        {
            if(x+1>=0 && x+1<this->size && y-1>=0 && y-1 < this->size)//...
                return matrix->at(x+1).at(y-1);//...
            break;
        }
        case 7:
        {
            if(x-1>=0 && x-1<this->size && y+1>=0 && y+1 < this->size)//..
                return matrix->at(x-1).at(y+1);//...
            break;
        }
        default:
        {
            return matrix->at(x).at(y); // default cell is cell at x y
        }
    }
    return new Cell(-1,-1,0,0,0);   //return random cell
}

int CellFinder::rayCast(int x,int y,int team)   //raycast, find all the possible free spaces via raycast method
{
    Cell* temp;
    int cntr=0;
    this->lastState = this->st;
    for(int dir=0; dir < 8; dir++) 	//0=y_up 1=y_down 2=x_right 3=x_left 4=x_left_y_up 5=x_right_y_down 6=x_right_y_up 7=x_left_y_down
    {
        int state = 0;
        int tempx = x;
        int tempy = y;
        bool fail = false;
        bool success = false;
        this->priceCounter = 0;
        do  // automat start
        {
            temp = getNextCell(tempx,tempy,dir);
            tempx = temp->getXPos();
            tempy = temp->getYPos();
            if(tempx < 0 || tempx >= this->size || tempy < 0 || tempy >= this->size)
            {
                fail = true;
                break;
            }
            if(team == BLACK)   // implementation used if actually examined stone is black
            {
                switch(state)   //fsm
                {
                    case 0:
                    {
                        if(temp->getTeam() == WHITE)    //if next cell is white ok
                        {
                            state = 1; // white continue;
                            this->priceCounter++;
                        }
                        else
                        {
                            state = 4; // empty,black = fail
                        }
                        break;
                    }
                    case 1: //white
                    {
                        if(temp->getTeam() != WHITE && temp->getTeam() != EMPTY)
                        {
                            state = 4; //black = fail
                        }
                        else if(temp->getTeam() == EMPTY)   //free cell found
                        {
                            this->st.push_back(temp);
                           /// temp->setContentAreaFilled(true);
                            success = true;
                            temp->setPrice(this->priceCounter);
                            this->counter++;
                            cntr++;
                            break;
                        }
                        else
                        {
                            state = 1;
                            this->priceCounter++;
                            break;
                        }
                    }
                    case 4://fail state
                    {
                        fail = true;
                        this->priceCounter = 0;
                        break;
                    }
                    default:
                    {
                        break;
                    }
                }
            }
            else  // implementation used if actually examined stone is white
            {
                switch(state)//fsm
                {
                    case 0:
                    {
                        if(temp->getTeam() == BLACK) //if next cell is black ok
                        {
                            state = 1; // white continue;
                            this->priceCounter++;
                        }
                        else
                        {
                            state = 4; // black = fail
                        }
                        break;
                    }
                    case 1: //white
                    {
                        if(temp->getTeam() != BLACK && temp->getTeam() != EMPTY)
                        {
                            state = 4; //black = fail
                        }
                        else if(temp->getTeam() == EMPTY)   // free cell found
                        {
                            success = true;
                            this->st.push_back(temp);
                            temp->setPrice(this->priceCounter);
                            this->counter++;
                            cntr++;
                            break;
                        }
                        else
                        {
                            state = 1;
                            this->priceCounter++;
                            break;
                        }
                    }

                    case 4://fail state
                    {
                        fail = true;
                        this->priceCounter = 0;
                        break;
                    }
                    default:
                    {
                        break;
                    }
                }
            }
        }
        while(!fail && !success);   // do while not fail or success flag set
    }
    return cntr;    //return number of found cells
}

void CellFinder::clearStack()       //clear stack
{
    this->st.clear();
}

vector<Cell*>* CellFinder::getCellList()    //return reference to list of possible stone placements
{
        return &this->st;
}

void CellFinder::resetEmpty()   //reset stack of possible placements
{
    this->clearStack();
}



void CellFinder::resetEmptyAll()    //reset all stacks
{
    this->counter=0;
    for(Cell* cont : lastState)
    {
        cont->setBlank();
    }
    for(int i=0; i<this->size; i++)
    {
        for(int j=0; j<this->size; j++)
        {
           /// matrix[i][j].setEnabled(false);
          ///  matrix[i][j].setContentAreaFilled(false);
            //matrix[i][j].undo();

        }
    }
    this->clearStack();
}

int CellFinder::recalculateAndMark(int team)    // find and mark possible places where can be stone put
{
    this->counter=0;
    int cntr=0;
    for(int i=0; i < this->size; i++)
    {
        for(int j=0; j < this->size; j++)
        {
            if(this->matrix->at(i).at(j)->team != EMPTY && this->matrix->at(i).at(j)->team != team && (this->matrix->at(i).at(j)->team == BLACK || this->matrix->at(i).at(j)->team == WHITE))
            {
                cntr = rayCast(i,j,matrix->at(i).at(j)->team);  // Do a raycast from every stone
            }
        }
    }
    return cntr;
}

void CellFinder::setPadsVisibility(bool vis)    //set visibility (render utility)
{
    this->visibility = vis;
}

void CellFinder::turnStones(int x,int y,bool team)     //turns stones
{
    int reversedDirection, i=0;
    int currentx = x;
    int currenty = y;
    Cell* current;


    for(int direction=0;direction<8;++direction)   //checks in all 8 directions from the stone that was placed
    {
        i=0;
        while(true){

            i++;
            current=getNextCell(currentx,currenty,direction); // next cell in given direction
            currentx = current->getXPos();
            currenty = current->getYPos();

            if(current->getTeam()==EMPTY || current->getTeam()==WHITE_FR || current->getTeam()==BLACK_FR){  // if the cell is empty, returns to the original
                currentx = x;        			// position and continues in a different direction
                currenty = y;
                break;
            }
            else if((current->getTeam() == BLACK && team==false) || (current->getTeam() == WHITE && team==true) ) // if the next cell checked contains stone of the current player
            {

                if((direction % 2)==1)			//  return back in opposite direction
                {
                    reversedDirection=direction-1;
                }
                else
                {
                    reversedDirection=direction+1;
                }

                current=getNextCell(currentx,currenty,reversedDirection);
                currentx = current->getXPos();
                currenty = current->getYPos();

                for(i--;i>0;i--){

                    //if(i>0)
                    current->swapTeam(!team); // change the color of the stone
                    current=getNextCell(currentx,currenty,reversedDirection);
                    currentx = current->getXPos();
                    currenty = current->getYPos();

                }
                break;
            }
        }
    }
}
