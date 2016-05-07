#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "gamewindow.h"
#include "statswindow.h"
/***********************************************************************************7
 * Martin Hlipala xhlipa00
 * Adam Bak xbakad00
 *
 * All rights reserved
 *
*/
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void openGameWindow();
    void openStatWindow();
    ~MainWindow();

private slots: //event handlers
    void handlePlayBtn();
    void handleLoadBtn();
    void handleExitBtn();

private: //reference holders
    Ui::MainWindow *ui;
    GameWindow *gw;
    GameSetting *gs;
    StatsWindow *sw;
};

#endif // MAINWINDOW_H
