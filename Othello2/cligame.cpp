#include "cligame.h"

cliGame::cliGame()
{
    int size;
    int mode;
    bool loadB = false;
    this->gs = new GameSetting();
    /*this->gs->setAiMode(1);
    this->gs->setSize(0);
    this->gs->setMaxFreezed(0);
    this->gs->setB_var(0);
    this->gs->setI_var(0);
    this->gs->setInstancies(0);
    this->gs->setGameMode(0);
    this->gs->setStoneFreezing(0);*/
    char load;
    do
    {
        cout << "Do you want to load the last saved game ? (y/n) :";
        cin >> load;
        cout <<endl;
    }
    while(load != 'y' && load != 'n');
    if(load == 'y')
    {
       loadB=true;
    }
    else
    {
        do
        {
            cout << "Select game size (8, 10 ,12): ";
            cin >> size;
            cout << endl;
        }
        while(size!=8 && size!=10 && size!=12);
        this->gs->setSize(size);
        do
        {
            cout << "Select opponent ( 0-CPU, 1-Human): ";
            cin >> mode;
            cout << endl;
        }
        while(mode!=0 && mode!=1);
        this->gs->setGameMode(mode);
        if(mode == 0)
        {
            int version;
            do
            {
                cout << "Select AI version ( 0-ver.2, 1-ver.1): ";
                cin >> version;
                cout << endl;
            }
            while(version!=0 && version!=1);
            if(version==0)
            {
                this->gs->aiMode = 2;
            }
            else
            {
                this->gs->aiMode = 1;
            }
        }
        int rules;
        do
        {
            cout << "Select rules ( 0-nonfreezing(classic), 1-freezing): ";
            cin >> rules;
            cout << endl;
        }
        while(rules!=0 && rules!=1);
        if(rules==0)
        {
            this->gs->setStoneFreezing(false);
        }
        else
        {
            this->gs->setStoneFreezing(true);
            int I=0,B=0,count=0;
            do
            {
                cout << "Set I value ( I > 0) :";
                cin >> I;
                cout << endl;
            }
            while(I < 1);
            do
            {
                cout << "Set B value ( B > I) :";
                cin >> B;
                cout << endl;
            }
            while(B > I);
            do
            {
                cout << "Set max number of freezed stones ( count > 0) :";
                cin >> count;
                cout << endl;
            }
            while(count < 1);
            this->gs->setB_var(B);
            this->gs->setI_var(I);
            this->gs->setMaxFreezed(count);
        }
    }
    ////////////////////TO BE CONTINUED, I, B , COUNT////////////////////////

    if(loadB)
    {
         this->game = new Game();
         cout << "Game created" <<endl;
         this->gs = this->game->getGs();
    }
    else
    {
         this->game = new Game(this->gs);

    }
    this->board = this->game->getBoard();
    this->selectionPads = this->game->getSelectionPads();
}
void cliGame::render()
{
    this->selectionPads = this->game->getSelectionPads();
    cout << "\t";
    for(int k=0; k<this->game->getGs()->getSize(); k++)
    {
        cout <<" "<< k << "\t";
    }
    cout << endl;
    for(int i=0; i<this->game->getGs()->getSize(); i++)
    {
        cout << i << "\t";
        for(int j=0; j<this->game->getGs()->getSize(); j++)
        {
            if(this->selectionPads->at(j).at(i) == true)
            {
                cout <<"[#]\t";
            }
            else if(this->board->at(j).at(i)->getTeam() == BLACK)
            {
                cout << "[B]\t";
            }
            else if(this->board->at(j).at(i)->getTeam() == WHITE)
            {
                cout << "[W]\t";
            }
            else if(this->board->at(j).at(i)->getTeam() == BLACK_FR || this->board->at(j).at(i)->getTeam() == WHITE_FR)
            {
                cout << "[F]\t";
            }
            else
            {
                cout << "[ ]\t";
            }
        }
        cout << endl <<endl;
    }
}
void cliGame::run()         //main game loop
{
    int x,y;
    bool stat;

    this->game->run();
    do
    {
        this->game->update();
        if(this->game->getGs()->getGameMode()==1)
        {
            if(this->game->isAiThinking() == true)
            {
                cout << "AI is thinking... please wait..." <<endl;
                while(this->game->isAiThinking()==true)
                {
                    continue;
                }
                this->render();
            }
        }
        if(this->game->getRenderRefresh())
        {
            this->render();
            this->game->setRenderRefreshed();
        }
        char action;
        do
        {
            cout << "Your next action : (c - continue, u - undo, s - save) :";
            cin >> action;
            cout <<endl;
        }
        while(action != 's' && action != 'u' && action != 'c');
        if(action == 'c')
        {
            if(this->game->isWaitingForInput())
            {
                do
                {
                    if(this->game->getGc()->getTeamID()==1)
                    {
                        cout << "Black player, enter the X coord :" ;
                        cin >> x;
                        cout << endl <<"Black player, enter the Y coord :" <<endl;
                        cin >> y;
                    }
                    else
                    {
                        cout << "White player, enter the X coord :" ;
                        cin >> x;
                        cout << endl <<"White player, enter the Y coord :" <<endl;
                        cin >> y;
                    }
                    stat=this->game->putTo(x,y);
                    if(stat==false)
                    {
                        cout << "Bad selection, use one of the marked (#) cells" <<endl;
                    }
                    else
                    {
                        break;
                    }
                }
                while(stat != true);
            }
        }
        else if(action == 'u')
        {
            cout << "UNDO";
            this->game->undo();
        }
        else if(action == 's')
        {
            cout << "SAVING..." <<endl;
            this->game->saveGame();
        }

    }
    while(this->game->isEndGame()==false);
}
