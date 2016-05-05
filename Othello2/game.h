#ifndef GAME_H
#define GAME_H

#include <fstream>
#include "cellfinder.h"
#include "gamecontroller.h"
#include "gamesetting.h"
#include "aiselector.h"
#include "ai1.h"
#include "ai2.h"

class Game
{
private :
    CellFinder* cf;
    GameController* gc;
    GameSetting* gs;
    AI1 *ai1;
    AI2 *ai2;
    int state = 1;
    int bRem;
    int wRem;
    int white;
    int black;
    vector< vector< Cell*>> board;
    vector< vector< bool>> selectionPads;
   // union renderer rend;
    bool renderRefresh = false;
    bool endGame = false;
    bool waitingForInput = false;
    bool aiThinking = false;
    int clickk=0;

public:
    Game();
    Game(GameSetting*);                                     //build game
    void run();                                 //run game logic
    vector <vector <Cell*>>* getBoard();        //UI output function
    vector <vector < bool>>* getSelectionPads(); //UI output function
    GameSetting * getGs();
    GameController *getGc();
    AISelector* getAs();
    void reloadSelPads();
    void clearSelPads();
    void freezerBody();
    void recordAll();
    void saveGame();
    void loadGame();
    int getWRem();
    int getBRem();
    int getBlack();
    int getWhite();
    void undo();
    bool isEndGame();
    bool isAiThinking();
    bool isWaitingForInput();
    bool prepare();
    bool getRenderRefresh();
    void setRenderRefreshed();
    void toDo(Cell*);
    void actualizeScore();
    void aiDo();
    void update();
    void doMarker();
    bool putTo(int,int);
    bool putToTeam(int,int,int);                //UI input function
};

#endif // GAME_H
