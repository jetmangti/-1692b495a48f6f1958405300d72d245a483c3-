#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "gamewindow.h"
#include "statswindow.h"

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

private slots:
    void handlePlayBtn();
    void handleLoadBtn();
    void handleExitBtn();

private:
    Ui::MainWindow *ui;
    GameWindow *gw;
    GameSetting *gs;
    StatsWindow *sw;
};

#endif // MAINWINDOW_H
