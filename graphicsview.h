#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QGraphicsView>
#include <functional>

class GraphicsView : public QGraphicsView
{
    typedef std::function<void(int)> Callback;
public:
    GraphicsView(QWidget* parent=nullptr);
protected:
    void keyPressEvent(QKeyEvent *event);
public:
    Callback callback = nullptr;
};

#endif // GRAPHICSVIEW_H
