#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class RRT;
class RRTItem;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(RRT& rrt, QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    RRT& rrt_;
    RRTItem *rrt_item;
};

#endif // MAINWINDOW_H
