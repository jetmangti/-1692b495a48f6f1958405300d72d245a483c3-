#include "game.h"
#include "cell.h"

Game::Game(GameSetting* gs)
{
    //this->renderer = renderer;
    this->gs = gs;
    int size = this->gs->getSize();
    this->cf = new CellFinder(this->gs->getSize(),&this->board);
    this->gc = new GameController();
    this->board.resize(size);
    this->selectionPads.resize(size);
    this->ai1 = new AI1(this->cf,this->gc,this->gs->getSize(),1,&this->board);
    this->ai2 = new AI2(this->cf,this->gc,this->gs->getSize(),1,&this->board);

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
    this->renderRefresh = true;
}
Game::Game()
{
    this->gs = new GameSetting();
    this->gc = new GameController();
    this->loadGame();
    //this->renderer = renderer;
    this->cf = new CellFinder(this->gs->getSize(),&this->board);

    this->ai1 = new AI1(this->cf,this->gc,this->gs->getSize(),1,&this->board);
    this->ai2 = new AI2(this->cf,this->gc,this->gs->getSize(),1,&this->board);


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
            ///?this.win.dispose();
    }
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
        cout << "here" <<endl;
        this->aiThinking=true;
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
        #ifdef LINUX
            usleep(700 * 1000);
        #endif
        #ifdef WINDOWS
            Sleep(700);
        #endif
       this->aiThinking=false;
       this->cf->turnStones(aiStone->getXPos(),aiStone->getYPos(),gc->getActualPlayer());
       this->cf->setPadsVisibility(true);
       this->bRem--;
             this->cf->resetEmpty();
       this->doMarker();
       this->state = 1;
    }
    this->actualizeScore();
}
bool Game::isAiThinking()
{
    return this->aiThinking;
}

void Game::actualizeScore()
{
    white=0;
    black=0;
    for(int i=0; i<this->gs->getSize(); i++)
    {
        for (int j=0;j<this->gs->getSize() ;j++)
        {
            if(this->board.at(i).at(j)->getTeam() == BLACK)
            {
                black++;
            }
            else if(this->board.at(i).at(j)->getTeam() == WHITE)
            {
                white++;
            }
            //board[i][j].recordStatus();
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
}
