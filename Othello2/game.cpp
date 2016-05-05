#include "game.h"
#include "cell.h"
#include "QThread"
#include <chrono>
#include <thread>
Game::Game(GameSetting* gs)
{
       srand(time(0));
    //this->renderer = renderer;
    this->gs = gs;
    int size = this->gs->getSize();
    this->cf = new CellFinder(this->gs->getSize(),&this->board);
    this->gc = new GameController();
    this->board.resize(size);
    this->selectionPads.resize(size);
    this->ai1 = new AI1(this->cf,this->gc,this->gs->getSize(),1,&this->board);
    this->ai2 = new AI2(this->cf,this->gc,this->gs->getSize(),1,&this->board);
    this->bRem = this->wRem = (this->gs->getSize()*this->gs->getSize()/2)-2;
    this->white = this->black = 0;
    for(int i=0; i<size; i++)
    {
        this->board.at(i).resize(size);
        this->selectionPads.at(i).resize(size);
    }
    for(int i=0; i<this->gs->getSize(); i++)
    {
        for(int j=0; j<this->gs->getSize(); j++)
        {
           this->board.at(i).at(j) = new Cell(this->gs->getSize(),i,j,i,j);
           this->selectionPads.at(i).at(j) = false;
        }
    }
    this->board.at(this->gs->getSize()/2).at(this->gs->getSize()/2)->setWhite();
    this->board.at(this->gs->getSize()/2).at(this->gs->getSize()/2-1)->setBlack();
    this->board.at(this->gs->getSize()/2-1).at(this->gs->getSize()/2-1)->setWhite();
    this->board.at(this->gs->getSize()/2-1).at(this->gs->getSize()/2)->setBlack();
    this->actualizeScore();
    this->renderRefresh = true;
}
Game::Game()
{
    this->gs = new GameSetting();
    this->gc = new GameController();
    this->loadGame();
    //this->renderer = renderer;
    this->cf = new CellFinder(this->gs->getSize(),&this->board);
    this->bRem = this->wRem = (this->gs->getSize()*this->gs->getSize()/2)-2;
    this->white = this->black = 0;
    this->ai1 = new AI1(this->cf,this->gc,this->gs->getSize(),1,&this->board);
    this->ai2 = new AI2(this->cf,this->gc,this->gs->getSize(),1,&this->board);

    this->actualizeScore();
    this->renderRefresh = true;
}
vector <vector <Cell*>>* Game::getBoard()        //UI output function
{
    return &(this->board);
}

vector <vector < bool>>* Game::getSelectionPads() //UI output function
{
    return &(this->selectionPads);
}

void Game::saveGame()
{
    ofstream savefile;
    savefile.open ("lastSave.sve");
    savefile << this->gc->getTeamID()<<endl;
    savefile << this->gs->getSize() <<endl;
    savefile << this->gs->getGameMode() <<endl;
    savefile << this->gs->getAiMode() <<endl;
    savefile << this->gs->getB_var() <<endl;
    savefile << this->gs->getI_var() <<endl;
    savefile << this->gs->isStoneFreezing() <<endl;
    savefile << this->gs->getInstancies() <<endl;
    savefile << this->gs->getMaxFreezed() <<endl;
    for(int i=0; i<this->gs->getSize(); i++)
    {
        for(int j=0; j<this->gs->getSize(); j++)
        {
            savefile << this->board.at(i).at(j)->getTeam() << endl;
        }
    }
    savefile.close();
}

