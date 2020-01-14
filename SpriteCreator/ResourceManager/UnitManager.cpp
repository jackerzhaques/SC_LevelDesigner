#include "SpriteCreator/ResourceManager/UnitManager.h"
#include "ui_UnitManager.h"

#include <QDebug>
#include <QDomDocument>
#include <QFile>

UnitManager::UnitManager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UnitManager)
{
    ui->setupUi(this);

    this->initializeUnitTable();

    Unit *emptyUnit = new Unit();
    emptyUnit->setName("Skeleton");
    this->addUnit(emptyUnit);
    ui->UnitList->setCurrentRow(0);

    this->initialized = true;
}

UnitManager::~UnitManager()
{
    delete ui;
}


void UnitManager::initializeUnitTable()
{
    /*
     * Mana Type
     */
    this->UnitManaTypeInput = new QComboBox(ui->UnitEditTable);
    for(int i = 0; i < N_MANA_TYPES; i++){
        UnitManaTypeInput->addItem(manaTypeToString(static_cast<ManaType>(i)));
    }
    connect(UnitManaTypeInput, SIGNAL(currentIndexChanged(int)), this, SLOT(saveManaType()));
    ui->UnitEditTable->setCellWidget(MANA_TYPE, 0, UnitManaTypeInput);

    /*
     * Attack Type
     */
    this->UnitAttackTypeInput = new QComboBox(ui->UnitEditTable);
    for(int i = 0; i < N_ATTACK_TYPES; i++){
        UnitAttackTypeInput->addItem(attackTypeToString(static_cast<AttackType>(i)));
    }
    connect(UnitAttackTypeInput, SIGNAL(currentIndexChanged(int)), this, SLOT(saveAttackType()));
    ui->UnitEditTable->setCellWidget(ATTACK_TYPE, 0, UnitAttackTypeInput);

    /*
     * Movement Type
     */
    this->UnitMovementTypeInput = new QComboBox(ui->UnitEditTable);
    for(int i = 0; i < N_MOVEMENT_TYPES; i++){
        UnitMovementTypeInput->addItem(movementTypeToString(static_cast<MovementType>(i)));
    }
    connect(UnitMovementTypeInput, SIGNAL(currentIndexChanged(int)), this, SLOT(saveMovementType()));
    ui->UnitEditTable->setCellWidget(MOVEMENT_TYPE, 0, UnitMovementTypeInput);

    /*
     * Resource Opening
     */
    this->UnitXMLDialog         = new ResourceOpenDialog(this);
    this->UnitIconDialog        = new ResourceOpenDialog(this);
    this->UnitSpritesheetDialog = new ResourceOpenDialog(this);

    connect(UnitXMLDialog, SIGNAL(dialogClosed(QString)), this, SLOT(updateXMLPath(QString)));
    connect(UnitIconDialog, SIGNAL(dialogClosed(QString)), this, SLOT(updateIconPath(QString)));
    connect(UnitSpritesheetDialog, SIGNAL(dialogClosed(QString)), this, SLOT(updateSpritesheetPath(QString)));

    ui->UnitEditTable->item(XML, 0)->setText("");
    ui->UnitEditTable->item(ICON, 0)->setText("");
    ui->UnitEditTable->item(SPRITESHEET, 0)->setText("");

    /*
     * Collision check
     */
    this->UnitCollisionCheckbox = new QCheckBox(ui->UnitEditTable);
    UnitCollisionCheckbox->setChecked(true);
    connect(UnitCollisionCheckbox, SIGNAL(toggled(bool)), this, SLOT(saveCollision()));
    ui->UnitEditTable->item(HAS_COLLISION, 0)->setText("");
    ui->UnitEditTable->setCellWidget(HAS_COLLISION, 0, UnitCollisionCheckbox);

    /*
     * Set header cells background color
     */
    ui->UnitEditTable->item(GENERIC_INFO, 0)->setData(Qt::BackgroundRole, QColor::fromRgb(235,235,235));
    ui->UnitEditTable->item(BASE_STATS, 0)->setData(Qt::BackgroundRole, QColor::fromRgb(235,235,235));
    ui->UnitEditTable->item(COMBAT, 0)->setData(Qt::BackgroundRole, QColor::fromRgb(235,235,235));
    ui->UnitEditTable->item(SPELLS_AND_ABILITIES, 0)->setData(Qt::BackgroundRole, QColor::fromRgb(235,235,235));
    ui->UnitEditTable->item(ART, 0)->setData(Qt::BackgroundRole, QColor::fromRgb(235,235,235));
    ui->UnitEditTable->item(MOVEMENT, 0)->setData(Qt::BackgroundRole, QColor::fromRgb(235,235,235));
}

