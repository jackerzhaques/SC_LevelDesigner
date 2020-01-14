#include "AbilityManager.h"
#include "ui_AbilityManager.h"

#include <QDebug>

AbilityManager::AbilityManager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AbilityManager)
{
    ui->setupUi(this);

    this->initializeTable();

    ui->EditTable->installEventFilter(this);

    Ability *emptyAbility = new Ability();
    emptyAbility->setNormalText("Fireball");
    addAbility(emptyAbility);
    ui->List->setCurrentRow(0);

    initialized = true;
}

AbilityManager::~AbilityManager()
{
    delete ui;
}

void AbilityManager::initializeTable()
{

    /*
     * Disabled Collision
     */
    this->CollisionCheck = new QCheckBox(ui->EditTable);
    CollisionCheck->setChecked(false);
    connect(CollisionCheck, SIGNAL(toggled(bool)), this, SLOT(saveCollision()));
    ui->EditTable->item(DISABLES_COLLISION, 0)->setText("");
    ui->EditTable->setCellWidget(DISABLES_COLLISION, 0, CollisionCheck);

    /*
     * Is Chanelled
     */
    this->IsChannelledCheck = new QCheckBox(ui->EditTable);
    IsChannelledCheck->setChecked(false);
    connect(IsChannelledCheck, SIGNAL(toggled(bool)), this, SLOT(saveChannelled()));
    ui->EditTable->item(IS_CHANNELLED, 0)->setText("");
    ui->EditTable->setCellWidget(IS_CHANNELLED, 0, IsChannelledCheck);

    /*
     * Target Type
     */
    this->TargetTypeInput = new QComboBox(ui->EditTable);
    for(int i = 0; i < N_TARGET_TYPES; i++){
        TargetTypeInput->addItem(targetTypeToString(static_cast<TargetType>(i)));
    }
    connect(TargetTypeInput, SIGNAL(currentIndexChanged(int)), this, SLOT(saveTargetType()));
    ui->EditTable->setCellWidget(TARGET_TYPE, 0, TargetTypeInput);

    /*
     * Resource Opening
     */
    this->CastSoundDialog       = new ResourceOpenDialog(this);
    this->CastEffectDialog      = new ResourceOpenDialog(this);
    this->ChannelSoundDialog    = new ResourceOpenDialog(this);
    this->ChannelEffectDialog   = new ResourceOpenDialog(this);

    connect(CastSoundDialog, SIGNAL(dialogClosed(QString)), this, SLOT(saveCastSound(QString)));
    connect(CastEffectDialog, SIGNAL(dialogClosed(QString)), this, SLOT(saveCastEffect(QString)));
    connect(ChannelSoundDialog, SIGNAL(dialogClosed(QString)), this, SLOT(saveChannelSound(QString)));
    connect(ChannelEffectDialog, SIGNAL(dialogClosed(QString)), this, SLOT(saveChannelEffect(QString)));

    ui->EditTable->item(CAST_SOUND, 0)->setText("");
    ui->EditTable->item(CAST_EFFECT, 0)->setText("");
    ui->EditTable->item(CHANNEL_SOUND, 0)->setText("");
    ui->EditTable->item(CHANNEL_EFFECT, 0)->setText("");

    /*
     * Expression Editors
     */
    const char *slot = SLOT(processExpressions(int, QString));
    TextLearnDialog         = new ExpressionDialog(TEXT_LEARN,              slot, "Learn Text", this);
    TextLearnExtDialog      = new ExpressionDialog(TEXT_LEARN_EXTENDED,     slot, "Learn Text Extension", this);
    TextNormalDialog        = new ExpressionDialog(TEXT_NORMAL,             slot, "Normal Text", this);
    TextNormalExtDialog     = new ExpressionDialog(TEXT_NORMAL_EXTENDED,    slot, "Normal Text Extension", this);
    TextDisableExtDialog    = new ExpressionDialog(TEXT_DISABLED_EXTENDED,  slot, "Disabled Text", this);
    CastTimeDialog          = new ExpressionDialog(CAST_TIME,               slot, "Cast Time", this);
    ChannelDurationDialog   = new ExpressionDialog(CHANNEL_DURATION,        slot, "Channel Duration", this);
    CooldownDialog          = new ExpressionDialog(COOLDOWN,                slot, "Cooldown", this);
    RangeDialog             = new ExpressionDialog(RANGE,                   slot, "Range", this);
    AbilityDamageDialog     = new ExpressionDialog(ABILITY_DAMAGE,          slot, "Ability Damage", this);
    ManaCostDialog          = new ExpressionDialog(MANA_COST,               slot, "Mana Cost", this);
    ManaDrainDialog         = new ExpressionDialog(MANA_DRAIN,              slot, "Mana Drain", this);
    IntellectDialog         = new ExpressionDialog(INTELLECT,               slot, "Intellect", this);
    StrengthDialog          = new ExpressionDialog(STRENGTH,                slot, "Strength", this);
    AgilityDialog           = new ExpressionDialog(AGILITY,                 slot, "Agility", this);
    ConstitutionDialog      = new ExpressionDialog(CONSTITUTION,            slot, "Constitution", this);
    SpiritDialog            = new ExpressionDialog(SPIRIT,                  slot, "Spirit", this);
    HealthDialog            = new ExpressionDialog(HEALTH_FIELD,                  slot, "Health", this);
    HealthRegenDialog       = new ExpressionDialog(HEALTH_REGEN,            slot, "Health Regen", this);
    ManaDialog              = new ExpressionDialog(MANA_FIELD,                    slot, "Mana", this);
    ManaRegenDialog         = new ExpressionDialog(MANA_REGEN,              slot, "Mana Regen", this);
    MoveSpeedDialog         = new ExpressionDialog(MOVEMENT_SPEED,          slot, "Move Speed", this);
    AccelerationDialog      = new ExpressionDialog(ACCELERATION,            slot, "Acceleration", this);
    DamageDialog            = new ExpressionDialog(DAMAGE,                  slot, "Damage", this);
    CritChanceDialog        = new ExpressionDialog(CRIT_CHANCE,             slot, "Crit Chance", this);
    CritMultiplierDialog    = new ExpressionDialog(CRIT_MULT,               slot, "Crit Multiplier", this);
    CritBonusDialog         = new ExpressionDialog(CRIT_BONUS,              slot, "Crit Bonus", this);

    /*
     * Set header cells background color
     */
    ui->EditTable->item(GENERIC_INFORMATION, 0)->setData(Qt::BackgroundRole, QColor::fromRgb(235,235,235));
    ui->EditTable->item(CAST_INFORMATION, 0)->setData(Qt::BackgroundRole, QColor::fromRgb(235,235,235));
    ui->EditTable->item(ART, 0)->setData(Qt::BackgroundRole, QColor::fromRgb(235,235,235));
    ui->EditTable->item(UNIT_ATTRIBUTE_MODIFIERS, 0)->setData(Qt::BackgroundRole, QColor::fromRgb(235,235,235));
    ui->EditTable->item(ATTACK_MODIFIERS, 0)->setData(Qt::BackgroundRole, QColor::fromRgb(235,235,235));
}

