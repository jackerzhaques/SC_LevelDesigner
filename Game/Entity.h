#ifndef ENTITY_H
#define ENTITY_H

#include "Globals.h"

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QDebug>

#include "Game/Spritesheet.h"

class Entity : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Entity(QGraphicsItem *parent = nullptr);

    //Init functions
    void initSpritesheets(QString xmlPath, QString srcImgPath);
    void initSprite(SpriteType t, Direction dir, Spritesheet *sheet);

    //Movement and anim functions
    void setDir(Direction dir);
    void setAnim(SpriteType type);
    void setSheet(SpriteType type, Direction dir);
    void setPoint(QPointF pos);
    void setPoint(float x, float y);
    void setSize(QSize size);

    //Debugging functions
    void debug();
    QString typeToString(EntityType t);

    //Setters
    void setName(QString name);
    void setType(EntityType type);

    //Getters
    QString getName();
    EntityType getType();

signals:

public slots:

private slots:
    void setSprite(QPixmap pix, Spritesheet::Frame frame);

private:
    //Entity spritesheet variables
    Spritesheet *sprites[N_TYPES][N_DIRS] = {{nullptr}};
    Spritesheet *currentSheet = sprites[IDLE][NORTH];
    Direction currentDir = NORTH;
    SpriteType currentSprite = IDLE;
    QPixmap srcImg;
    double scalingFactor = 1.0;

    //Entitiy scene variables
    QPointF point;
    QSize size;

    //Entity properties
    QString name    = "EMPTY ENTITY";
    EntityType type = TERRAIN;

    //Private movement and anim functions
    void refreshSheet();
    void clearSpritesheets();
    void addFrame(Spritesheet::Frame frame, SpriteType type, Direction dir, int index);

};

#endif // ENTITY_H
