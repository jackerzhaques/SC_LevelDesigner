#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include <QWidget>
#include <QFileDialog>
#include <QTreeWidgetItem>
#include <QTreeWidget>
#include <QFile>
#include <QDir>
#include <QMessageBox>
#include <QIcon>

namespace Ui {
class AssetManager;
}

class AssetManager : public QWidget
{
    Q_OBJECT

public:
    explicit AssetManager(QWidget *parent = nullptr);
    ~AssetManager();

    void setResourceFilePath(QString path);

signals:
    void itemChanged();

private slots:
    void on_EditTable_cellChanged(int row, int column);

    void on_AddItem_released();

    void on_RemoveItem_released();

    void on_BrowseButton_released();

private:
    Ui::AssetManager *ui;
    QString resourceFilePath;

    enum AssetCategory{
        MUSIC,
        SOUND_EFFECT,
        IMAGE,
        ICON,
        SPRITESHEET_UNIT,
        SPRITESHEET_TERRAIN,
        SPRITESHEET_EFFECT,
        SPRITESHEET_PROJECTILE,
        N_ASSET_CATEGORIES
    };

    struct Asset{
        QString name = "";
        QString path = "";
        AssetCategory category = IMAGE;
    };

    void refreshGUI();
    void addAsset(Asset asset);
    void saveAssets();
    bool moveAssetFile(Asset asset);
    bool deleteAssetFile(Asset asset);
    AssetCategory getSelectedAssetCategory();
    bool itemIsCategory(QTreeWidgetItem *item);
    QString getCategoryAssetPath(AssetCategory category);

    QList<QList<Asset>> assets;

    QList<QTreeWidgetItem*> items;
};

#endif // ASSETMANAGER_H
