#include "AssetManager.h"
#include "ui_AssetManager.h"

#include <QDebug>

AssetManager::AssetManager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AssetManager)
{
    ui->setupUi(this);

    //Initialize asset lists
    for(int i = 0; i < N_ASSET_CATEGORIES; i++){
        QList<Asset> list;
        assets.append(list);
    }

    //Get pointers to each category
    QTreeWidgetItem *spritesheetCategory = ui->List->findItems("Spritesheets", Qt::MatchExactly).first();
    QTreeWidgetItem *soundCategory = ui->List->findItems("Sounds", Qt::MatchExactly).first();

    items.append(soundCategory->child(1));
    items.append(soundCategory->child(0));
    items.append(ui->List->findItems("Images", Qt::MatchExactly).first());
    items.append(ui->List->findItems("Icons", Qt::MatchExactly).first());
    items.append(spritesheetCategory->child(0));
    items.append(spritesheetCategory->child(1));
    items.append(spritesheetCategory->child(2));
    items.append(spritesheetCategory->child(3));

    for(QTreeWidgetItem *item : items){
        qDebug() << item->text(0);
    }
}

AssetManager::~AssetManager()
{
    delete ui;
}

void AssetManager::setResourceFilePath(QString path)
{
    QStringList parts = path.split('/');
    parts.removeLast();
    QString dirPath = parts.join('/');
    QDir dir;
    if(!dir.exists(dirPath)){
        dir.mkpath(dirPath);
    }

    this->resourceFilePath = dirPath;
}

void AssetManager::on_EditTable_cellChanged(int row, int column)
{

}

void AssetManager::on_AddItem_released()
{
    if(!this->resourceFilePath.isEmpty()){
        QString path            = ui->PathInput->text();
        QString name            = ui->AddInput->text();
        AssetCategory category  = getSelectedAssetCategory();

        if(!name.isEmpty()){
            //Make sure the item exists
            if(QFile::exists(path)){
                Asset asset;
                asset.name      = name;
                asset.path      = path;
                asset.category  = category;
                addAsset(asset);
            }
        }
    }
    else{
        QMessageBox::warning(this, "No Resource File Loaded",
                             "No resource file has been loaded. You must load a resource file to import assets",
                             QMessageBox::Ok);
    }
}

void AssetManager::on_RemoveItem_released()
{
    QTreeWidgetItem *item = ui->List->currentItem();

    if(!itemIsCategory(item)){
        QString name = item->text(0);

        for(int i = 0; i < N_ASSET_CATEGORIES; i++){
            for(int j = 0; j < assets[i].size(); j++){
                Asset asset = assets[i][j];
                if(asset.name == name){
                    //asset found, remove it
                    assets[i].removeAt(j);
                    deleteAssetFile(asset);
                    saveAssets();
                }
            }
        }
    }
}

bool AssetManager::moveAssetFile(AssetManager::Asset asset)
{
    bool moveSuccessfull = false;

    //Get asset file name
    QStringList parts = asset.path.split('/');
    QString fileName = parts.last();

    //Construct the path for the new asset
    QString newPath = this->resourceFilePath;
    newPath += getCategoryAssetPath(asset.category);

    QString dirPath = newPath;
    newPath += fileName;

    //Create directory if necessary
    QDir dir;
    if(!dir.exists(dirPath)){
        dir.mkpath(dirPath);
    }
    QFile::copy(asset.path, newPath);

    if(QFile::exists(newPath)){
        moveSuccessfull = true;
    }

    return moveSuccessfull;
}

bool AssetManager::deleteAssetFile(AssetManager::Asset asset)
{
    bool deleteSuccessfull = false;

    //Construct path to asset file
    QString path = this->resourceFilePath;
    path += getCategoryAssetPath(asset.category);
    path += asset.name;

    //If file exists, remove it
    if(QFile::exists(path)){
        QFile::remove(path);
        deleteSuccessfull = true;
    }

    return deleteSuccessfull;
}

AssetManager::AssetCategory AssetManager::getSelectedAssetCategory()
{
    AssetCategory category = N_ASSET_CATEGORIES;    //Unknown category

    QString categoryText = ui->List->currentItem()->text(0);

    if(categoryText == "Music"){
        category = MUSIC;
    }
    else if(categoryText == "Sound Effects"){
        category = SOUND_EFFECT;
    }
    else if(categoryText == "Images"){
        category = IMAGE;
    }
    else if(categoryText == "Icons"){
        category = ICON;
    }
    else if(categoryText == "Units"){
        category = SPRITESHEET_UNIT;
    }
    else if(categoryText == "Effects"){
        category = SPRITESHEET_EFFECT;
    }
    else if(categoryText == "Terrain"){
        category = SPRITESHEET_TERRAIN;
    }
    else if(categoryText == "Projectiles"){
        category = SPRITESHEET_PROJECTILE;
    }
    else{
        qDebug() << "Bad category";
    }

    return category;
}

bool AssetManager::itemIsCategory(QTreeWidgetItem *item)
{
    bool isCategory = false;

    for(int i = 0; i < items.size(); i++){
        if(items[i] == item){
            isCategory = true;
            break;
        }
    }

    return isCategory;
}

QString AssetManager::getCategoryAssetPath(AssetManager::AssetCategory category)
{
    QString path;

    switch(category){
        case MUSIC:
            path = "/Assets/Sounds/Music/";
            break;
        case SOUND_EFFECT:
            path = "/Assets/Sounds/SoundEffects/";
            break;
        case IMAGE:
            path = "/Assets/Images/";
            break;
        case ICON:
            path = "/Assets/Icon/";
            break;
        case SPRITESHEET_UNIT:
            path = "/Assets/Spritesheets/Units/";
            break;
        case SPRITESHEET_TERRAIN:
            path = "/Assets/Spritesheets/Terrain/";
            break;
        case SPRITESHEET_EFFECT:
            path = "/Assets/Spritesheets/Effect/";
            break;
        case SPRITESHEET_PROJECTILE:
            path = "/Assets/Spritesheets/Projectile/";
            break;
        default:
            path = "";
            break;
    }

    return path;
}

void AssetManager::on_BrowseButton_released()
{
    QString name = QFileDialog::getOpenFileName(this,
                                                "Open Asset", "P:\\QtProjects\\Gingerspice\\LevelDesigner\\Resources",
                                                "All Files (*.*)");
    ui->PathInput->setText(name);
}

void AssetManager::refreshGUI()
{

    for(int i = 0; i < N_ASSET_CATEGORIES; i++){
        QTreeWidgetItem *header = items[i];
        qDeleteAll(header->takeChildren());

        for(Asset asset : assets[i]){
            QTreeWidgetItem *child = new QTreeWidgetItem();
            child->setText(0, asset.name);
            child->setIcon(0, QIcon("://file icon.jpg"));
            header->addChild(child);
        }
    }

    ui->List->expandAll();
}

void AssetManager::addAsset(AssetManager::Asset asset)
{
    if(asset.category < N_ASSET_CATEGORIES){
        assets[asset.category].append(asset);
        moveAssetFile(asset);
        saveAssets();
    }
}

void AssetManager::saveAssets()
{
    refreshGUI();
    emit itemChanged();
}
