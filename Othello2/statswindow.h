#ifndef STATSWINDOW_H
#define STATSWINDOW_H

#include <QDialog>

namespace Ui {
class StatsWindow;
}

class StatsWindow : public QDialog
{
    Q_OBJECT

public:
    explicit StatsWindow(QWidget *parent = 0);
    ~StatsWindow();

private slots:
    void handleExit();
private:
    Ui::StatsWindow *ui;
};

#endif // STATSWINDOW_H