void Game::loadGame()
{

    int value = 10;
    cout << "Opening save file...";
    FILE * savefile = fopen("lastSave.sve","r");
    cout << " DONE" <<endl;

    cout << "Loading teamID...";
    fscanf(savefile,"%d",&value);
    cout << value;
    this->gc->setTeamID(value);  //char to int conversion
    cout << " DONE" <<endl;

    cout << "Loading size...";
    fscanf(savefile,"%d\n",&value);
    cout << value;
    this->gs->setSize(value);
    cout << " DONE" <<endl;

    cout << "Loading gameMode...";
    fscanf(savefile,"%d\n",&value);
    cout << value;
    this->gs->setGameMode(value);
    cout << " DONE" <<endl;

    cout << "Loading aiMode...";
    fscanf(savefile,"%d\n",&value);
    cout << value;
    this->gs->setAiMode(value);
    cout << " DONE" <<endl;

    cout << "Loading B value...";
    fscanf(savefile,"%d\n",&value);
    cout << value;
    this->gs->setB_var(value);
    cout << " DONE" <<endl;

    cout << "Loading I value...";
    fscanf(savefile,"%d\n",&value);
    cout << value;
    this->gs->setI_var(value);
    cout << " DONE" <<endl;

    cout << "Loading freezingSetting...";
    fscanf(savefile,"%d",&value);
    cout << value;
    this->gs->setStoneFreezing(value);
    cout << " DONE" <<endl;

    cout << "Loading instancies...";
    fscanf(savefile,"%d",&value);
    cout << value;
    this->gs->setInstancies(value);
    cout << " DONE" <<endl;

    cout << "Loading maxFreezed...";
    fscanf(savefile,"%d",&value);
    cout << value;
    this->gs->setMaxFreezed(value);
    cout << " DONE" <<endl;

    cout << "Setting up board size:[" <<this->gs->getSize()<<"] ...";
   // this->board.resize(this->gs->getSize());
    cout << " DONE" <<endl;

    this->board.resize(this->gs->getSize());
    this->selectionPads.resize(this->gs->getSize());

    for(int i=0; i<this->gs->getSize(); i++)
    {
        this->board.at(i).resize(this->gs->getSize());
        this->selectionPads.at(i).resize(this->gs->getSize());
    }
    for(int i=0; i< this->gs->getSize();i++)
    {
        for(int j=0; j< this->gs->getSize();j++)
        {
            cout << "Loading Cell.." <<endl;
            fscanf(savefile,"%d",&value);
            this->board.at(i).at(j) = new Cell(this->gs->getSize(),i,j,i,j);
            this->selectionPads.at(i).at(j) = false;
            this->board.at(i).at(j)->setTeam(value);
        }
    }
    fclose(savefile);
}

bool Game::putTo(int x,int y)                         //UI input function
{
    for(int i=0; i<this->gs->getSize(); i++)
    {
        for (int j=0;j<this->gs->getSize() ;j++)
        {
            if(i == x && j == y && this->selectionPads.at(i).at(j)==true)
            {
                this->waitingForInput=false;
                this->toDo(this->board.at(i).at(j));
                return true;
            }
        }
    }
    return false;
}

bool Game::isWaitingForInput()
{
    if(this->waitingForInput)
    {
        return true;
    }
    return false;
}

void Game::recordAll()
{
    for(int i=0; i<this->gs->getSize(); i++)
    {
        for(int j=0;j<this->gs->getSize() ;j++)
        {
                //board[i][j].resetHistory();
            this->board.at(i).at(j)->recordStatus();
        }
    }
    this->clickk++;
}
void Game::undo()
{
    if(this->clickk > 0)
    {
        this->clickk--;
    //undoStck.pop().run();
        for(int i=0; i<this->gs->getSize(); ++i)
        {
            for (int j=0;j<this->gs->getSize() ;++j)
            {
                this->board.at(i).at(j)->undo();
                //board[i][j].undo();
            }
        }
        if(this->gc->getTeamID()==0)
        {
            bRem++;
        }
        else
        {
            wRem++;
        }
        this->gc->changeTeam();
        if(this->gs->getGameMode() == 0)
        {
            if(this->gc->getTeamID()==0)
            {
                bRem++;
            }
            else
            {
                wRem++;
            }
            for(int i=0; i<this->gs->getSize(); ++i)
            {
                for (int j=0;j<this->gs->getSize() ;++j)
                {
                    this->board.at(i).at(j)->undo();
                }
            }
            this->gc->changeTeam();
        }
        this->cf->hidePads();
        this->cf->resetEmpty();
        doMarker();
        this->actualizeScore();
    }
}

bool Game::putToTeam(int x,int y,int team)                 //UI input function
{
    return true;
}

void Game::setRenderRefreshed()
{
    this->renderRefresh = false;
}

bool Game::isEndGame()
{
    return this->endGame;
}

bool Game::getRenderRefresh()
{
    return this->renderRefresh;
}

GameSetting * Game::getGs()
{
    return this->gs;
}

GameController * Game::getGc()
{
    return this->gc;
}

