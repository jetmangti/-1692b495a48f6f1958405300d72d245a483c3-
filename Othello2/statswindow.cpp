#include "statswindow.h"
#include "ui_statswindow.h"

StatsWindow::StatsWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StatsWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton,SIGNAL(released()),this,SLOT(handleExit()));
}

void StatsWindow::handleExit()
{
    this->close();
    QCoreApplication::exit();
}

StatsWindow::~StatsWindow()
{
    delete ui;
}
