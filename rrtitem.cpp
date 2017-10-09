#include "rrtitem.h"
#include "rrt.h"
#include <QPainter>
#include <QGraphicsScene>

#define MAX(A,B) (A>B?A:B)

RRTItem::RRTItem(RRT &rrt) :
    rrt_(rrt),
    bound_rect(QRectF(QPoint(-10,-10),QPoint(10,10)))
{

}

void RRTItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    auto points = rrt_.getPoints();
    auto parent = rrt_.getParentMap();
    auto child = rrt_.getChildMap();
    QVector<QLineF> lines;
    auto min_x = 0.0;
    auto min_y = 0.0;
    auto max_x = 0.0;
    auto max_y = 0.0;

    static int color_select = 0;
    color_select++;
    color_select = color_select%10;
    painter->setPen(QColor(color_select,0,color_select));
    painter->setBrush(QColor(color_select,0,color_select,127));


    for(size_t i=0; i<rrt_.size(); i++)
    {
        auto x = points[i].x;
        auto y = points[i].y;
        auto px = points[MAX(parent[i],0)].x;
        auto py = points[MAX(parent[i],0)].y;
        if(x<min_x)
            min_x = x;
        else if(x>max_x)
            max_x = x;
        if(y<min_y)
            min_y = y;
        else if(y>max_y)
            max_y = y;
        painter->drawEllipse(QPointF(x,y),1.0,1.0);
        lines.push_back(QLineF(QPointF(x,y),QPointF(px,py)));
    }
//    painter->setPen(QColor(0,0,0,127));
    painter->drawLines(lines);
    painter->setPen(Qt::blue);
    painter->drawText(QPointF(scene()->sceneRect().topLeft()+QPointF(20,20)),QString::number(rrt_.getIteration()));
    bound_rect = QRectF(QPointF(min_x,min_y),QPointF(max_x,max_y));
}

QRectF RRTItem::boundingRect() const
{
    return bound_rect;
}
