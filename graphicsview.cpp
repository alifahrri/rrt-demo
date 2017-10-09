#include "graphicsview.h"
#include <QKeyEvent>
#include <QMouseEvent>

GraphicsView::GraphicsView(QWidget *parent)
{

}

void GraphicsView::keyPressEvent(QKeyEvent *event)
{
    if(callback)
    {
        if(event->key()==Qt::Key_Space)
            callback(1);
        else if(event->key()==Qt::Key_C)
            callback(-1);
        else if(event->key()==Qt::Key_O)
            callback(-2);
    }
}

void GraphicsView::mousePressEvent(QMouseEvent *event)
{
    if(mouse_callback)
    {
        switch (event->button()) {
        case Qt::LeftButton:
            switch (event->modifiers()) {
            case Qt::ShiftModifier:
                pts.push_back(mapToScene(event->pos()));
                break;
            default:
                if(pts.size()>=3)
                    mouse_callback(1,pts);
                pts.clear();
                break;
            }
            break;
        case Qt::RightButton:
            break;
        case Qt::MiddleButton:
            pts.clear();
            mouse_callback(0,pts);
            break;
        default:
            break;
        }
    }
}
