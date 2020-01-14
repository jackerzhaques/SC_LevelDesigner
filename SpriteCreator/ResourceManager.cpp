#include "ResourceManager.h"
#include "ui_ResourceManager.h"

#include <QFileDialog>

ResourceManager::ResourceManager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ResourceManager)
{
    ui->setupUi(this);

    unitManager = new UnitManager(ui->tabWidget);
    connect(unitManager, SIGNAL(unitChanged()), this, SLOT(saveResourceFile()));

    abilityManager = new AbilityManager(ui->tabWidget);
    connect(abilityManager, SIGNAL(itemChanged()), this, SLOT(saveResourceFile()));

    assetManager = new AssetManager(ui->tabWidget);
    connect(assetManager, SIGNAL(itemChanged()), this, SLOT(saveResourceFile()));

    ui->tabWidget->addTab(unitManager, "Units");
    ui->tabWidget->addTab(abilityManager, "Abilities");
    ui->tabWidget->addTab(assetManager, "Assets");
    ui->tabWidget->setCurrentIndex(3);
}

ResourceManager::~ResourceManager()
{
    delete ui;
}

QString ResourceManager::toXML()
{
    QString xmlString;

    QDomDocument doc;

    doc.appendChild(unitManager->getXML(&doc));
    doc.appendChild(abilityManager->getXML(&doc));

    xmlString = doc.toString();

    return xmlString;
}

void ResourceManager::on_ResourceFileBrowseButton_released()
{
    QString projectPath = "P:/QtProjects/Gingerspice/LevelDesigner";
    QString path = QFileDialog::getSaveFileName(
                this,
                "Open Resource File",
                projectPath + "/Resources/",
                "Resource Files (*.ldr);;All Files (*.*)");

    //Create the file if it doesn't exist
    QStringList parts = path.split('/');
    parts.removeLast();
    QDir dir;
    if(!dir.exists(parts.join('/'))){
        dir.mkpath(parts.join('/'));
    }

    //QFile file(path);
    //file.open(QIODevice::WriteOnly);

    ui->ResourceFileInput->setText(path);
    this->resourceFilePath = path;
    this->assetManager->setResourceFilePath(path);
}

void ResourceManager::loadResourceFile()
{

}

void ResourceManager::saveResourceFile()
{
    QFile file(this->resourceFilePath);

    if(file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)){
        QTextStream out(&file);
        out << this->toXML();
        file.close();
    }
    else{
        qDebug() << "ResourceManager: Unable to open XML File";
    }
}

void ResourceManager::on_ResourceFileSaveButton_released()
{
    this->saveResourceFile();
}
