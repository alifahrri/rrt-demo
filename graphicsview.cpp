#include "graphicsview.h"
#include <QKeyEvent>

GraphicsView::GraphicsView(QWidget *parent)
{

}

void GraphicsView::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_Space)
    {
        if(callback)
            callback(50);
    }
}
