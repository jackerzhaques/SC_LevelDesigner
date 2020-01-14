#include "LevelDesigner.h"
#include "ui_LevelDesigner.h"

#include <QGraphicsEllipseItem>

#include <QTimer>

#include "Game/Camera.h"

static void add(QRectF rect, QGraphicsScene *s){
    auto *i = new QGraphicsEllipseItem();
    i->setRect(rect);
    s->addItem(i);
}

LevelDesigner::LevelDesigner(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LevelDesigner)
{
    ui->setupUi(this);

    this->scene = new QGraphicsScene(ui->View);
    //scene->setSceneRect(-10000,-10000,10000,10000);
    ui->View->setScene(scene);

    auto *e = new Entity();
    e->setPoint(100,100);
    scene->addItem(e);

    add(QRectF(-5,-5,10,10), scene);
    add(QRectF(-105,-105,10,10), scene);
    add(QRectF(-105,95,10,10), scene);
    add(QRectF(95,-105,10,10), scene);
    add(QRectF(95,95,10,10), scene);

    e->initSpritesheets("P:/QtProjects/Gingerspice/LevelDesigner/Resources/Spritesheets/Units/Sara.xml", "P:/QtProjects/Gingerspice/LevelDesigner/Resources/Spritesheets/Units/Sara.png");
    e->debug();

    this->camera = new Camera(this, ui->View);
}

LevelDesigner::~LevelDesigner()
{
    delete ui;
}
