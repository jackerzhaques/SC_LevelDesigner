#ifndef UNITMANAGER_H
#define UNITMANAGER_H

#include <QWidget>
#include <QComboBox>
#include <QCheckBox>

#include "Game/Unit.h"
#include "Game/Globals.h"
#include "SpriteCreator/ResourceOpenDialog.h"

#include <QDomElement>

namespace Ui {
class UnitManager;
}

class UnitManager : public QWidget
{
    Q_OBJECT

public:
    explicit UnitManager(QWidget *parent = nullptr);
    ~UnitManager();

    enum UnitFields{
        GENERIC_INFO,   //NOT EDITABLE
        NAME,
        BASE_STATS,     //NOT EDITABLE
        INTELLECT,
        STRENGTH,
        AGILITY,
        CONSTITUTION,
        SPIRIT,
        MANA_TYPE,
        MANA_BASE,
        MANA_REGEN,
        HEALTH_BASE,
        HEALTH_REGEN,
        COMBAT, //NOT EDITABLE
        ATTACK_TYPE,
        RANGE,
        BASE_DAMAGE,
        CRITICAL_STRIKE_CHANCE,
        CRITICAL_STRIKE_MULTIPLIER,
        CRITICAL_STRIKE_BONUS,
        MISSILE_ART,
        MISSILE_ARC,
        SPLASH_RANGE,
        SPELLS_AND_ABILITIES,//NOT EDITABLE
        ABILITIES,
        PASSIVES,
        ART, //NOT EDITABLE
        SPRITESHEET,
        XML,
        ICON,
        PROJECTILE_LAUNCH_POSITION_X,
        PROJECTILE_LAUNCH_POSITION_Y,
        MOVEMENT,   //NOT EDITABLE
        MOVEMENT_TYPE,
        MOVEMENT_BASE,
        MOVEMENT_ACCELERATION,
        HAS_COLLISION,
        N_UNIT_FIELDS,
    };

    void initializeUnitTable();

    QDomElement unitToXML(Unit *unit, QDomDocument *doc);
    QDomElement getXML(QDomDocument *doc);

signals:
    void unitChanged();

private slots:
    void updateSpritesheetPath(const QString &path);
    void updateXMLPath(const QString &path);
    void updateIconPath(const QString &path);

    void saveManaType();
    void saveAttackType();
    void saveMovementType();
    void saveCollision();

private slots:
    void on_AddUnitButton_released();

    void on_UnitEditTable_cellDoubleClicked(int row, int column);

    void on_UnitEditTable_cellChanged(int row, int column);

    void on_UnitList_currentRowChanged(int currentRow);

    void on_RemoveUnitButton_released();

private:
    Ui::UnitManager *ui;
    bool initialized = false;

    //Object lists
    QList<Unit*> units;

    //Object list manipulation
    void addUnit(Unit *unit);
    void removeUnit(int index);
    bool unitExists(const QString &name);
    void setUnitProperty(Unit *unit, UnitFields field, const QString &propertyText);


    //GUI Update functions
    void refreshUnitList();
    void setEditTableUnit(Unit *unit);
    void setEditTableField(const UnitFields &field, const QString &val);
    void setEditTableField(const UnitFields &field, const int &val);

    //Custom table fields
    QComboBox *UnitManaTypeInput                = nullptr;
    QComboBox *UnitAttackTypeInput              = nullptr;
    QComboBox *UnitMovementTypeInput            = nullptr;
    ResourceOpenDialog *UnitSpritesheetDialog   = nullptr;
    ResourceOpenDialog *UnitXMLDialog           = nullptr;
    ResourceOpenDialog *UnitIconDialog          = nullptr;
    QCheckBox *UnitCollisionCheckbox            = nullptr;
};

#endif // UNITMANAGER_H
