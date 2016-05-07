#include "mainwindow.h"
#include "statswindow.h"
#include "ui_mainwindow.h"
/***********************************************************************************7
 * Martin Hlipala xhlipa00
 * Adam Bak xbakad00
 *
 * All rights reserved
 *
*/
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->playBtn,SIGNAL(released()),this,SLOT(handlePlayBtn())); // connect signals to slots (communication between widgets)
    connect(ui->loadBtn,SIGNAL(released()),this,SLOT(handleLoadBtn())); // connect signals to slots (communication between widgets)
    connect(ui->exitBtn,SIGNAL(released()),this,SLOT(handleExitBtn())); // connect signals to slots (communication between widgets)
    ui->label_6->setPixmap(*(new QPixmap("img\\brand.jpg")));
}

void MainWindow::openGameWindow() //open new window
{
    for(int i=0; i<this->gs->getInstancies(); i++)  //make instancies according to setting
    {
        this->gw = new GameWindow(0,this->gs);
        this->gw->show();
    }
}

void MainWindow::handleLoadBtn()    //event handler
{
    this->gw = new GameWindow(0);
    this->gw->show();
    this->hide();
}

void MainWindow::handlePlayBtn()    //event handler (save everything set to the setting holder class GameSetting)
{
    this->gs = new GameSetting();
    this->gs->setGameMode(ui->humanSet->isChecked());
    this->gs->setSize(ui->gameSize->value());
    this->gs->setStoneFreezing(ui->freezingSet->isChecked());
    this->gs->setB_var(ui->bVal->value());
    this->gs->setI_var(ui->iVal->value());
    this->gs->setMaxFreezed(ui->maxFreezed->value());
    this->gs->setInstancies(ui->gameInstancies->value());
    this->openGameWindow();
    this->hide();
}

void MainWindow::openStatWindow() //...
{
    this->sw = new StatsWindow();
}

void MainWindow::handleExitBtn()//handler
{
    this->close();
    QCoreApplication::exit(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}
