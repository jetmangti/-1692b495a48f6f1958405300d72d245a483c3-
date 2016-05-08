#include "gamewindow.h"
#include "ui_gamewindow.h"
#include <qpushbutton.h>
#include <QBoxLayout>
#include <QGridLayout>
#include <QLayout>
#include <QWidget>
#include <QThread>
#include <QMainWindow>
#include <QFrame>
#include "game.h"
#include <thread>
#include "statswindow.h"

#define sizeConst 496
#define defaultX 150
#define defaultY 100
/***********************************************************************************7
 * Martin Hlipala xhlipa00
 * Adam Bak xbakad00
 *
 * All rights reserved
 *
*/
GameWindow::GameWindow(QWidget *parent, GameSetting *gs) : // gui game creation
    QDialog(parent),
    ui(new Ui::GameWindow)
{
    this->parent = parent;
    this->gs = gs;
    ui->setupUi(this);
    connect(ui->undoButton,SIGNAL(released()),this,SLOT(undo())); // connect signals to slots (communication between widgets)
    connect(ui->saveButton,SIGNAL(released()),this,SLOT(saveGame())); // connect signals to slots (communication between widgets)
    if(gs)
    {
        this->newGame(this->gs);
    }
    else
    {
        this->loadGame();
    }
    this->buildBoard();
    this->run();
}
void GameWindow::toDoThread(int i, int j) //thread routine
{
    this->gm->putTo(i,j);
    this->gm->clearSelPads();
    this->gm->update();
}

void GameWindow::clickHandler() // event handler (on cell click,find aprop.cell and run toDoThread as independent thread)
{
    QObject *se = sender();
    for(int i=0; i< this->gm->getGs()->getSize(); i++)
    {
        for(int j=0; j< this->gm->getGs()->getSize(); j++)
        {
            if(this->boardBtn.at(i).at(j) == se)
            {
                std::thread t(&this->toDoThread,this,i,j);
                t.detach();
                break;
            }
        }
    }
}

void GameWindow::buildBoard()   //create game board (Buttons representing cells generator)
{
    QWidget *wg = new QWidget();
    QFrame *lo = new QFrame(wg);
    int x=defaultX;
    int y=defaultY;
    int btnSize = sizeConst/this->gm->getGs()->getSize();
    this->btnSize=btnSize;
    this->boardBtn.resize(this->gm->getGs()->getSize());
    for(int i=0; i< this->gm->getGs()->getSize(); i++)
    {
        this->boardBtn.at(i).resize(this->gm->getGs()->getSize());
        for(int j=0; j< this->gm->getGs()->getSize(); j++)
        {
            this->boardBtn.at(i).at(j) = new QPushButton();
            this->boardBtn.at(i).at(j)->setGeometry(x,y,btnSize,btnSize);
            this->boardBtn.at(i).at(j)->setParent(this);
            this->boardBtn.at(i).at(j)->setEnabled(false);
            connect(this->boardBtn.at(i).at(j),SIGNAL(released()),this,SLOT(clickHandler()));
            x+=btnSize;
        }
        x=defaultX;
        y+=btnSize;
    }

}

void GameWindow::saveGame() //save game
{
    this->gm->saveGame();
    this->gm->update();
    //this->render();
}

void GameWindow::undo() // undo
{
    this->gm->undo();
    this->gm->reloadSelPads();
    this->gm->update();
    //this->render();
}

void GameWindow::loadGame() // load game constructor
{
    this->gm = new Game();
    this->gm->loadGame();
    this->board = this->gm->getBoard();
    this->selectionPads = this->gm->getSelectionPads();
}

void GameWindow::newGame(GameSetting *st) //new empty Game constructor
{
    this->gm = new Game(st);
    this->board = this->gm->getBoard();
    this->selectionPads = this->gm->getSelectionPads();
}

