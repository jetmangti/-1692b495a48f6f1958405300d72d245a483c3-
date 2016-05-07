#include "statswindow.h"
#include "ui_statswindow.h"
/***********************************************************************************7
 * Martin Hlipala xhlipa00
 * Adam Bak xbakad00
 *
 * All rights reserved
 *
*/
StatsWindow::StatsWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StatsWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton,SIGNAL(released()),this,SLOT(handleExit())); // connect signals to slots (communication between widgets)
}

void StatsWindow::handleExit()  //event handler
{
    this->close();
    QCoreApplication::exit();
}

void StatsWindow::setStats(int black, int white)    //configure ui according to data passed
{
    if(black > white)
    {
        ui->label->setText("BLACK WON!!!");
    }
    else if( white > black)
    {
        ui->label->setText("WHITE WON!!!");
    }
    else
    {
        ui->label->setText("DRAW!!!");
    }
    ui->label_3->setText("Black: "+QString::number(black)+" VS White:"+QString::number(white));
}

StatsWindow::~StatsWindow()
{
    delete ui;
}
