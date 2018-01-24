#ifndef RRTITEM_H
#define RRTITEM_H

#include <QGraphicsItem>

class RRT;

class RRTItem : public QGraphicsItem
{
public:
    RRTItem(RRT& rrt);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
private:
    RRT &rrt_;
    QRectF bound_rect;
};

#endif // RRTITEM_H
