#include "Game/Entity.h"

#include <QDomDocument>
#include <QFile>
#include <QResource>

Entity::Entity(QGraphicsItem *parent) : QObject(nullptr), QGraphicsPixmapItem(parent)
{
}

void Entity::initSpritesheets(QString xmlPath, QString srcImgPath)
{
    //Load the image
    QPixmap src(srcImgPath);
    if(!src.isNull()){
        this->srcImg = src;

        //Load the XML
        QDomDocument doc;
        QFile file(xmlPath);

        if(!file.open(QIODevice::ReadOnly)){
            qDebug() << "Failed to load spritesheet from XML. Could not open XML doc." << xmlPath;
        }
        else{
            doc.setContent(&file);
            file.close();

            //Free any spritesheets in use
            this->clearSpritesheets();

            //Load all frames
            QDomElement root = doc.documentElement();
            QDomElement child = root.firstChild().toElement();

            while(!child.isNull()){
                int typeIndex = child.attribute("type", "0").toInt();
                int dirIndex = child.attribute("dir", "0").toInt();

                //Bound the input
                if(typeIndex >= N_TYPES){
                    typeIndex = 0;
                }
                else if(typeIndex < 0){
                    typeIndex = 0;
                }
                if(dirIndex >= N_DIRS){
                    dirIndex = 0;
                }
                else if(dirIndex < 0){
                    dirIndex = 0;
                }

                //Cast to their enums
                SpriteType type = static_cast<SpriteType>(typeIndex);
                Direction dir = static_cast<Direction>(dirIndex);

                //Load sprite index and period
                int index = child.attribute("index", "0").toInt();
                int period = child.attribute("period", "200").toInt();

                //Load sprite positions/rects
                QPointF origin = stringToPointF(child.attribute("origin", "(0,0)"));
                //NOT LOADING ANCHOR RIGHT NOW. No use for it yet
                QRectF rect = stringToRectF(child.attribute("rect", "(0,0,0,0)"));

                //Construct a frame from the elements
                Spritesheet::Frame frame;
                frame.rect = rect;
                frame.origin = origin;
                frame.period = period;

                //Add the frame to the correct spritesheet
                this->addFrame(frame, type, dir, index);

                //Proceed to next child
                child = child.nextSibling().toElement();
            }

            this->setSheet(IDLE, NORTH);
        }
    }
}

void Entity::initSprite(SpriteType t, Direction dir, Spritesheet *sheet)
{
    this->sprites[t][dir] = sheet;
}

void Entity::setDir(Direction dir)
{
    this->currentDir = dir;
    this->refreshSheet();
}

void Entity::setAnim(SpriteType type)
{
    this->currentSprite = type;
    this->refreshSheet();
}

void Entity::setSheet(SpriteType type, Direction dir)
{
    this->currentDir = dir;
    this->currentSprite = type;
    this->refreshSheet();
}

void Entity::setPoint(QPointF pos)
{
    this->point = pos;
}

void Entity::setPoint(float x, float y)
{
    this->point = QPointF(static_cast<qreal>(x),static_cast<qreal>(y));
}

void Entity::setSize(QSize size)
{
    this->size = size;
}

void Entity::debug()
{
    QString debugText;

    debugText += "Entity:\t'%1'\n";
    debugText += "\tType: %2\n";
    debugText += "\tPos: (%3,%4)\n";

    debugText = debugText.arg(name).arg(typeToString(type)).arg(point.x()).arg(point.y());

    //Animation debug
    debugText += "\tSpritesheet: (%1,%2)\n";
    debugText = debugText.arg(spriteTypeToString(currentSprite)).arg(dirToString(currentDir));


    qDebug().noquote() << debugText;
}

QString Entity::typeToString(EntityType t)
{
    QString str;

    switch(t){
        case UNIT:
            str = "Unit";
            break;
        case TERRAIN:
            str = "Terrain";
            break;
        case DESTRUCTIBLE:
            str = "Destructible";
            break;
        case ITEM:
            str = "Item";
            break;
        case PROJECTILE:
            str = "Projectile";
            break;
        case EFFECT:
            str = "Effect";
            break;
        default:
            str = "UNKNOWN ENTITY TYPE";
            break;
    }

    return str;
}

void Entity::setName(QString name)
{
    this->name = name;
}

void Entity::setType(EntityType type)
{
    this->type = type;
}

QString Entity::getName()
{
    return this->name;
}

EntityType Entity::getType()
{
    return this->type;
}

void Entity::setSprite(QPixmap pix, Spritesheet::Frame frame)
{
    this->setPixmap(pix);

    //Adjust our position to be centered at the origin
    QPointF origin = frame.origin - frame.rect.topLeft();

    //Reflect the y axis
    origin.setY(-origin.y());

    QPointF newPos = this->point - origin;  //Subtract because we want to move the origin in the opposite direction

    //Reflect the y axis
    newPos.setY(-newPos.y());

    this->setPos(newPos);
}

void Entity::refreshSheet()
{
    Spritesheet *newSheet = sprites[currentSprite][currentDir];

    if(newSheet != currentSheet){
        //Stop the animation timer if running
        if(currentSheet){
            currentSheet->stop();
        }

        currentSheet = newSheet;

        //If new sheet doesn't exist, set it to default sheet
        if(!this->currentSheet){
            currentSheet = sprites[IDLE][NORTH];
        }

        //Start the sheet's animation if it exists
        if(this->currentSheet){
            currentSheet->start();
        }
    }
}

void Entity::clearSpritesheets()
{
    //Reset the current properties
    currentDir = NORTH;
    currentSprite = IDLE;
    currentSheet = nullptr;

    for(int i = 0; i < N_TYPES; i++){
        for(int j = 0; j < N_DIRS; j++){
            delete sprites[i][j];
            sprites[i][j] = nullptr;
        }
    }
}

void Entity::addFrame(Spritesheet::Frame frame, SpriteType type, Direction dir, int index)
{
    Spritesheet *sheet = sprites[type][dir];

    if(!sheet){
        sheet = new Spritesheet(this->srcImg, this);
        connect(sheet, SIGNAL(newFrameAvailable(QPixmap, Spritesheet::Frame)), this, SLOT(setSprite(QPixmap, Spritesheet::Frame)));
    }

    sheet->addFrame(index, frame);

    sprites[type][dir] = sheet;
}
