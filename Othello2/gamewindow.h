#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QDialog>
#include <QThread>
#include "includes.h"
#include "game.h"
#include "statswindow.h"
/***********************************************************************************7
 * Martin Hlipala xhlipa00
 * Adam Bak xbakad00
 *
 * All rights reserved
 *
*/
namespace Ui {
class GameWindow;
}

class GameWindow : public QDialog
{
    Q_OBJECT

public: //description in cpp file
    explicit GameWindow(QWidget *parent = 0, GameSetting *gs=NULL);
    void buildBoard();
    void loadGame();
    void render();
    void toDoThread(int,int);
    void run();
    void rendererThread();
    void showStats();
    void newGame(GameSetting*);
    Game* getGm();
    ~GameWindow();

private slots:
    void clickHandler();
    void undo();
    void saveGame();
    void endGame();

private:
    QPixmap* texBlack;
    QPixmap* texWhite;
    QPixmap* texFreezed;
    QIcon* texBlackI;
    QIcon* texWhiteI;
    QIcon* texFreezedI;
    int btnSize;
    vector <vector< QPushButton*>> boardBtn;
    Ui::GameWindow *ui;
    Game *gm;
    QWidget *parent;
    StatsWindow* sw;
    GameSetting* gs;
    vector< vector< bool>>* selectionPads;
    vector< vector< Cell*>>* board;
};


class RenderThread : public QThread
{
    Q_OBJECT
private:
    GameWindow *gw;
public:

    RenderThread(GameWindow *parent)
    {
        this->gw = parent;
    }
    void run()
    {
        while(true)
        {
            //this->gw->getGm()->update();
            this->gw->render();
            //this->gw->update();
            if(this->gw->getGm()->isEndGame())
            {
                break;
            }
        }
        emit endDetected();
        return;
    }
signals:
    void endDetected();
};

#endif // GAMEWINDOW_H
