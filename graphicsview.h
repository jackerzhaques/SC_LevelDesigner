#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QGraphicsView>
#include <QMouseEvent>
#include <QPoint>
#include <QGraphicsSceneMouseEvent>

class GraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    GraphicsView(QWidget *parent);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent* mouseEvent);

signals:
    void mousePressed(QPoint pos);
    void mouseMoved(QPointF pos);
};

#endif // GRAPHICSVIEW_H
