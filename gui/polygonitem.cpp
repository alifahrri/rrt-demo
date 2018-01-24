#include "polygonitem.h"
#include "polygon.h"
#include <QPainter>

PolygonItem::PolygonItem(Polygon &poly) :
    polygon(poly)
{

}

void PolygonItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    auto points = polygon.points();
    painter->setPen(Qt::black);
    QVector<QPointF> poly_pts;
    for(int i=0; i<points.size(); i++)
    {
        poly_pts.push_back(QPointF(points[i].x,points[i].y));
//        int next = (i+1)%points.size();
//        painter->drawLine(QPointF(points[i].x,points[i].y),
//                          QPointF(points[next].x,points[next].y));
    }
    painter->setBrush(Qt::gray);
    painter->drawPolygon(QPolygonF(poly_pts));
}

QRectF PolygonItem::boundingRect() const
{
    return QRectF(-200,-200,400,400);
}

PolygonsItem::PolygonsItem(const std::vector<Polygon> &_polygons) :
    polygons(_polygons)
{

}

void PolygonsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    std::vector<Polygon> poly = polygons;
    for(auto& p : poly)
    {
        PolygonItem p_item(p);
        p_item.paint(painter,option,widget);
    }
}

QRectF PolygonsItem::boundingRect() const
{
    return QRectF(-400,-400,800,800);
}