QDomElement UnitManager::unitToXML(Unit *unit, QDomDocument *doc)
{
    QDomElement xml;

    xml = doc->createElement("UnitType");
    xml.setAttribute("intellect", unit->getIntellect());
    xml.setAttribute("strength", unit->getStrength());
    xml.setAttribute("agility", unit->getAgility());
    xml.setAttribute("constitution", unit->getConstitution());
    xml.setAttribute("spirit", unit->getSpirit());
    xml.setAttribute("manaType", unit->getManaType());
    xml.setAttribute("manaBase", unit->getManaBase());
    xml.setAttribute("currentMana", unit->getCurrentMana());
    xml.setAttribute("manaRegen", unit->getManaRegen());
    xml.setAttribute("healthBase", unit->getHealthBase());
    xml.setAttribute("currentHealth", unit->getCurrentHealth());
    xml.setAttribute("healthRegen", unit->getHealthRegen());
    xml.setAttribute("attackType", unit->getAttackType());
    xml.setAttribute("range", unit->getRange());
    xml.setAttribute("baseDamage", unit->getBaseDamage());
    xml.setAttribute("critChance", unit->getCritChance());
    xml.setAttribute("critMultiplier", unit->getCritMultiplier());
    xml.setAttribute("critBonus", unit->getCritBonus());
    xml.setAttribute("missileArc", unit->getMissileArc());
    xml.setAttribute("splashRange", unit->getSplashRange());
    xml.setAttribute("spritePath", unit->getSpritePath());
    xml.setAttribute("spriteXMLPath", unit->getSpriteXMLPath());
    xml.setAttribute("iconPath", unit->getIconPath());
    xml.setAttribute("projectileOrigin", pointToString(unit->getProjectileOrigin()));
    xml.setAttribute("baseMoveSpeed", unit->getBaseMoveSpeed());
    xml.setAttribute("acceleration", unit->getAcceleration());
    xml.setAttribute("hasCollision", unit->getHasCollision());

    return xml;
}

QDomElement UnitManager::getXML(QDomDocument *doc)
{
    QDomElement root = doc->createElement("UnitTypes");

    for(auto unit : units){
        root.appendChild(unitToXML(unit, doc));
    }

    return root;
}

void UnitManager::updateSpritesheetPath(const QString &path)
{
    ui->UnitEditTable->item(SPRITESHEET, 0)->setText(path);
}

void UnitManager::updateXMLPath(const QString &path)
{
    ui->UnitEditTable->item(XML, 0)->setText(path);
}

void UnitManager::updateIconPath(const QString &path)
{
    ui->UnitEditTable->item(ICON, 0)->setText(path);
}

void UnitManager::saveManaType()
{
    Unit *unit = units.at(ui->UnitList->currentRow());
    QString manaTypeString = QString::number(UnitManaTypeInput->currentIndex());
    this->setUnitProperty(unit, MANA_TYPE, manaTypeString);
}

void UnitManager::saveAttackType()
{
    Unit *unit = units.at(ui->UnitList->currentRow());
    QString attackTypeString = QString::number(UnitAttackTypeInput->currentIndex());
    this->setUnitProperty(unit, ATTACK_TYPE, attackTypeString);
}

void UnitManager::saveMovementType()
{
    Unit *unit = units.at(ui->UnitList->currentRow());
    QString movementTypeString = QString::number(UnitMovementTypeInput->currentIndex());
    this->setUnitProperty(unit, MOVEMENT_TYPE, movementTypeString);
}

void UnitManager::saveCollision()
{
    Unit *unit = units.at(ui->UnitList->currentRow());
    QString colString = "";
    if(UnitCollisionCheckbox->isChecked()){
        colString = "1";
    }
    else{
        colString = "0";
    }
    this->setUnitProperty(unit, HAS_COLLISION, colString);
}

void UnitManager::addUnit(Unit *unit)
{
    units.append(unit);
    this->refreshUnitList();
}

void UnitManager::removeUnit(int index)
{
    this->units.removeAt(index);
    this->refreshUnitList();
}

