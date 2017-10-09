#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QGraphicsView>
#include <functional>

class GraphicsView : public QGraphicsView
{
    typedef std::function<void(int)> Callback;
    typedef std::function<void(int,QVector<QPointF>)> MouseCallback;
public:
    GraphicsView(QWidget* parent=nullptr);
protected:
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);
private:
    QVector<QPointF> pts;
public:
    Callback callback = nullptr;
    MouseCallback mouse_callback = nullptr;
};

#endif // GRAPHICSVIEW_H
