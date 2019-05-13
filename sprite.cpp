#include "sprite.h"

#include <QDebug>

Sprite::Sprite(QObject *parent) : QObject(parent)
{
}

void Sprite::setType(Sprite::SpriteType Type)
{
    this->Type = Type;
}

Sprite::SpriteType Sprite::type()
{
    return this->Type;
}

void Sprite::setDir(Sprite::Direction Dir)
{
    this->Dir = Dir;
}

Sprite::Direction Sprite::dir()
{
    return this->Dir;
}

void Sprite::setOrigin(QPointF Origin)
{
    this->Origin = Origin;
}

QPointF Sprite::origin()
{
    return this->Origin;
}

void Sprite::setAnchor(QPointF Anchor)
{
    this->Anchor.setX(Anchor.x());
    this->Anchor.setY(Anchor.y());
}

QPointF Sprite::anchor()
{
    return this->Anchor;
}

void Sprite::setRect(QRectF rect)
{
    this->Rect = rect;
}

void Sprite::setPeriod(int period)
{
    this->Period = period;
}

QRectF Sprite::rect()
{
    return this->Rect;
}

int Sprite::period()
{
    return this->Period;
}

void Sprite::CopyTo(Sprite *s)
{
    s->Origin = this->Origin;
    s->Anchor = this->Anchor;
    s->Rect = this->Rect;
    s->Type = this->Type;
    s->Dir = this->Dir;
}