QDomElement AbilityManager::abilityToXML(Ability *ability, QDomDocument *doc)
{
    QDomElement xml;

    xml = doc->createElement("UnitType");

    xml.setAttribute("learnText",           ability->getLearnText());
    xml.setAttribute("learnTextExt",        ability->getLearnTextExtended());
    xml.setAttribute("normalText",          ability->getNormalText());
    xml.setAttribute("normalTextExt",       ability->getNormalTextExtended());
    xml.setAttribute("disabledTextExt",     ability->getDisabledTextExtended());
    xml.setAttribute("castTime",            expToString(ability->getCastTime()));
    xml.setAttribute("isChanneled",         ability->getIsChanneled());
    xml.setAttribute("channelDuration",     expToString(ability->getChannelDuration()));
    xml.setAttribute("cooldown",            expToString(ability->getCooldown()));
    xml.setAttribute("range",               expToString(ability->getRange()));
    xml.setAttribute("abilityDamage",       expToString(ability->getAbilityDamage()));
    xml.setAttribute("targetType",          ability->getTargetType());
    xml.setAttribute("manaCost",            expToString(ability->getManaCost()));
    xml.setAttribute("manaDrain",           expToString(ability->getManaDrain()));
    xml.setAttribute("maxLevels",           ability->getMaxLevels());
    xml.setAttribute("levelGap",            ability->getLevelGap());
    // TODO: Implement sounds and art
    //xml.setAttribute("castSound",           ability->getCastSound());
    //xml.setAttribute("castEffect",          ability->getCastEffect());
    //xml.setAttribute("channelSound",        ability->getChannelSound());
    //xml.setAttribute("channelEffect",       ability->getChannelEffect());
    xml.setAttribute("intellect",           expToString(ability->getIntellect()));
    xml.setAttribute("strength",            expToString(ability->getStrength()));
    xml.setAttribute("agility",             expToString(ability->getAgility()));
    xml.setAttribute("constitution",        expToString(ability->getConstitution()));
    xml.setAttribute("spirit",              expToString(ability->getSpirit()));
    xml.setAttribute("health",              expToString(ability->getHealth()));
    xml.setAttribute("healthRegen",         expToString(ability->getHealthRegen()));
    xml.setAttribute("mana",                expToString(ability->getMana()));
    xml.setAttribute("manaRegen",           expToString(ability->getManaRegen()));
    xml.setAttribute("movementSpeed",       expToString(ability->getMovementSpeed()));
    xml.setAttribute("acceleration",        expToString(ability->getAcceleration()));
    xml.setAttribute("disablesCollision",   ability->getDisablesCollision());
    xml.setAttribute("damage",              expToString(ability->getDamage()));
    xml.setAttribute("critChance",          expToString(ability->getCritChance()));
    xml.setAttribute("critMultiplier",      expToString(ability->getCritMultiplier()));
    xml.setAttribute("critBonus",           expToString(ability->getCritBonus()));

    return xml;
}

