#ifndef SPRITE_H
#define SPRITE_H

#include <QObject>
#include <QPointF>
#include <QRectF>
#include <QPixmap>

class Sprite : public QObject
{
    Q_OBJECT
public:
    explicit Sprite(QObject *parent = nullptr);

    enum Direction{
        NORTH   = 0,
        SOUTH   = 1,
        EAST    = 2,
        WEST    = 3,
        N_DIRS  = 4
    };

    enum SpriteType{
        IDLE    = 0,
        WALK    = 1,
        CAST    = 2,
        SHOOT   = 3,
        DEATH   = 4,
        DEAD    = 5,
        N_TYPES = 6
    };

    void setType(SpriteType Type);
    void setDir(Direction Dir);
    void setOrigin(QPointF Origin);
    void setAnchor(QPointF Anchor);
    void setRect(QRectF rect);
    void setPeriod(int period);

    SpriteType type();
    Direction dir();
    QPointF origin();
    QPointF anchor();
    QRectF rect();
    int period();

    void CopyTo(Sprite* s);

signals:

public slots:

private:
    SpriteType Type         = IDLE;
    Direction Dir           = NORTH;
    QPointF Origin;
    QPointF Anchor;
    QRectF Rect;
    int Period = 200;
};

#endif // SPRITE_H
