#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "rrt.h"
#include "rrtitem.h"

MainWindow::MainWindow(RRT& rrt, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    rrt_(rrt),
    rrt_item(new RRTItem(rrt_))
{
    ui->setupUi(this);
    auto s = this->size();
    auto w = s.width()-30;
    auto h = s.height()-70;
    ui->graphicsView->setScene(new QGraphicsScene(-w/2,-h/2,w,h,this));
    ui->graphicsView->scene()->addItem(rrt_item);
    ui->graphicsView->setRenderHints(QPainter::Antialiasing | QPainter::HighQualityAntialiasing);
    ui->graphicsView->callback = [=](int n)
    {
        rrt_.grow(n);
        ui->graphicsView->scene()->update();
    };
}

MainWindow::~MainWindow()
{
    delete ui;
}
