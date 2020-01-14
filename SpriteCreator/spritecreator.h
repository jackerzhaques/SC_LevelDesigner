#ifndef SPRITECREATOR_H
#define SPRITECREATOR_H

#include "sprite.h"
#include "graphicsview.h"

#include <QMainWindow>
#include <QList>
#include <QString>
#include <QDebug>
#include <QFileDialog>
#include <QUrl>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <QKeyEvent>
#include <QTimer>
#include <QtXml/QDomElement>
#include <QtXml/QDomDocument>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QWidget>

#define PLACE_SIZE              10
#define DEFAULT_FRAME_RATE      1000/5     //milliseconds not hertz

namespace Ui {
class SpriteCreator;
}

class SpriteCreator : public QWidget
{
    Q_OBJECT

public:
    explicit SpriteCreator(QWidget *parent = nullptr);
    ~SpriteCreator();

private slots:
    void FullSpritesheetClicked(QPoint pos);
    void ZoomedSpritesheetClicked(QPoint pos);
    void FullSpritesheetMouseMoved(QPointF pos);
    void ZoomedSpritesheetMouseMoved(QPointF pos);
    void AdvanceAnimationFrame();

    //GUI Callbacks
    void on_AddFrameButton_released();

    void on_SpriteList_currentRowChanged(int currentRow);

    void on_SpriteDirCombo_currentIndexChanged(int index);

    void on_OpenSpriteButton_released();

    void on_PlaceModeCombo_currentIndexChanged(int index);

    void on_SpriteTypeCombo_currentIndexChanged(int index);

    void on_AutoplayCheck_toggled(bool checked);

    void on_HideOriginCheck_toggled(bool checked);

    void on_ScaleSpriteSlider_valueChanged(int value);

    void on_RemoveFrameButton_released();

    void on_SaveAsButton_released();

    void on_SpritePeriodInput_valueChanged(int arg1);

private:
    enum PlaceMode{
        NORMAL      = 0,
        ANCHOR      = 1,
        ORIGIN      = 2,
        DRAG        = 3,
        N_MODES     = 4
    };

    Ui::SpriteCreator *ui;
    QString SpritesheetSource;
    QString SpritesheetFilePath;
    QList<QList<QList<Sprite*>>> Sprites;   //First dimension is type, second dimension is direction
    QPointF SavedPlacePos;                  //Used for saving the pos of the object being placed.
    Sprite *CurrentSprite                   = nullptr;
    PlaceMode PlacingMode                   = NORMAL;
    QString TypeStrings[Sprite::N_TYPES]    = {"Idle", "Walk", "Cast", "Shoot", "Death", "Dead"};
    QString DirStrings[Sprite::N_DIRS]      = {"North", "South", "East", "West"};
    QGraphicsView *FullSheetView            = nullptr;
    GraphicsView *SpriteEditView            = nullptr;
    GraphicsView *SpritePreview             = nullptr;
    QGraphicsScene *SpritesheetScene        = nullptr;
    QGraphicsScene *AnimatedSpriteScene     = nullptr;
    QGraphicsPixmapItem *FullSpritesheet    = nullptr;
    QGraphicsRectItem *SpritesheetSelection = nullptr;
    QGraphicsRectItem *ZoomedSelection      = nullptr;
    QGraphicsEllipseItem *Anchor            = nullptr;
    QGraphicsEllipseItem *Origin            = nullptr;
    QGraphicsPixmapItem *AnimatedSprite     = nullptr;
    QGraphicsEllipseItem *AnimationOrigin   = nullptr;
    QPoint ObjectPos                        = QPoint(0,0);
    double AnimationViewPercentage          = 0.85;
    QTimer *AnimationTimer                  = nullptr;
    int CurrentFrame                        = 0;        //Animation frame
    bool AutoplayEnabled                    = true;

    void AddSprite();
    void AddSprite(Sprite::SpriteType type, Sprite::Direction dir, QPointF anchor,
                   QPointF origin, QRectF rect, int index, int period);
    void ClearSprites();
    void RemoveSelectedSprite();
    void RefreshList();
    void SaveCurrentSprite();
    void RefreshCurrentSprite();
    void AdjustSelectionRect(QPointF target);
    void AdjustZoomedView();
    void keyPressEvent(QKeyEvent *keyEvent);
    void SavePlacingObjectPos();
    void SetPlacingObjectPos();
    void SetPlacingMode(PlaceMode mode);
    void HandleClick(QPointF pos);
    void HandleDrag(QPointF pos);
    void SetEllipseObjectPos(QGraphicsEllipseItem *item, QPointF pos);
    void SetRectObjectPos(QGraphicsRectItem *item, QPointF pos);
    void SetAnimation();
    void ScaleAnimatedSprite(double ViewPercentage);
    QString ConvertToXML();
    void OpenImage(const QString &filePath);
    void OpenXML(const QString &filePath);
    QPointF StringToPointF(QString string);
    QRectF StringToRectF(QString string);

};

#endif // SPRITECREATOR_H
