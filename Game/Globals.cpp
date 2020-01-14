#include "Globals.h"

#include <QDebug>

QString spriteTypeToString(SpriteType type)
{
    QString str;

    switch(type){
        case IDLE:
            str = "Idle";
            break;
        case WALK:
            str = "Walk";
            break;
        case CAST:
            str = "Cast";
            break;
        case SHOOT:
            str = "Shoot";
            break;
        case DEATH:
            str = "Death";
            break;
        case DEAD:
            str = "Dead";
            break;
        default:
            str = "UNKNOWN SPRITE TYPE";
            break;
    }

    return str;
}



QString dirToString(Direction dir)
{
    QString str;

    switch(dir){
        case NORTH:
            str = "North";
            break;
        case SOUTH:
            str = "South";
            break;
        case EAST:
            str = "East";
            break;
        case WEST:
            str = "West";
            break;
        default:
            str = "UNKNOWN DIRECTION";
            break;
    }

    return str;
}

#include "Globals.h"

QPointF stringToPointF(QString str)
{
    //Remove parenthesis in front and back
    str.remove(0,1);
    str.remove(str.size() - 1, 1);

    //Separate the two numbers
    QStringList posAsStrings = str.split(",");

    if(posAsStrings.size() == 2){
        bool x_ok = false;
        bool y_ok = false;
        double x = posAsStrings[0].toDouble(&x_ok);
        double y = posAsStrings[1].toDouble(&y_ok);

        if(x_ok & y_ok){
            //Conversion succeeded
            return QPointF(x,y);
        }
    }

    //Conversion failed
    qDebug() << "Position string is corrupted" << str;
    return QPointF(0,0);
}

QRectF stringToRectF(QString str)
{
    //Remove parenthesis in front and back
    str.remove(0,1);
    str.remove(str.size() - 1, 1);

    //Separate the numbers
    QStringList posAsStrings = str.split(",");

    if(posAsStrings.size() == 4){
        bool x_ok = false;
        bool y_ok = false;
        bool w_ok = false;
        bool h_ok = false;
        double x = posAsStrings[0].toDouble(&x_ok);
        double y = posAsStrings[1].toDouble(&y_ok);
        double w = posAsStrings[2].toDouble(&w_ok);
        double h = posAsStrings[3].toDouble(&h_ok);

        if(x_ok && y_ok && w_ok && h_ok){
            //Conversion succeeded
            return QRectF(x,y,w,h);
        }
    }

    //Conversion failed
    qDebug() << "Position string is corrupted: " << str;
    return QRectF(0,0,1,1);
}

QString manaTypeToString(ManaType type)
{
    QString str = "";

    switch(type){
        case MANA:
            str = "Mana";
            break;
        case ENERGY:
            str = "Energy";
            break;
        case RAGE:
            str = "Rage";
            break;
        default:
            str = "UNKNOWN MANA TYPE";
            break;
        }

    return str;
}

QString attackTypeToString(AttackType type)
{
    QString str = "";

    switch(type){
        case MELEE:
            str = "Melee";
            break;
        case MELEE_CLEAVE:
            str = "Melee (Cleave)";
            break;
        case MISSILE:
            str = "Missile";
            break;
        case MISSILE_BOUNCE:
            str = "Missile (Bounce)";
            break;
        case MISSILE_SPLASH:
            str = "Missile (Splash)";
            break;
        case INSTANT:
            str = "Instant";
            break;
        default:
            str = "UNKNOWN ATTACK TYPE";
            break;
        }

    return str;
}

QString movementTypeToString(MovementType type)
{
    QString str = "";

    switch(type){
        case NORMAL:
            str = "Normal";
            break;
        case FLY:
            str = "Fly";
            break;
        default:
            str = "UNKNOWN MOVEMENT TYPE";
            break;
        }

    return str;
}

QString pointToString(QPointF point)
{
    QString str = QString("(%1,%2)").arg(point.x()).arg(point.y());
    return str;
}

QString targetTypeToString(TargetType type)
{
    QString str = "";

    switch(type){
        case NO_TARGET:
            str = "No Target";
            break;
        case POINT_TARGET:
            str = "Point Target";
            break;
        case UNIT_TARGET:
            str = "Unit Target";
            break;
        default:
            str = "UNKNOWN TARGET TYPE";
            break;
    }

    return str;
}

AttributeType stringToAttributeType(QString str)
{
    AttributeType type = STR;

    if(str == STR_TEXT){
        type = STR;
    }
    else if(str == INT_TEXT){
        type = INT;
    }
    else if(str == AGI_TEXT){
        type = AGI;
    }
    else if(str == CON_TEXT){
        type = CON;
    }
    else if(str == SPI_TEXT){
        type = SPI;
    }
    else if(str == HP_TEXT){
        type = HP;
    }
    else if(str == MP_TEXT){
        type = MP;
    }
    else if(str == ULVL_TEXT){
        type = ULVL;
    }
    else if(str == ALVL_TEXT){
        type = ALVL;
    }
    else{
        //Invalid type
        type = N_ATTRIBUTE_TYPES;
    }

    return type;
}

QString attributeTypeToString(AttributeType type)
{
    QString str = "";

    switch(type){
        case STR:
            str = "STR";
            break;
        case INT:
            str = "INT";
            break;
        case AGI:
            str = "AGI";
            break;
        case CON:
            str = "CON";
            break;
        case SPI:
            str = "SPI";
            break;
        case HP:
            str = "HP";
            break;
        case MP:
            str = "MP";
            break;
        case ULVL:
            str = "ULVL";
            break;
        case ALVL:
            str = "ALVL";
            break;
        default:
            str = "INVALID ATTRIBUTE TYPE";
            break;
    }

    return str;
}