QDomElement AbilityManager::getXML(QDomDocument *doc)
{
    QDomElement root = doc->createElement("Abilities");

    for(auto ability : abilities){
        root.appendChild(abilityToXML(ability, doc));
    }

    return root;
}

void AbilityManager::saveCastSound(QString str)
{
    ui->EditTable->item(CAST_SOUND, 0)->setText(str);

    //TODO. IMPLEMENT SAVING
}

void AbilityManager::saveCastEffect(QString str)
{
    ui->EditTable->item(CAST_EFFECT, 0)->setText(str);

    //TODO. IMPLEMENT SAVING
}

void AbilityManager::saveChannelSound(QString str)
{
    ui->EditTable->item(CHANNEL_SOUND, 0)->setText(str);

    //TODO. IMPLEMENT SAVING
}

void AbilityManager::saveChannelEffect(QString str)
{
    ui->EditTable->item(CHANNEL_EFFECT, 0)->setText(str);

    //TODO. IMPLEMENT SAVING
}

void AbilityManager::saveCollision()
{
    auto ability = abilities.at(ui->List->currentRow());
    setAbilityProperty(ability, DISABLES_COLLISION, CollisionCheck->isChecked());
}

void AbilityManager::saveChannelled()
{
    auto ability = abilities.at(ui->List->currentRow());
    setAbilityProperty(ability, IS_CHANNELLED, IsChannelledCheck->isChecked());
}

void AbilityManager::saveTargetType()
{
    auto ability = abilities.at(ui->List->currentRow());
    setAbilityProperty(ability, TARGET_TYPE, TargetTypeInput->currentIndex());
}

