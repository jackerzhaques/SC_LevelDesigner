#ifndef UNIT_H
#define UNIT_H

#include "Entity.h"

class Unit : public Entity
{
public:
    Unit(QGraphicsItem *parent = nullptr);

    //Setters
    void setIntellect(int intellect);
    void setStrength(int strength);
    void setAgility(int agility);
    void setConstitution(int constitution);
    void setSpirit(int spirit);
    void setManaType(ManaType manaType);
    void setManaBase(double manaBase);
    void setCurrentMana(double currentMana);
    void setManaRegen(double manaRegen);
    void setHealthBase(double healthBase);
    void setCurrentHealth(double currentHealth);
    void setHealthRegen(double healthRegen);
    void setAttackType(AttackType attackType);
    void setRange(double range);
    void setBaseDamage(double baseDamage);
    void setCritChance(double critChance);
    void setCritMultiplier(double critMultiplier);
    void setCritBonus(double critBonus);
    void setMissileArc(double missileArc);
    void setSplashRange(double splashRange);
    void setSprite(Spritesheet* sprite);
    void setSpritePath(QString spritePath);
    void setSpriteXMLPath(QString spriteXMLPath);
    void setIcon(QPixmap icon);
    void setIconPath(QString iconPath);
    void setProjectileOrigin(QPointF projectileOrigin);
    void setMovementType(MovementType type);
    void setBaseMoveSpeed(double baseMoveSpeed);
    void setAcceleration(double acceleration);
    void setHasCollision(bool hasCollision);

    //Getters
    int getIntellect();
    int getStrength();
    int getAgility();
    int getConstitution();
    int getSpirit();
    ManaType getManaType();
    double getManaBase();
    double getCurrentMana();
    double getManaRegen();
    double getHealthBase();
    double getCurrentHealth();
    double getHealthRegen();
    AttackType getAttackType();
    double getRange();
    double getBaseDamage();
    double getCritChance();
    double getCritMultiplier();
    double getCritBonus();
    double getMissileArc();
    double getSplashRange();
    Spritesheet* getSprite();
    QString getSpritePath();
    QString getSpriteXMLPath();
    QPixmap getIcon();
    QString getIconPath();
    QPointF getProjectileOrigin();
    MovementType getMoveType();
    double getBaseMoveSpeed();
    double getAcceleration();
    bool getHasCollision();

    void debug();

    QString getObjectUID() const;
    void setObjectUID(const QString &value);

    QString getEntityUID() const;
    void setEntityUID(const QString &value);

private:
    //Unit specific properties
    int intellect           = 0;
    int strength            = 0;
    int agility             = 0;
    int constitution        = 0;
    int spirit              = 0;
    ManaType manaType       = MANA;
    double manaBase         = 100;
    double currentMana      = 0;
    double manaRegen        = 1;
    double healthBase       = 100;
    double currentHealth    = 100;
    double healthRegen      = 1;
    AttackType attackType   = MELEE;
    double range            = 100;
    double baseDamage       = 5;
    double critChance       = 0.10;
    double critMultiplier   = 2.00;
    double critBonus        = 0;
    //Missile art not implemented yet
    double missileArc       = 0;    //Degrees from ground
    double splashRange      = 0;
    //Abilities not implemented yet
    //QList<Ability> abilities;
    //Passives not implemented yet
    //QList<Ability> passives;
    Spritesheet* sprite     = nullptr;
    QString spritePath      = "";
    QString spriteXMLPath   = "";
    QPixmap icon;
    QString iconPath        = "";
    QPointF projectileOrigin;
    MovementType moveType   = NORMAL;
    double baseMoveSpeed    = 100;
    double acceleration     = 50;
    bool hasCollision       = true;

    //Identification
    QString entityUID       = "0";
    QString objectUID       = "0";
};

#endif // UNIT_H
