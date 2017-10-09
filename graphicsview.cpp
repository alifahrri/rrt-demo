#include "graphicsview.h"
#include <QKeyEvent>

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
    }
}
