#ifndef ABILITYMANAGER_H
#define ABILITYMANAGER_H

#include <QWidget>
#include <QCheckBox>
#include <QComboBox>

#include "SpriteCreator/ResourceManager/ExpressionDialog.h"
#include <SpriteCreator/ResourceOpenDialog.h>
#include "Game/Globals.h"
#include "Game/Ability.h"

#include <QDomElement>

namespace Ui {
class AbilityManager;
}

class AbilityManager : public QWidget
{
    Q_OBJECT

public:
    explicit AbilityManager(QWidget *parent = nullptr);
    ~AbilityManager();

    enum Fields{
        //Note: fields marked as categories are table headers or unused
        GENERIC_INFORMATION,        //Category
        TEXT_LEARN,
        TEXT_LEARN_EXTENDED,
        TEXT_NORMAL,
        TEXT_NORMAL_EXTENDED,
        TEXT_DISABLED_EXTENDED,
        CAST_INFORMATION,
        CAST_TIME,
        IS_CHANNELLED,
        CHANNEL_DURATION,
        COOLDOWN,
        RANGE,
        ABILITY_DAMAGE,
        TARGET_TYPE,
        MANA_COST,
        MANA_DRAIN,
        MAXIMUM_LEVELS,
        LEVEL_GAP,
        ART,                        //Category
        CAST_SOUND,
        CAST_EFFECT,
        CHANNEL_SOUND,
        CHANNEL_EFFECT,
        UNIT_ATTRIBUTE_MODIFIERS,   //Category
        INTELLECT,
        STRENGTH,
        AGILITY,
        CONSTITUTION,
        SPIRIT,
        HEALTH_FIELD,
        HEALTH_REGEN,
        MANA_FIELD,
        MANA_REGEN,
        MOVEMENT_SPEED,
        ACCELERATION,
        ATTACK_MODIFIERS,           //Category
        DISABLES_COLLISION,
        DAMAGE,
        CRIT_CHANCE,
        CRIT_MULT,
        CRIT_BONUS,
        N_FIELDS                    //Category
    };

    void initializeTable();

    QDomElement abilityToXML(Ability *ability, QDomDocument *doc);
    QDomElement getXML(QDomDocument *doc);

signals:
    void itemChanged();

private slots:
    void saveCastSound(QString str);
    void saveCastEffect(QString str);
    void saveChannelSound(QString str);
    void saveChannelEffect(QString str);
    void saveCollision();
    void saveChannelled();
    void saveTargetType();
    void processExpressions(int ID, QString str);

private slots:
    void on_EditTable_cellDoubleClicked(int row, int column);

    void on_AddButton_released();

    void on_List_currentRowChanged(int currentRow);

    void on_EditTable_cellChanged(int row, int column);

    void on_RemoveButton_released();

private:
    Ui::AbilityManager *ui;
    bool initialized = false;
    bool eventFilter(QObject *obj, QEvent *event);
    QString expToString(Expression *exp);

    //Object lists
    QList<Ability*> abilities;

    //Object list manipulation
    void addAbility(Ability *ability);
    void removeAbility(int index);
    bool abilityExists(QString name);
    void setAbilityProperty(Ability *ability, Fields field, QString str);
    void setAbilityProperty(Ability *ability, Fields field, int val);
    void setAbilityProperty(Ability *ability, Fields field, Expression *exp);
    Ability *currentAbility();


    //GUI Update functions
    void refreshAbilityList();
    void setEditTableAbility(Ability *ability);
    void setField(Fields field, QString val);
    void setField(Fields field, int val);
    void setField(Fields field, Expression *exp);
    void updateExpressionDialog(Fields field, QString str);

    //GUI Display functions
    void showDialog(int row);
    void processTableFieldEnterPress();


    QCheckBox *IsChannelledCheck                 = nullptr;
    QCheckBox *CollisionCheck                   = nullptr;
    QComboBox *TargetTypeInput                  = nullptr;
    ResourceOpenDialog *CastSoundDialog         = nullptr;
    ResourceOpenDialog *CastEffectDialog        = nullptr;
    ResourceOpenDialog *ChannelSoundDialog      = nullptr;
    ResourceOpenDialog *ChannelEffectDialog     = nullptr;
    ExpressionDialog *TextLearnDialog           = nullptr;
    ExpressionDialog *TextLearnExtDialog        = nullptr;
    ExpressionDialog *TextNormalDialog          = nullptr;
    ExpressionDialog *TextNormalExtDialog       = nullptr;
    ExpressionDialog *TextDisableExtDialog      = nullptr;
    ExpressionDialog *CastTimeDialog            = nullptr;
    ExpressionDialog *ChannelDurationDialog     = nullptr;
    ExpressionDialog *CooldownDialog            = nullptr;
    ExpressionDialog *RangeDialog               = nullptr;
    ExpressionDialog *AbilityDamageDialog       = nullptr;
    ExpressionDialog *ManaCostDialog            = nullptr;
    ExpressionDialog *ManaDrainDialog           = nullptr;
    ExpressionDialog *IntellectDialog           = nullptr;
    ExpressionDialog *StrengthDialog            = nullptr;
    ExpressionDialog *AgilityDialog             = nullptr;
    ExpressionDialog *ConstitutionDialog        = nullptr;
    ExpressionDialog *SpiritDialog              = nullptr;
    ExpressionDialog *HealthDialog              = nullptr;
    ExpressionDialog *HealthRegenDialog         = nullptr;
    ExpressionDialog *ManaDialog                = nullptr;
    ExpressionDialog *ManaRegenDialog           = nullptr;
    ExpressionDialog *MoveSpeedDialog           = nullptr;
    ExpressionDialog *AccelerationDialog        = nullptr;
    ExpressionDialog *DamageDialog              = nullptr;
    ExpressionDialog *CritChanceDialog          = nullptr;
    ExpressionDialog *CritMultiplierDialog      = nullptr;
    ExpressionDialog *CritBonusDialog           = nullptr;
};

#endif // ABILITYMANAGER_H
