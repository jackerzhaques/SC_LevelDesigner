#include "graphicsview.h"
#include <QDebug>

GraphicsView::GraphicsView()
{

}

void GraphicsView::mousePressEvent(QMouseEvent *event)
{
    QGraphicsView::mousePressEvent(event);

    if(event->button() == Qt::LeftButton){
        event->accept();
        emit mousePressed(event->pos());
    }
}

void GraphicsView::mouseMoveEvent(QMouseEvent *mouseEvent)
{
    emit mouseMoved(mouseEvent->pos());

    this->update();
}
