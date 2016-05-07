#ifndef STATSWINDOW_H
#define STATSWINDOW_H
/***********************************************************************************7
 * Martin Hlipala xhlipa00
 * Adam Bak xbakad00
 *
 * All rights reserved
 *
*/
#include <QDialog>

namespace Ui {
class StatsWindow;
}

class StatsWindow : public QDialog
{
    Q_OBJECT

public:
    explicit StatsWindow(QWidget *parent = 0);
    void setStats(int,int);
    ~StatsWindow();

private slots:
    void handleExit();
private:
    Ui::StatsWindow *ui;
};

#endif // STATSWINDOW_H
