#include "graphicsview.h"
#include <QDebug>

GraphicsView::GraphicsView(QWidget *parent) : QGraphicsView (parent)
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
