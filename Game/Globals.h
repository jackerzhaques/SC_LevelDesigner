#ifndef GLOBALS_H
#define GLOBALS_H

#include <QString>
#include <QStringList>
#include <QPoint>
#include <QRect>

#define INT_TEXT        "[INT]"
#define STR_TEXT        "[STR]"
#define AGI_TEXT        "[AGI]"
#define CON_TEXT        "[CON]"
#define SPI_TEXT        "[SPI]"
#define HP_TEXT         "[HP]"
#define MP_TEXT         "[MP]"
#define ULVL_TEXT       "[ULVL]"
#define ALVL_TEXT       "[ALVL]"

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

enum EntityType{
    UNIT,
    TERRAIN,
    DESTRUCTIBLE,
    ITEM,
    PROJECTILE,
    EFFECT,
    N_ENTITY_TYPES,
};

enum ManaType{
    MANA,
    ENERGY,
    RAGE,
    N_MANA_TYPES,
};

enum AttackType{
    MELEE,
    MELEE_CLEAVE,
    MISSILE,
    MISSILE_BOUNCE,
    MISSILE_SPLASH,
    INSTANT,
    N_ATTACK_TYPES,
};

enum MovementType{
    NORMAL,
    FLY,
    N_MOVEMENT_TYPES,
};

enum TargetType{
    NO_TARGET,
    POINT_TARGET,
    UNIT_TARGET,
    N_TARGET_TYPES
};

enum AttributeType{
    STR,
    INT,
    AGI,
    CON,
    SPI,
    HP,
    MP,
    ULVL,               //Unit level
    ALVL,               //Ability level
    N_ATTRIBUTE_TYPES
};

struct Attributes{
    double str;
    double inte;
    double agi;
    double con;
    double spi;
    double hp;
    double mp;
    double ulvl;    //Unit level
    double alvl;    //Ability level
};

QString manaTypeToString(ManaType type);
QString attackTypeToString(AttackType type);
QString movementTypeToString(MovementType type);
QString targetTypeToString(TargetType type);

QString spriteTypeToString(SpriteType type);
QString dirToString(Direction dir);

QString attributeTypeToString(AttributeType type);

QPointF stringToPointF(QString str);
QRectF stringToRectF(QString str);
QString pointToString(QPointF point);
AttributeType stringToAttributeType(QString str);

#endif // GLOBALS_H
