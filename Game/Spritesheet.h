#ifndef SPRITESHEET_H
#define SPRITESHEET_H

#include <QObject>
#include <QRect>
#include <QPixmap>
#include <QTimer>

class Spritesheet : public QObject
{
    Q_OBJECT
public:
    explicit Spritesheet(QPixmap srcImg, QObject *parent = nullptr);

    struct Frame{
        QRectF rect;
        int period = 200;   //ms
        QPointF origin;
    };

    void addFrame(int index, Frame frame);
    void setFrame(int index, Frame frame);

    QPixmap getCurrentFrame();

    //debug functions
    static void debug(Frame *frame);
    static void debug(Spritesheet *sheet);
    void debug();

signals:
    void newFrameAvailable(QPixmap pix, Spritesheet::Frame f);

public slots:
    void stop();
    void start();

private slots:
    void advanceAnimFrame();

private:
    QList<Frame> frames;
    QPixmap currentFrame;
    QPixmap srcImg;
    int currentIndex = 0;
    QTimer *animTimer = nullptr;
};

#endif // SPRITESHEET_H
