#include "mainwindow.h"
#include "includes.h"
#include <QApplication>
#include <QPushButton>
#include <QWidget>
#include <QBoxLayout>

#include "cligame.h"
/***********************************************************************************7
 * Martin Hlipala xhlipa00
 * Adam Bak xbakad00
 *
 * All rights reserved
 *
*/
using namespace std;

int main(int argc, char *argv[])
{
    int sel;
    bool repeat;
    cout << "Othello game!" << endl;
    cout << "Credits: Martin Hlipala, Adam Bak. All rights reserved."<<endl;
    cout <<endl;
    cout << "Select mode:"<<endl;
    cout << "   1) CLI" <<endl;
    cout << "   2) QT GUI" <<endl<<endl;
    do  //wait for selection
    {
        repeat = false;
        cout << "Your selection: ";
        cin  >> sel;
        switch(sel)
        {
            case 1: //in case CLI was set, create cliGame()
            {
                cout << "You have selected CLI version, please wait..." << endl;
                cliGame *cli = new cliGame();
                cli->run();
                break;
            }
            case 2: // else create GUI game
            {
                cout << "You have selected GUI version, switching to GUI, please wait..." << endl;
                QApplication a(argc, argv);
                MainWindow w;
              /*//////  QWidget * wdg = new QWidget();
                QVBoxLayout *lout = new QVBoxLayout(wdg);
                QPushButton *btn1 = new QPushButton("btn1");
                QPushButton *btn2 = new QPushButton("btn2");
                QPushButton *btn3 = new QPushButton("btn3");
                lout->addWidget(btn1);
                lout->addWidget(btn2);
                lout->addWidget(btn3);
                w.setCentralWidget(wdg);*/
                w.show();
                return a.exec();
                break;
            }
            default:
            {
                cout << "This selection does not exist!! try again..." <<endl;
                repeat=true;
                break;
            }
        }
    }
    while(repeat==true);
    return 0;
}
