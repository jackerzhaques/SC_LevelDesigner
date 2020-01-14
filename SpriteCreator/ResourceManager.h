#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <QWidget>
#include <QComboBox>
#include <QCheckBox>

#include "Game/Unit.h"
#include "Game/Globals.h"
#include "SpriteCreator/ResourceOpenDialog.h"
#include "ResourceManager/UnitManager.h"
#include "ResourceManager/AbilityManager.h"
#include "ResourceManager/AssetManager.h"

#include <QList>

namespace Ui {
class ResourceManager;
}

class ResourceManager : public QWidget
{
    Q_OBJECT

public:
    explicit ResourceManager(QWidget *parent = nullptr);
    ~ResourceManager();

    enum Pages{
        RESOURCES,
        UNIT_PAGE,
        //TERRAIN,
        //DESTRUCTIBLE,
        //ITEM,
        //PROJECTILE,
        ABILITIES_PAGE,
        ASSETS_PAGE,
        N_PAGES
    };

    QString toXML();

private slots:
    void loadResourceFile();
    void saveResourceFile();

private slots:
    void on_ResourceFileBrowseButton_released();
    
    void on_ResourceFileSaveButton_released();

private:
    Ui::ResourceManager *ui;
    UnitManager *unitManager        = nullptr;
    AbilityManager *abilityManager  = nullptr;
    AssetManager *assetManager      = nullptr;

    //Resource load/save functions/variables
    QString resourceFilePath = "";
};

#endif // RESOURCEMANAGER_H
