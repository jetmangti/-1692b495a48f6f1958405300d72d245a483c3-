#include "mainwindow.h"
#include "includes.h"
#include <QApplication>

#include "cligame.h"

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
    do
    {
        repeat = false;
        cout << "Your selection: ";
        cin  >> sel;
        switch(sel)
        {
            case 1:
            {
                cout << "You have selected CLI version, please wait..." << endl;
                cliGame *cli = new cliGame();
                cli->run();
                break;
            }
            case 2:
            {
                cout << "You have selected GUI version, switching to GUI, please wait..." << endl;
                QApplication a(argc, argv);
                MainWindow w;
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
