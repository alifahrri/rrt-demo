#include "mainwindow.h"
#include <QApplication>
#include "rrt.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RRT rrt;
    MainWindow w(rrt);
    w.show();

    return a.exec();
}
