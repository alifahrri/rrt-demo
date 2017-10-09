#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "rrt.h"
#include "rrtitem.h"
#include "polygonitem.h"
#include <QDebug>

MainWindow::MainWindow(RRT& rrt, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    rrt_(rrt),
    rrt_item(new RRTItem(rrt_)),
    polygon_item(new PolygonsItem(rrt_.getObstacles()))
{
    ui->setupUi(this);
    auto s = this->size();
    auto w = s.width()-30;
    auto h = s.height()-70;
    ui->graphicsView->setScene(new QGraphicsScene(-w/2,-h/2,w,h,this));
    ui->graphicsView->scene()->addItem(polygon_item);
    ui->graphicsView->scene()->addItem(rrt_item);
    ui->graphicsView->setRenderHints(QPainter::Antialiasing | QPainter::HighQualityAntialiasing);
    ui->graphicsView->callback = [=](int n)
    {
        if(n>0)
            rrt_.grow(n);
        else if(n==-1)
            rrt_.clear();
        else if(n==-2)
            rrt_.clearObstacles();
        ui->graphicsView->scene()->update();
    };
    ui->graphicsView->mouse_callback = [=](int i, QVector<QPointF> pts)
    {
        if(i)
        {
            std::vector<Line::Point> points;
            for(const auto& p : pts)
                points.push_back(Line::Point(p.x(),p.y()));
            rrt_.addObstacles({Polygon(points)});
            qDebug() << pts;
        }
        else
            rrt_.clearObstacles();
        ui->graphicsView->scene()->update();
    };

    setWindowTitle("RRT Test");
}

MainWindow::~MainWindow()
{
    delete ui;
}
