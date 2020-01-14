#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "sprite.h"
#include "graphicsview.h"
#include "SpriteCreator/spritecreator.h"
#include "SpriteCreator/LevelDesigner.h"
#include "SpriteCreator/ResourceManager.h"

#include <QMainWindow>

#define PLACE_SIZE              10
#define DEFAULT_FRAME_RATE      1000/5     //milliseconds not hertz

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

private:
    Ui::MainWindow *ui;

    SpriteCreator *spritePage               = nullptr;
    LevelDesigner *levelDesignerPage        = nullptr;
    ResourceManager *resourceManagerPage    = nullptr;

};

#endif // MAINWINDOW_H
