#ifndef LEVELDESIGNER_H
#define LEVELDESIGNER_H

#include <QWidget>

#include "Game/Entity.h"
#include "Game/Camera.h"

#include <QGraphicsView>
#include <QGraphicsScene>


namespace Ui {
class LevelDesigner;
}

class LevelDesigner : public QWidget
{
    Q_OBJECT

public:
    explicit LevelDesigner(QWidget *parent = nullptr);
    ~LevelDesigner();

private:
    Ui::LevelDesigner *ui;

    QGraphicsScene *scene = nullptr;
    Camera *camera = nullptr;
};

#endif // LEVELDESIGNER_H