void Game::doMarker()
{
    if(this->cf->recalculateAndMark(this->gc->getTeamID())==0)
    {
            /*if(this.wm == null)
            {
                System.out.println("WM NULL");
            }*/
            ///this.wm.endGame(gc.getTeamID(), this.black, this.white);
            this->endGame=true;
            cout << "endgame" <<endl;
    }
}
void Game::aiDo()
{
    this->aiThinking=true;
      std::this_thread::sleep_for(std::chrono::milliseconds(700));
    state = 2;
    this->cf->resetEmpty();
    Cell* aiStone;
    if(this->gs->getAiMode() == 1)
    {
        aiStone = ai1->doJob();
    }
    else
    {
        aiStone = ai2->doJob();
    }
    if(aiStone==NULL)
    {
        ///wm.endGame(gc.getTeamID(), black, white);
        this->endGame=true;
       /// win.dispose();
    }
   this->cf->turnStones(aiStone->getXPos(),aiStone->getYPos(),gc->getActualPlayer());
   this->cf->setPadsVisibility(true);
   this->bRem--;
   this->cf->resetEmpty();
   this->doMarker();
   this->state = 1;
   this->aiThinking=false;
}

void Game::toDo(Cell* temp)
{
    this->recordAll();
    if(state == 1)
    {
        //undoStck.push(this);
        this->cf->resetEmpty();
        this->gc->placeStone(temp);
       /// Cell* placedStone =(Cell) e.getSource(); 											 // gets ID of cell where stone was added
        this->cf->turnStones(temp->getXPos(),temp->getYPos(),this->gc->getActualPlayer());   // turns opponents stones and gc.getActualPlayer
        if(this->gs->getGameMode() == 0)
        {
            this->cf->setPadsVisibility(true);
        }
        this->doMarker();
        if(this->gs->getGameMode() == 0)
        {
             state = 2;
             this->cf->resetEmpty();
        }
        else
        {
            state = 1;
        }
        if(this->gc->getTeamID()==0)
        {
            this->bRem--;
        }
        else
        {
            wRem--;
        }
    }
    if(this->gs->getGameMode() != 1)
    {
        this->aiDo();
    }
    this->actualizeScore();
}
void Game::clearSelPads()
{
    this->cf->resetEmptyAll();
}

bool Game::isAiThinking()
{
    return this->aiThinking;
}
int Game::getBRem()
{
    return this->bRem;
}

int Game::getWRem()
{
    return this->wRem;
}

int Game::getBlack()
{
    return this->black;
}

int Game::getWhite()
{
    return this->white;
}

void Game::actualizeScore()
{
    this->white=0;
    this->black=0;
    for(int i=0; i<this->gs->getSize(); i++)
    {
        for (int j=0;j<this->gs->getSize() ;j++)
        {
            if(this->board.at(i).at(j)->getTeam() == BLACK)
            {
                this->black++;
            }
            else if(this->board.at(i).at(j)->getTeam() == WHITE)
            {
                this->white++;
            }
            //board[i][j].recordStatus();
        }
    }
}
void Game::reloadSelPads()
{
    this->cf->resetEmpty();
    doMarker();
}
void Game::freezerBody()
{
    cout << "Freezer running" <<endl;
    while(true){
        int x = rand()%(this->getGs()->getSize()-1);
        int y = rand()%(this->getGs()->getSize()-1);
        cout <<x << ": "<<y <<endl;
        int timeToSleep = (rand()%(this->getGs()->getB_var()))+this->getGs()->getI_var();
        if(this->board.at(x).at(y)->getTeam() != EMPTY && !this->board.at(x).at(y)->getFreezed())
        {
            std::cout << "GOT ONE" <<endl;
            this->board.at(x).at(y)->setFreezed();
            //cf.resetEmpty();
            //doMarker(gc,cf);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(timeToSleep*1000));
        if(this->board.at(x).at(y)->getTeam() != EMPTY &&this->board.at(x).at(y)->getFreezed())
        {
            this->board.at(x).at(y)->unsetFreezed();
        }
    }
}

bool Game::prepare()
{
    this->doMarker();
    vector < Cell*>* list;
    list = this->cf->getCellList();
    for(int i=0; i<this->gs->getSize(); i++)
    {
        for(int j=0; j<this->gs->getSize(); j++)
        {
            this->selectionPads.at(i).at(j) = false;
        }
    }
    for(Cell* cell : (*list))
    {
        this->selectionPads.at(cell->getXPos()).at(cell->getYPos()) = true;
    }
    return true;
}
void Game::update()
{
    this->prepare();
    this->renderRefresh = true;
    this->waitingForInput = !this->aiThinking;
}

void Game::run()
{
    this->prepare();
    if(this->getGs()->isStoneFreezing())
    {
        for(int i=0; i<this->getGs()->getMaxFreezed(); i++)
        {
            thread t(&this->freezerBody,this);
            t.detach();
        }
    }
}