void AbilityManager::processExpressions(int ID, QString str)
{
    if(str != IGNORE_CHANGES_CODE){
        auto fieldID = static_cast<Fields>(ID);
        setField(fieldID, str);

        //For TEXT_ fields, just save the string
        if(ID == TEXT_LEARN ||
            ID == TEXT_LEARN_EXTENDED ||
            ID == TEXT_NORMAL ||
            ID == TEXT_NORMAL_EXTENDED ||
            ID == TEXT_DISABLED_EXTENDED)
        {
            setAbilityProperty(currentAbility(), fieldID, str);

            //Special condition for TEXT_NORMAL, update ability name in GUI
            if(ID == TEXT_NORMAL){
                refreshAbilityList();
            }
        }
        //For all other fields, save as an expression
        else{
            setAbilityProperty(currentAbility(), fieldID, Expression::stringToExpression(str));
        }
    }
}

void AbilityManager::on_EditTable_cellDoubleClicked(int row, int)
{
    showDialog(row);
}

void AbilityManager::addAbility(Ability *ability)
{
    abilities.append(ability);
    this->refreshAbilityList();
}

void AbilityManager::removeAbility(int index)
{
    if(abilities.size() > 1){
        abilities.removeAt(index);
        refreshAbilityList();
    }
}

bool AbilityManager::abilityExists(QString name)
{
    for(auto ability : abilities){
        if(ability->getNormalText() == name){
            return true;
        }
    }
    return false;
}

void AbilityManager::setAbilityProperty(Ability *ability, AbilityManager::Fields field, QString str)
{
    switch(field){
        case TEXT_LEARN:
            ability->setLearnText(str);
            break;
        case TEXT_LEARN_EXTENDED:
            ability->setLearnTextExtended(str);
            break;
        case TEXT_NORMAL:
            ability->setNormalText(str);
            break;
        case TEXT_NORMAL_EXTENDED:
            ability->setNormalTextExtended(str);
            break;
        case TEXT_DISABLED_EXTENDED:
            ability->setDisabledTextExtended(str);
            break;
        case CAST_SOUND:
            //TODO: Implement this
            break;
        case CAST_EFFECT:
            //TODO: Implement this
            break;
        case CHANNEL_SOUND:
            //TODO: Implement this
            break;
        case CHANNEL_EFFECT:
            //TODO Implement this
            break;
        default:
            //Do nothing
            break;
    }

    emit itemChanged();
}

void AbilityManager::setAbilityProperty(Ability *ability, AbilityManager::Fields field, int val)
{
    switch(field){
        case IS_CHANNELLED:
        {
            bool state = static_cast<bool>(val);
            ability->setIsChanneled(state);
            break;
        }
        case TARGET_TYPE:
        {
            auto type = static_cast<TargetType>(val);
            ability->setTargetType(type);
            break;
        }
        case MAXIMUM_LEVELS:
            ability->setMaxLevels(val);
            break;
        case LEVEL_GAP:
            ability->setLevelGap(val);
            break;
        case DISABLES_COLLISION:
        {
            bool state = static_cast<bool>(val);
            ability->setDisablesCollision(state);
            break;
        }
        default:
            //Do nothing
            break;
    }

    emit itemChanged();
}

void AbilityManager::setAbilityProperty(Ability *ability, AbilityManager::Fields field, Expression *exp)
{
    switch(field){
        case CAST_TIME:
            ability->setCastTime(exp);
            break;
        case CHANNEL_DURATION:
            ability->setChannelDuration(exp);
            break;
        case COOLDOWN:
            ability->setCooldown(exp);
            break;
        case RANGE:
            ability->setRange(exp);
            break;
        case ABILITY_DAMAGE:
            ability->setAbilityDamage(exp);
            break;
        case MANA_COST:
            ability->setManaCost(exp);
            break;
        case MANA_DRAIN:
            ability->setManaDrain(exp);
            break;
        case INTELLECT:
            ability->setIntellect(exp);
            break;
        case STRENGTH:
            ability->setStrength(exp);
            break;
        case AGILITY:
            ability->setAgility(exp);
            break;
        case CONSTITUTION:
            ability->setConstitution(exp);
            break;
        case SPIRIT:
            ability->setSpirit(exp);
            break;
        case HEALTH_FIELD:
            ability->setHealth(exp);
            break;
        case HEALTH_REGEN:
            ability->setHealthRegen(exp);
            break;
        case MANA_FIELD:
            ability->setMana(exp);
            break;
        case MANA_REGEN:
            ability->setManaRegen(exp);
            break;
        case MOVEMENT_SPEED:
            ability->setMovementSpeed(exp);
            break;
        case ACCELERATION:
            ability->setAcceleration(exp);
            break;
        case DAMAGE:
            ability->setDamage(exp);
            break;
        case CRIT_CHANCE:
            ability->setCritChance(exp);
            break;
        case CRIT_MULT:
            ability->setCritMultiplier(exp);
            break;
        case CRIT_BONUS:
            ability->setCritBonus(exp);
            break;
        default:
            //Do nothing
            break;
    }

    emit itemChanged();
}

