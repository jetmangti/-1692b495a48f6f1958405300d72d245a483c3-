#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QDialog>
#include "includes.h"
#include "game.h"
namespace Ui {
class GameWindow;
}

class GameWindow : public QDialog
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = 0, GameSetting *gs=NULL);
    void buildBoard();
    void loadGame();
    void render();
    void toDoThread(int,int);
    void run();
    void renderThread();
    void newGame(GameSetting*);
    ~GameWindow();

private slots:
    void clickHandler();
    void undo();
    void saveGame();

private:
    vector <vector< QPushButton*>> boardBtn;
    Ui::GameWindow *ui;
    Game *gm;
    QWidget *parent;
    GameSetting* gs;
    vector< vector< bool>>* selectionPads;
    vector< vector< Cell*>>* board;
};

#endif // GAMEWINDOW_H