bool UnitManager::unitExists(const QString &name)
{
    bool exists = false;

    for(Unit *unit : units){
        if(unit->getName() == name){
            exists = true;
            break;
        }
    }

    return exists;
}

void UnitManager::setUnitProperty(Unit *unit, UnitManager::UnitFields field, const QString &propertyText)
{
    //Most properties are a double, so the value will always try to be casted as a double
    double val = propertyText.toDouble();
    int iVal = static_cast<int>(val);

    switch(field){
        case NAME:
            unit->setName(propertyText);
            break;
        case INTELLECT:
            unit->setIntellect(iVal);
            break;
        case STRENGTH:
            unit->setStrength(iVal);
            break;
        case AGILITY:
            unit->setAgility(iVal);
            break;
        case CONSTITUTION:
            unit->setConstitution(iVal);
            break;
        case SPIRIT:
            unit->setSpirit(iVal);
            break;
        case MANA_TYPE:
            {
                auto t = static_cast<ManaType>(iVal);
                unit->setManaType(t);
            }
            break;
        case MANA_BASE:
            unit->setManaBase(val);
            break;
        case MANA_REGEN:
            unit->setManaRegen(val);
            break;
        case HEALTH_BASE:
            unit->setHealthBase(val);
            break;
        case HEALTH_REGEN:
            unit->setHealthRegen(val);
            break;
        case ATTACK_TYPE:
        {
            auto t = static_cast<AttackType>(iVal);
            unit->setAttackType(t);
        }
            break;
        case RANGE:
            unit->setRange(val);
            break;
        case BASE_DAMAGE:
            unit->setBaseDamage(val);
            break;
        case CRITICAL_STRIKE_CHANCE:
            unit->setCritChance(val);
            break;
        case CRITICAL_STRIKE_MULTIPLIER:
            unit->setCritMultiplier(val);
            break;
        case CRITICAL_STRIKE_BONUS:
            unit->setCritBonus(val);
            break;
        case MISSILE_ART:
            //NOT IMPLEMENTED YET
            break;
        case MISSILE_ARC:
            unit->setMissileArc(val);
            break;
        case SPLASH_RANGE:
            unit->setSplashRange(val);
            break;
        case ABILITIES:
            //NOT IMPLEMENTED YET
            break;
        case PASSIVES:
            //NOT IMPLEMENTED YET
            break;
        case SPRITESHEET:
            unit->setSpritePath(propertyText);
            break;
        case XML:
            unit->setSpriteXMLPath(propertyText);
            break;
        case ICON:
            unit->setIconPath(propertyText);
            break;
        case PROJECTILE_LAUNCH_POSITION_X:
        {
            QPointF origin = unit->getProjectileOrigin();
            origin.setX(val);
            unit->setProjectileOrigin(origin);
        }
            break;
        case PROJECTILE_LAUNCH_POSITION_Y:
        {
            QPointF origin = unit->getProjectileOrigin();
            origin.setY(val);
            unit->setProjectileOrigin(origin);
        }
            break;
        case MOVEMENT_TYPE:
        {
            auto t = static_cast<MovementType>(iVal);
            unit->setMovementType(t);
        }
            break;
        case MOVEMENT_BASE:
            unit->setBaseMoveSpeed(val);
            break;
        case MOVEMENT_ACCELERATION:
            unit->setAcceleration(val);
            break;
        case HAS_COLLISION:
            if(propertyText == "1"){
                unit->setHasCollision(true);
            }
            else{
                unit->setHasCollision(false);
            }
            break;
        default:
            //Do nothing
            break;
    }

    emit unitChanged();
}

void UnitManager::refreshUnitList()
{
    int rowState = ui->UnitList->currentRow();
    ui->UnitList->clear();

    for(Unit *unit : units){
        ui->UnitList->addItem(unit->getName());
    }

    if(rowState >= units.size()){
        ui->UnitList->setCurrentRow(0);
    }
    else{
        ui->UnitList->setCurrentRow(rowState);
    }
}