Ability *AbilityManager::currentAbility()
{
    Ability *ability = nullptr;

    int row = ui->List->currentRow();
    if(row >= 0 && row < abilities.size()){
        ability = abilities[row];
    }

    return ability;
}

void AbilityManager::refreshAbilityList()
{
    int rowState = ui->List->currentRow();
    ui->List->clear();

    for(auto ability : abilities){
        ui->List->addItem(ability->getNormalText());
    }

    while(rowState >= abilities.size()){
        rowState--;
    }

    ui->List->setCurrentRow(rowState);
}

void AbilityManager::setEditTableAbility(Ability *ability)
{
    setField(TEXT_LEARN, ability->getLearnText());
    setField(TEXT_LEARN_EXTENDED, ability->getLearnTextExtended());
    setField(TEXT_NORMAL, ability->getNormalText());
    setField(TEXT_NORMAL_EXTENDED, ability->getNormalTextExtended());
    setField(TEXT_DISABLED_EXTENDED, ability->getDisabledTextExtended());
    setField(CAST_TIME, ability->getCastTime());
    setField(IS_CHANNELLED, ability->getIsChanneled());
    setField(CHANNEL_DURATION, ability->getChannelDuration());
    setField(COOLDOWN, ability->getCooldown());
    setField(RANGE, ability->getRange());
    setField(ABILITY_DAMAGE, ability->getAbilityDamage());
    setField(TARGET_TYPE, ability->getTargetType());
    setField(MANA_COST, ability->getManaCost());
    setField(MANA_DRAIN, ability->getManaDrain());
    setField(MAXIMUM_LEVELS, ability->getMaxLevels());
    setField(LEVEL_GAP, ability->getLevelGap());
    //TODO: Implement these when sound and art is implemented
    //setField(CAST_SOUND, ability->getCastSound());
    //setField(CAST_EFFECT, ability->getCastEffect());
    //setField(CHANNEL_SOUND, ability->getChannelSound());
    //setField(CHANNEL_EFFECT, ability->getChannelEffect());
    setField(INTELLECT, ability->getIntellect());
    setField(STRENGTH, ability->getStrength());
    setField(AGILITY, ability->getAgility());
    setField(CONSTITUTION, ability->getConstitution());
    setField(SPIRIT, ability->getSpirit());
    setField(HEALTH_FIELD, ability->getHealth());
    setField(HEALTH_REGEN, ability->getHealthRegen());
    setField(MANA_FIELD, ability->getMana());
    setField(MANA_REGEN, ability->getManaRegen());
    setField(MOVEMENT_SPEED, ability->getMovementSpeed());
    setField(ACCELERATION, ability->getAcceleration());
    setField(DISABLES_COLLISION, ability->getDisablesCollision());
    setField(DAMAGE, ability->getDamage());
    setField(CRIT_CHANCE, ability->getCritChance());
    setField(CRIT_MULT, ability->getCritMultiplier());
    setField(CRIT_BONUS, ability->getCritBonus());

    //Update the TEXT fields manually because they are not automatically handled
    TextLearnDialog->setText(ability->getLearnText());
    TextLearnExtDialog->setText(ability->getLearnTextExtended());
    TextNormalDialog->setText(ability->getNormalText());
    TextNormalExtDialog->setText(ability->getNormalTextExtended());
    TextDisableExtDialog->setText(ability->getDisabledTextExtended());
}

