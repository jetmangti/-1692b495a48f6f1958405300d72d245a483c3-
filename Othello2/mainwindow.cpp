#include "mainwindow.h"
#include "statswindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->playBtn,SIGNAL(released()),this,SLOT(handlePlayBtn()));
    connect(ui->loadBtn,SIGNAL(released()),this,SLOT(handleLoadBtn()));
    connect(ui->exitBtn,SIGNAL(released()),this,SLOT(handleExitBtn()));
}

void MainWindow::openGameWindow()
{
    for(int i=0; i<this->gs->getInstancies(); i++)
    {
        this->gw = new GameWindow(0,this->gs);
        this->gw->show();
    }
}

void MainWindow::handleLoadBtn()
{
    this->gw = new GameWindow(0);
    this->gw->show();
    this->hide();
}

void MainWindow::handlePlayBtn()
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

void MainWindow::openStatWindow()
{
    this->sw = new StatsWindow();
}

void MainWindow::handleExitBtn()
{
    this->close();
    QCoreApplication::exit(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}
