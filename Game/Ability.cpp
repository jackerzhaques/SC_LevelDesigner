#include "Ability.h"

Ability::Ability(QObject *parent) : QObject(parent)
{

}

QString Ability::getLearnText() const
{
    return learnText;
}

void Ability::setLearnText(const QString &value)
{
    learnText = value;
}

QString Ability::getLearnTextExtended() const
{
    return learnTextExtended;
}

void Ability::setLearnTextExtended(const QString &value)
{
    learnTextExtended = value;
}

QString Ability::getNormalText() const
{
    return normalText;
}

void Ability::setNormalText(const QString &value)
{
    normalText = value;
}

QString Ability::getNormalTextExtended() const
{
    return normalTextExtended;
}

void Ability::setNormalTextExtended(const QString &value)
{
    normalTextExtended = value;
}

QString Ability::getDisabledTextExtended() const
{
    return disabledTextExtended;
}

void Ability::setDisabledTextExtended(const QString &value)
{
    disabledTextExtended = value;
}

Expression *Ability::getCastTime() const
{
    return castTime;
}

void Ability::setCastTime(Expression *value)
{
    castTime = value;
}

bool Ability::getIsChanneled() const
{
    return isChanneled;
}

void Ability::setIsChanneled(bool value)
{
    isChanneled = value;
}

Expression *Ability::getChannelDuration() const
{
    return channelDuration;
}

void Ability::setChannelDuration(Expression *value)
{
    channelDuration = value;
}

Expression *Ability::getCooldown() const
{
    return cooldown;
}

void Ability::setCooldown(Expression *value)
{
    cooldown = value;
}

Expression *Ability::getRange() const
{
    return range;
}

void Ability::setRange(Expression *value)
{
    range = value;
}

TargetType Ability::getTargetType() const
{
    return targetType;
}

void Ability::setTargetType(const TargetType &value)
{
    targetType = value;
}

Expression *Ability::getManaCost() const
{
    return manaCost;
}

void Ability::setManaCost(Expression *value)
{
    manaCost = value;
}

Expression *Ability::getManaDrain() const
{
    return manaDrain;
}

void Ability::setManaDrain(Expression *value)
{
    manaDrain = value;
}

int Ability::getMaxLevels() const
{
    return maxLevels;
}

void Ability::setMaxLevels(int value)
{
    maxLevels = value;
}

int Ability::getLevelGap() const
{
    return levelGap;
}

void Ability::setLevelGap(int value)
{
    levelGap = value;
}

Sound *Ability::getCastSound() const
{
    return castSound;
}

void Ability::setCastSound(Sound *value)
{
    castSound = value;
}

Spritesheet *Ability::getCastEffect() const
{
    return castEffect;
}

void Ability::setCastEffect(Spritesheet *value)
{
    castEffect = value;
}

Sound *Ability::getChannelSound() const
{
    return channelSound;
}

void Ability::setChannelSound(Sound *value)
{
    channelSound = value;
}

Spritesheet *Ability::getChannelEffect() const
{
    return channelEffect;
}

void Ability::setChannelEffect(Spritesheet *value)
{
    channelEffect = value;
}

Expression *Ability::getIntellect() const
{
    return intellect;
}

void Ability::setIntellect(Expression *value)
{
    intellect = value;
}

Expression *Ability::getStrength() const
{
    return strength;
}

void Ability::setStrength(Expression *value)
{
    strength = value;
}

Expression *Ability::getAgility() const
{
    return agility;
}

void Ability::setAgility(Expression *value)
{
    agility = value;
}

Expression *Ability::getConstitution() const
{
    return constitution;
}

void Ability::setConstitution(Expression *value)
{
    constitution = value;
}

Expression *Ability::getSpirit() const
{
    return spirit;
}

void Ability::setSpirit(Expression *value)
{
    spirit = value;
}

Expression *Ability::getHealth() const
{
    return health;
}

void Ability::setHealth(Expression *value)
{
    health = value;
}

Expression *Ability::getHealthRegen() const
{
    return healthRegen;
}

void Ability::setHealthRegen(Expression *value)
{
    healthRegen = value;
}

Expression *Ability::getMana() const
{
    return mana;
}

void Ability::setMana(Expression *value)
{
    mana = value;
}

Expression *Ability::getManaRegen() const
{
    return manaRegen;
}

void Ability::setManaRegen(Expression *value)
{
    manaRegen = value;
}

Expression *Ability::getMovementSpeed() const
{
    return movementSpeed;
}

void Ability::setMovementSpeed(Expression *value)
{
    movementSpeed = value;
}

Expression *Ability::getAcceleration() const
{
    return acceleration;
}

void Ability::setAcceleration(Expression *value)
{
    acceleration = value;
}

bool Ability::getDisablesCollision() const
{
    return disablesCollision;
}

void Ability::setDisablesCollision(bool value)
{
    disablesCollision = value;
}

Expression *Ability::getDamage() const
{
    return damage;
}

void Ability::setDamage(Expression *value)
{
    damage = value;
}

Expression *Ability::getCritChance() const
{
    return critChance;
}

void Ability::setCritChance(Expression *value)
{
    critChance = value;
}

Expression *Ability::getCritMultiplier() const
{
    return critMultiplier;
}

void Ability::setCritMultiplier(Expression *value)
{
    critMultiplier = value;
}

Expression *Ability::getCritBonus() const
{
    return critBonus;
}

void Ability::setCritBonus(Expression *value)
{
    critBonus = value;
}

Expression *Ability::getAbilityDamage() const
{
    return abilityDamage;
}

void Ability::setAbilityDamage(Expression *value)
{
    abilityDamage = value;
}