void AbilityManager::setField(AbilityManager::Fields field, QString val)
{
    ui->EditTable->item(field, 0)->setText(val);
}

void AbilityManager::setField(AbilityManager::Fields field, int val)
{
    switch(field){
        //Fields with special widgets
        case IS_CHANNELLED:
        {
            auto state = static_cast<bool>(val);
            IsChannelledCheck->setChecked(state);
            break;
        }
        case TARGET_TYPE:
        {
            TargetTypeInput->setCurrentIndex(val);
            break;
        }
        case DISABLES_COLLISION:
        {
            auto state = static_cast<bool>(val);
            CollisionCheck->setChecked(state);
            break;
        }
        //Fields that actually are integers
        case MAXIMUM_LEVELS:
            setField(field, QString::number(val));
            break;
        case LEVEL_GAP:
            setField(field, QString::number(val));
            break;
        default:
            //Do nothing
            break;
    }
}

void AbilityManager::setField(AbilityManager::Fields field, Expression *exp)
{
    QString str = "";
    if(exp){
        str = exp->toString();
    }
    setField(field, str);
    updateExpressionDialog(field, str);
}

void AbilityManager::updateExpressionDialog(AbilityManager::Fields field, QString str)
{
    switch(field){
        case TEXT_LEARN:
            TextLearnDialog->setText(str);
            break;
        case TEXT_LEARN_EXTENDED:
            TextLearnExtDialog->setText(str);
            break;
        case TEXT_NORMAL:
            TextNormalDialog->setText(str);
            break;
        case TEXT_NORMAL_EXTENDED:
            TextNormalExtDialog->setText(str);
            break;
        case TEXT_DISABLED_EXTENDED:
            TextDisableExtDialog->setText(str);
            break;
        case CAST_TIME:
            CastTimeDialog->setText(str);
            break;
        case CHANNEL_DURATION:
            ChannelDurationDialog->setText(str);
            break;
        case COOLDOWN:
            CooldownDialog->setText(str);
            break;
        case RANGE:
            RangeDialog->setText(str);
            break;
        case ABILITY_DAMAGE:
            AbilityDamageDialog->setText(str);
            break;
        case MANA_COST:
            ManaCostDialog->setText(str);
            break;
        case MANA_DRAIN:
            ManaDrainDialog->setText(str);
            break;
        case INTELLECT:
            IntellectDialog->setText(str);
            break;
        case STRENGTH:
            StrengthDialog->setText(str);
            break;
        case AGILITY:
            AgilityDialog->setText(str);
            break;
        case CONSTITUTION:
            ConstitutionDialog->setText(str);
            break;
        case SPIRIT:
            SpiritDialog->setText(str);
            break;
        case HEALTH_FIELD:
            HealthDialog->setText(str);
            break;
        case HEALTH_REGEN:
            HealthRegenDialog->setText(str);
            break;
        case MANA_FIELD:
            ManaDialog->setText(str);
            break;
        case MANA_REGEN:
            ManaRegenDialog->setText(str);
            break;
        case MOVEMENT_SPEED:
            MoveSpeedDialog->setText(str);
            break;
        case ACCELERATION:
            AccelerationDialog->setText(str);
            break;
        case DAMAGE:
            DamageDialog->setText(str);
            break;
        case CRIT_CHANCE:
            CritChanceDialog->setText(str);
            break;
        case CRIT_MULT:
            CritMultiplierDialog->setText(str);
            break;
        case CRIT_BONUS:
            CritBonusDialog->setText(str);
            break;
        default:
            //Do nothing
            break;
    }
}

