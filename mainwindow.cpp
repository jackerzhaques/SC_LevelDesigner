#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->levelDesignerPage = new LevelDesigner(this);
    ui->tabWidget->addTab(levelDesignerPage, "Level Designer");

    this->spritePage = new SpriteCreator(this);
    ui->tabWidget->addTab(spritePage, "Spritesheet Editor");

    this->resourceManagerPage = new ResourceManager(this);
    ui->tabWidget->addTab(resourceManagerPage, "Resource Manager");

    //Testing
    ui->tabWidget->setCurrentIndex(2);
}

MainWindow::~MainWindow()
{
    delete ui;
}