void UnitManager::setEditTableUnit(Unit *unit)
{
    setEditTableField(NAME, unit->getName());
    setEditTableField(INTELLECT, QString::number(unit->getIntellect()));
    setEditTableField(STRENGTH, QString::number(unit->getStrength()));
    setEditTableField(AGILITY, QString::number(unit->getAgility()));
    setEditTableField(CONSTITUTION, QString::number(unit->getConstitution()));
    setEditTableField(SPIRIT, QString::number(unit->getSpirit()));
    setEditTableField(MANA_TYPE, unit->getManaType());
    setEditTableField(MANA_BASE, QString::number(unit->getManaBase()));
    setEditTableField(MANA_REGEN, QString::number(unit->getManaRegen()));
    setEditTableField(HEALTH_BASE, QString::number(unit->getHealthBase()));
    setEditTableField(HEALTH_REGEN, QString::number(unit->getHealthRegen()));
    setEditTableField(ATTACK_TYPE, unit->getAttackType());
    setEditTableField(BASE_DAMAGE, QString::number(unit->getBaseDamage()));
    setEditTableField(CRITICAL_STRIKE_CHANCE, QString::number(unit->getCritChance()));
    setEditTableField(CRITICAL_STRIKE_MULTIPLIER, QString::number(unit->getCritMultiplier()));
    setEditTableField(CRITICAL_STRIKE_BONUS, QString::number(unit->getCritBonus()));
    //setEditTableField(MISSILE_ART, unit->getName());  //Not implemented yet
    setEditTableField(MISSILE_ARC, QString::number(unit->getMissileArc()));
    setEditTableField(SPLASH_RANGE, QString::number(unit->getSplashRange()));
    //Abilities and passives not implemented yet
    //setEditTableField(ABILITIES, unit->getName());
    //setEditTableField(PASSIVES, unit->getName());
    setEditTableField(SPRITESHEET, unit->getSpritePath());
    setEditTableField(XML, unit->getSpriteXMLPath());
    setEditTableField(PROJECTILE_LAUNCH_POSITION_X, QString::number(unit->getProjectileOrigin().x()));
    setEditTableField(PROJECTILE_LAUNCH_POSITION_Y, QString::number(unit->getProjectileOrigin().y()));
    setEditTableField(MOVEMENT_TYPE, unit->getMoveType());
    setEditTableField(MOVEMENT_BASE, QString::number(unit->getBaseMoveSpeed()));
    setEditTableField(MOVEMENT_ACCELERATION, QString::number(unit->getAcceleration()));
    setEditTableField(HAS_COLLISION, unit->getHasCollision());
}

//Used for string type fields
void UnitManager::setEditTableField(const UnitManager::UnitFields &field, const QString &val)
{
    ui->UnitEditTable->item(field, 0)->setText(val);
}

//Used for widget type fields
void UnitManager::setEditTableField(const UnitManager::UnitFields &field, const int &val)
{
    switch(field){
        case MANA_TYPE:
            UnitManaTypeInput->setCurrentIndex(val);
            break;
        case ATTACK_TYPE:
            UnitAttackTypeInput->setCurrentIndex(val);
            break;
        case MOVEMENT_TYPE:
            UnitMovementTypeInput->setCurrentIndex(val);
            break;
        case HAS_COLLISION:
        {
            bool state = static_cast<bool>(val);
            UnitCollisionCheckbox->setChecked(state);
        }
            break;
        default:
            //Do nothing
            break;
    }
}

void UnitManager::on_AddUnitButton_released()
{
    QString name = ui->AddUnitInput->text();
    if(!name.isEmpty() && !unitExists(name)){
        Unit *unit = new Unit();
        unit->setName(ui->AddUnitInput->text());
        this->addUnit(unit);
    }
}

void UnitManager::on_UnitEditTable_cellDoubleClicked(int row, int)
{
    switch(row){
        case XML:
            this->UnitXMLDialog->show();
            break;
        case SPRITESHEET:
            this->UnitSpritesheetDialog->show();
            break;
        case ICON:
            this->UnitIconDialog->show();
            break;
        default:
            //Do nothing
            break;
    }
}

void UnitManager::on_UnitEditTable_cellChanged(int row, int)
{
    if(this->initialized && row >= 0){
        //Store this in the currently selected unit
        QString property = ui->UnitEditTable->item(row, 0)->text();
        Unit *unit = this->units.at(ui->UnitList->currentRow());
        setUnitProperty(unit, static_cast<UnitFields>(row), property);
    }
}

void UnitManager::on_UnitList_currentRowChanged(int currentRow)
{
    if(currentRow >= 0 && currentRow < units.size()){
        this->setEditTableUnit(units[currentRow]);
    }
}

void UnitManager::on_RemoveUnitButton_released()
{
    //Never remove the last unit
    if(units.size() > 1){
        this->removeUnit(ui->UnitList->currentRow());
    }
}
