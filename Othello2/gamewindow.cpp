#include "gamewindow.h"
#include "ui_gamewindow.h"
#include <qpushbutton.h>
#include <QBoxLayout>
#include <QGridLayout>
#include <QLayout>
#include <QWidget>
#include <QMainWindow>
#include <QFrame>
#include "game.h"
#include <thread>

#define sizeConst 496
#define defaultX 150
#define defaultY 100

GameWindow::GameWindow(QWidget *parent, GameSetting *gs) :
    QDialog(parent),
    ui(new Ui::GameWindow)
{
    this->parent = parent;
    this->gs = gs;
    ui->setupUi(this);
    connect(ui->undoButton,SIGNAL(released()),this,SLOT(undo()));
    connect(ui->saveButton,SIGNAL(released()),this,SLOT(saveGame()));
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
void GameWindow::toDoThread(int i, int j)
{
    this->gm->putTo(i,j);
    this->gm->clearSelPads();
    this->gm->update();
}

void GameWindow::clickHandler()
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
            }
        }
    }
}

void GameWindow::buildBoard()
{
    QWidget *wg = new QWidget();
    QFrame *lo = new QFrame(wg);
    int x=defaultX;
    int y=defaultY;
    int btnSize = sizeConst/this->gm->getGs()->getSize();
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

void GameWindow::saveGame()
{
    this->gm->saveGame();
    this->gm->update();
    //this->render();
}

void GameWindow::undo()
{
    this->gm->undo();
    this->gm->reloadSelPads();
    this->gm->update();
    //this->render();
}

void GameWindow::loadGame()
{
    this->gm = new Game();
    this->gm->loadGame();
    this->board = this->gm->getBoard();
    this->selectionPads = this->gm->getSelectionPads();
}

void GameWindow::newGame(GameSetting *st)
{
    this->gm = new Game(st);
    this->board = this->gm->getBoard();
    this->selectionPads = this->gm->getSelectionPads();
}

void GameWindow::render()
{
    ui->wScore->setText("White score:"+QString::number(this->gm->getWhite()));
    ui->bScore->setText("Black score:"+QString::number(this->gm->getBlack()));
    ui->bRem->setVisible(false);
    ui->wRem->setVisible(false);
    for(int i=0; i<this->gm->getGs()->getSize(); i++)
    {
        for(int j=0; j<this->gm->getGs()->getSize(); j++)
        {
            if(this->selectionPads->at(j).at(i) == true && this->gm->isAiThinking()==false && this->board->at(j).at(i)->getTeam() == EMPTY)
            {
                this->boardBtn.at(j).at(i)->setEnabled(true);
                this->boardBtn.at(j).at(i)->setText("#");
            }
            else if(this->board->at(j).at(i)->getTeam() == BLACK)
            {
                this->boardBtn.at(j).at(i)->setEnabled(false);
                 this->boardBtn.at(j).at(i)->setText("B");
            }
            else if(this->board->at(j).at(i)->getTeam() == WHITE)
            {
                this->boardBtn.at(j).at(i)->setEnabled(false);
                this->boardBtn.at(j).at(i)->setText("W");
            }
            else if(this->board->at(j).at(i)->getTeam() == BLACK_FR || this->board->at(j).at(i)->getTeam() == WHITE_FR)
            {
                this->boardBtn.at(j).at(i)->setEnabled(false);
                this->boardBtn.at(j).at(i)->setText("F");
            }
            else
            {
                this->boardBtn.at(j).at(i)->setEnabled(false);
                this->boardBtn.at(j).at(i)->setText("");
            }
            this->boardBtn.at(j).at(i)->update();
        }
    }
}
void GameWindow::renderThread()
{
    while(true)
    {
        this->render();
    }
}

void GameWindow::run()
{
    this->gm->run();
    this->gm->update();
    //this->render();
    std::thread t(&this->renderThread,this);
    t.detach();
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
