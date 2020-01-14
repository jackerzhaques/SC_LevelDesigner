#ifndef ABILITY_H
#define ABILITY_H

#include <QObject>
#include <QString>

#include "Globals.h"
#include "Game/Spritesheet.h"
#include "Game/Sound.h"
#include "Game/Expression.h"

class Ability : public QObject
{
    Q_OBJECT
public:
    explicit Ability(QObject *parent = nullptr);

    QString getLearnText() const;
    void setLearnText(const QString &value);

    QString getLearnTextExtended() const;
    void setLearnTextExtended(const QString &value);

    QString getNormalText() const;
    void setNormalText(const QString &value);

    QString getNormalTextExtended() const;
    void setNormalTextExtended(const QString &value);

    QString getDisabledTextExtended() const;
    void setDisabledTextExtended(const QString &value);

    Expression *getCastTime() const;
    void setCastTime(Expression *value);

    bool getIsChanneled() const;
    void setIsChanneled(bool value);

    Expression *getChannelDuration() const;
    void setChannelDuration(Expression *value);

    Expression *getCooldown() const;
    void setCooldown(Expression *value);

    Expression *getRange() const;
    void setRange(Expression *value);

    TargetType getTargetType() const;
    void setTargetType(const TargetType &value);

    Expression *getManaCost() const;
    void setManaCost(Expression *value);

    Expression *getManaDrain() const;
    void setManaDrain(Expression *value);

    int getMaxLevels() const;
    void setMaxLevels(int value);

    int getLevelGap() const;
    void setLevelGap(int value);

    Sound *getCastSound() const;
    void setCastSound(Sound *value);

    Spritesheet *getCastEffect() const;
    void setCastEffect(Spritesheet *value);

    Sound *getChannelSound() const;
    void setChannelSound(Sound *value);

    Spritesheet *getChannelEffect() const;
    void setChannelEffect(Spritesheet *value);

    Expression *getIntellect() const;
    void setIntellect(Expression *value);

    Expression *getStrength() const;
    void setStrength(Expression *value);

    Expression *getAgility() const;
    void setAgility(Expression *value);

    Expression *getConstitution() const;
    void setConstitution(Expression *value);

    Expression *getSpirit() const;
    void setSpirit(Expression *value);

    Expression *getHealth() const;
    void setHealth(Expression *value);

    Expression *getHealthRegen() const;
    void setHealthRegen(Expression *value);

    Expression *getMana() const;
    void setMana(Expression *value);

    Expression *getManaRegen() const;
    void setManaRegen(Expression *value);

    Expression *getMovementSpeed() const;
    void setMovementSpeed(Expression *value);

    Expression *getAcceleration() const;
    void setAcceleration(Expression *value);

    bool getDisablesCollision() const;
    void setDisablesCollision(bool value);

    Expression *getDamage() const;
    void setDamage(Expression *value);

    Expression *getCritChance() const;
    void setCritChance(Expression *value);

    Expression *getCritMultiplier() const;
    void setCritMultiplier(Expression *value);

    Expression *getCritBonus() const;
    void setCritBonus(Expression *value);

    Expression *getAbilityDamage() const;
    void setAbilityDamage(Expression *value);

signals:

public slots:

private:
    QString learnText                   = "Blank Ability";
    QString learnTextExtended           = "No description";
    QString normalText                  = "Blank Ability";
    QString normalTextExtended          = "No description";
    QString disabledTextExtended        = "Ability disabled";
    Expression* castTime                = nullptr;
    bool isChanneled                    = false;
    Expression* channelDuration         = nullptr;
    Expression* cooldown                = nullptr;
    Expression* range                   = nullptr;
    Expression* abilityDamage           = nullptr;
    TargetType targetType               = NO_TARGET;
    Expression* manaCost                = nullptr;
    Expression* manaDrain               = nullptr;
    int maxLevels                       = 0;
    int levelGap                        = 0;
    Sound* castSound                    = nullptr;
    Spritesheet* castEffect             = nullptr;
    Sound* channelSound                 = nullptr;
    Spritesheet* channelEffect          = nullptr;
    Expression* intellect               = nullptr;
    Expression* strength                = nullptr;
    Expression* agility                 = nullptr;
    Expression* constitution            = nullptr;
    Expression* spirit                  = nullptr;
    Expression* health                  = nullptr;
    Expression* healthRegen             = nullptr;
    Expression* mana                    = nullptr;
    Expression* manaRegen               = nullptr;
    Expression* movementSpeed           = nullptr;
    Expression* acceleration            = nullptr;
    bool disablesCollision              = false;
    Expression* damage                  = nullptr;
    Expression* critChance              = nullptr;
    Expression* critMultiplier          = nullptr;
    Expression* critBonus               = nullptr;
};

#endif // ABILITY_H