void GameWindow::render() //render routine
{
    ui->wScore->setText("White score:"+QString::number(this->gm->getWhite()));
    ui->bScore->setText("Black score:"+QString::number(this->gm->getBlack()));
    ui->bRem->setVisible(false);
    ui->wRem->setVisible(false);
    for(int i=0; i<this->gm->getGs()->getSize(); i++)
    {
        for(int j=0; j<this->gm->getGs()->getSize(); j++)
        {
            if(this->selectionPads->at(j).at(i) == true && this->gm->getVisibility()&& this->board->at(j).at(i)->getTeam() == EMPTY) // SHOW POSSIBLE CELL PLACEMENTS
            {
                this->boardBtn.at(j).at(i)->setEnabled(true);
                this->boardBtn.at(j).at(i)->setText("#");
               // this->boardBtn.at(j).at(i)->setStyle("background-color: #FFFFFFF;");
                this->boardBtn.at(j).at(i)->setIcon(QIcon());
            }
            else if(this->board->at(j).at(i)->getTeam() == BLACK) //SET CELL BLACK ICON
            {
                this->boardBtn.at(j).at(i)->setEnabled(false);
                this->boardBtn.at(j).at(i)->setText("B");
                this->boardBtn.at(j).at(i)->setIcon(*this->texBlackI);
               // this->boardBtn.at(j).at(i)->setIconSize(QSize(this->btnSize,this->btnSize));
            }
            else if(this->board->at(j).at(i)->getTeam() == WHITE) // SET CELL WHITE ICON
            {
                this->boardBtn.at(j).at(i)->setEnabled(false);
                this->boardBtn.at(j).at(i)->setText("W");
                this->boardBtn.at(j).at(i)->setIcon(*this->texWhiteI);
                //this->boardBtn.at(j).at(i)->setIconSize(QSize(this->btnSize,this->btnSize));
            }
            else if(this->board->at(j).at(i)->getTeam() == BLACK_FR || this->board->at(j).at(i)->getTeam() == WHITE_FR) //SET CELL ICE ICON
            {
                this->boardBtn.at(j).at(i)->setEnabled(false);
                this->boardBtn.at(j).at(i)->setText("F");
                this->boardBtn.at(j).at(i)->setIcon(*this->texFreezedI);
                //this->boardBtn.at(j).at(i)->setIconSize(QSize(this->btnSize,this->btnSize));
            }
            else    // CELL IS EMPTY
            {
                this->boardBtn.at(j).at(i)->setEnabled(false);
                this->boardBtn.at(j).at(i)->setText("");
                this->boardBtn.at(j).at(i)->setIcon(QIcon());
            }

        }
    }
}
void GameWindow::showStats() // show stats window
{
    this->sw->setStats(this->gm->getBlack(),this->gm->getWhite());
    this->sw->exec();
}

void GameWindow::rendererThread()
{
   /* while(true)
    {
        this->render();
        if(this->gm->isEndGame())
        {
            break;
        }
    }*/
}

void GameWindow::endGame() //endGame handler (called from other threads)
{
    this->showStats();
}

Game* GameWindow::getGm()//return pointer to game object
{
    return this->gm;
}

void GameWindow::run()
{
    this->texBlack = new QPixmap("img\\s_black.png");   //texture loading and setting...
    this->texWhite = new QPixmap("img\\s_white.png");//..
    this->texFreezed = new QPixmap("img\\s_ice.png");//..
    this->texBlackI = new QIcon(*this->texBlack);//..
    this->texWhiteI = new QIcon(*this->texWhite);//..
    this->texFreezedI = new QIcon(*this->texFreezed); //..
    ui->label_2->setPixmap(*(new QPixmap("img\\header.png")));
    this->sw = new StatsWindow(); // some init stuff
    this->gm->run(); //..
    this->gm->update(); //..
    //this->render();
    RenderThread *rndr = new RenderThread(this); // create independent render thread
    connect(rndr,SIGNAL(endDetected()),this,SLOT(endGame())); //create communication canal from worker thread to main thread
    rndr->start();
  /*  do
    {
        this->gm->update();
        if(this->gm->getGs()->getGameMode()==1)
        {
            if(this->gm->isAiThinking() == true)
            {
                while(this->gm->isAiThinking()==true)
                {
                    continue;
                }
                this->render();
            }
        }
        if(this->gm->getRenderRefresh());
        {
            this->render();
            this->gm->setRenderRefreshed();
        }
    }
    while(this->gm->isEndGame()==false);*/
}

GameWindow::~GameWindow()
{
    delete ui;
}
