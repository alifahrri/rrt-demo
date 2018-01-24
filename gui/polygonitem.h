#ifndef POLYGONITEM_H
#define POLYGONITEM_H

#include <QGraphicsItem>

class Polygon;

class PolygonItem : public QGraphicsItem
{
public:
    PolygonItem(Polygon &poly);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
private:
    Polygon& polygon;
};

class PolygonsItem : public QGraphicsItem
{
public:
    PolygonsItem(const std::vector<Polygon>& _polygons);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
private:
    const std::vector<Polygon>& polygons;
};

#endif // POLYGONITEM_H
