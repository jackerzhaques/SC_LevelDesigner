#include "Game/Spritesheet.h"

#include <QDebug>

Spritesheet::Spritesheet(QPixmap srcImg, QObject *parent) : QObject(parent)
{
    this->srcImg = srcImg;

    animTimer = new QTimer(this);
    connect(animTimer, SIGNAL(timeout()), this, SLOT(advanceAnimFrame()));
}

void Spritesheet::addFrame(int index, Frame frame)
{
    //If the index is negative, insert the index at the end
    //If the index is greater than the maximum, insert it at the end
    if(index < 0 || index >= frames.size()){
        frames.append(frame);
    }
    else{
        frames.insert(index, frame);
    }
}

void Spritesheet::setFrame(int index, Frame frame)
{
    //If the index is negative, just add a new frame.
    if(index < 0){
        this->addFrame(-1, frame);
    }
    else{
        //Replace the frame if it exists
        if(index < this->frames.size()){
            this->frames.replace(index, frame);
        }
    }
}

QPixmap Spritesheet::getCurrentFrame()
{
    return currentFrame;
}

void Spritesheet::advanceAnimFrame()
{
    //Bound the current index
    if(currentIndex < 0){
        currentIndex = 0;
    }
    else if(currentIndex >= frames.size()){
        currentIndex = 0;
    }
    else{
        //Do nothing
    }

    this->currentFrame = srcImg.copy(frames[currentIndex].rect.toRect());

    emit newFrameAvailable(currentFrame, frames[currentIndex]);

    //Adjust the timer period
    animTimer->start(frames[currentIndex].period);

    this->currentIndex++;
}

void Spritesheet::stop()
{
    this->animTimer->stop();
}

void Spritesheet::start()
{
    this->currentIndex = 0;
    animTimer->start(frames[currentIndex].period);
}

void Spritesheet::debug(Spritesheet::Frame *frame)
{
    qDebug() << "Frame: ";

    //Rect
    QString rectStr = "(%1,%2,%3,%4)";
    rectStr = rectStr.arg(frame->rect.x()).arg(frame->rect.y()).arg(frame->rect.width()).arg(frame->rect.height());
    qDebug() << "\tRect: " << rectStr;

    //Origin
    QString origStr = "(%1,%2)";
    origStr = origStr.arg(frame->origin.x()).arg(frame->origin.y());
    qDebug() << "\tOrigin: " << origStr;

    //Period
    qDebug() << "\tPeriod: " << frame->period;
}

void Spritesheet::debug(Spritesheet *sheet)
{
    if(sheet){
        sheet->debug();
    }
    else{
        qDebug() << "Spritesheet: Null sheet";
    }
}

void Spritesheet::debug()
{
    qDebug() << "Sheet: ";

    if(!this->srcImg){
        qDebug() << "Source Image: No source";
    }
    else{
        qDebug() << "Source Image: Has source";
    }

    qDebug() << "Frames: ";

    for(Frame f : frames){
        debug(&f);
    }
}