void AbilityManager::showDialog(int row)
{
    switch(row){
        case TEXT_LEARN:
            TextLearnDialog->show();
            break;
        case TEXT_LEARN_EXTENDED:
            TextLearnExtDialog->show();
            break;
        case TEXT_NORMAL:
            TextNormalDialog->show();
            break;
        case TEXT_NORMAL_EXTENDED:
            TextNormalExtDialog->show();
            break;
        case TEXT_DISABLED_EXTENDED:
            TextDisableExtDialog->show();
            break;
        case CAST_TIME:
            CastTimeDialog->show();
            break;
        case CHANNEL_DURATION:
            ChannelDurationDialog->show();
            break;
        case COOLDOWN:
            CooldownDialog->show();
            break;
        case RANGE:
            RangeDialog->show();
            break;
        case ABILITY_DAMAGE:
            AbilityDamageDialog->show();
            break;
        case MANA_COST:
            ManaCostDialog->show();
            break;
        case MANA_DRAIN:
            ManaDrainDialog->show();
            break;
        case INTELLECT:
            IntellectDialog->show();
            break;
        case STRENGTH:
            StrengthDialog->show();
            break;
        case AGILITY:
            AgilityDialog->show();
            break;
        case CONSTITUTION:
            ConstitutionDialog->show();
            break;
        case SPIRIT:
            SpiritDialog->show();
            break;
        case HEALTH_FIELD:
            HealthDialog->show();
            break;
        case HEALTH_REGEN:
            HealthRegenDialog->show();
            break;
        case MANA_FIELD:
            ManaDialog->show();
            break;
        case MANA_REGEN:
            ManaRegenDialog->show();
            break;
        case MOVEMENT_SPEED:
            MoveSpeedDialog->show();
            break;
        case ACCELERATION:
            AccelerationDialog->show();
            break;
        case DAMAGE:
            DamageDialog->show();
            break;
        case CRIT_CHANCE:
            CritChanceDialog->show();
            break;
        case CRIT_MULT:
            CritMultiplierDialog->show();
            break;
        case CRIT_BONUS:
            CritBonusDialog->show();
            break;
        case CAST_SOUND:
            CastSoundDialog->show();
            break;
        case CAST_EFFECT:
            CastEffectDialog->show();
            break;
        case CHANNEL_SOUND:
            ChannelSoundDialog->show();
            break;
        case CHANNEL_EFFECT:
            ChannelEffectDialog->show();
            break;
        default:
            //Do nothing
            break;
    }
}

void AbilityManager::processTableFieldEnterPress()
{
    showDialog(ui->EditTable->currentRow());
}

bool AbilityManager::eventFilter(QObject *obj, QEvent *event)
{
    if(obj == ui->EditTable &&
        event->type() == QEvent::KeyPress)
    {
        auto keyEvent = static_cast<QKeyEvent*>(event);
        if(keyEvent->key() == Qt::Key_Enter || keyEvent->key() == Qt::Key_Return){
            processTableFieldEnterPress();
            return true;
        }
    }

    return false;
}

QString AbilityManager::expToString(Expression *exp)
{
    QString str = "";

    if(exp){
        str = exp->toString();
    }

    return str;
}

void AbilityManager::on_AddButton_released()
{
    QString name = ui->AddInput->text();
    if(!name.isEmpty() && !abilityExists(name)){
        Ability *ability = new Ability();
        ability->setNormalText(name);
        this->addAbility(ability);
    }
}

void AbilityManager::on_List_currentRowChanged(int currentRow)
{
    if(currentRow >= 0 && currentRow < abilities.size()){
        setEditTableAbility(abilities[currentRow]);
    }
}

void AbilityManager::on_EditTable_cellChanged(int row, int)
{
    if(initialized && row >= 0){
        QString property = ui->EditTable->item(row, 0)->text();
        auto ability = currentAbility();
        setAbilityProperty(ability, static_cast<Fields>(row), property.toInt());
    }
}

void AbilityManager::on_RemoveButton_released()
{
    int row = ui->List->currentRow();
    if(row >= 0){
        this->removeAbility(row);
    }
}
