#include "Unit.h"

Unit::Unit(QGraphicsItem *parent) : Entity(parent)
{
    this->setType(UNIT);
}

//NOTE. Setters and getters auto generated.

//Setter funcs
void Unit::setIntellect(int intellect){
    this->intellect = intellect;
}

void Unit::setStrength(int strength){
    this->strength = strength;
}

void Unit::setAgility(int agility){
    this->agility = agility;
}

void Unit::setConstitution(int constitution){
    this->constitution = constitution;
}

void Unit::setSpirit(int spirit){
    this->spirit = spirit;
}

void Unit::setManaType(ManaType manaType){
    this->manaType = manaType;
}

void Unit::setManaBase(double manaBase){
    this->manaBase = manaBase;
}

void Unit::setCurrentMana(double currentMana){
    this->currentMana = currentMana;
}

void Unit::setManaRegen(double manaRegen){
    this->manaRegen = manaRegen;
}

void Unit::setHealthBase(double healthBase){
    this->healthBase = healthBase;
}

void Unit::setCurrentHealth(double currentHealth){
    this->currentHealth = currentHealth;
}

void Unit::setHealthRegen(double healthRegen){
    this->healthRegen = healthRegen;
}

void Unit::setAttackType(AttackType attackType){
    this->attackType = attackType;
}

void Unit::setRange(double range){
    this->range = range;
}

void Unit::setBaseDamage(double baseDamage){
    this->baseDamage = baseDamage;
}

void Unit::setCritChance(double critChance){
    this->critChance = critChance;
}

void Unit::setCritMultiplier(double critMultiplier){
    this->critMultiplier = critMultiplier;
}

void Unit::setCritBonus(double critBonus){
    this->critBonus = critBonus;
}

void Unit::setMissileArc(double missileArc){
    this->missileArc = missileArc;
}

void Unit::setSplashRange(double splashRange){
    this->splashRange = splashRange;
}

void Unit::setSprite(Spritesheet* sprite){
    this->sprite = sprite;
}

void Unit::setSpritePath(QString spritePath){
    this->spritePath = spritePath;
}

void Unit::setSpriteXMLPath(QString spriteXMLPath){
    this->spriteXMLPath = spriteXMLPath;
}

void Unit::setIcon(QPixmap icon){
    this->icon = icon;
}

void Unit::setIconPath(QString iconPath){
    this->iconPath = iconPath;
}

void Unit::setProjectileOrigin(QPointF projectileOrigin){
    this->projectileOrigin = projectileOrigin;
}

void Unit::setMovementType(MovementType type)
{
    this->moveType = type;
}

void Unit::setBaseMoveSpeed(double baseMoveSpeed){
    this->baseMoveSpeed = baseMoveSpeed;
}

void Unit::setAcceleration(double acceleration){
    this->acceleration = acceleration;
}

void Unit::setHasCollision(bool hasCollision){
    this->hasCollision = hasCollision;
}


//Getter funxs
int Unit::getIntellect(){
   return this->intellect;
}

int Unit::getStrength(){
   return this->strength;
}

int Unit::getAgility(){
   return this->agility;
}

int Unit::getConstitution(){
   return this->constitution;
}

int Unit::getSpirit(){
   return this->spirit;
}

ManaType Unit::getManaType(){
   return this->manaType;
}

double Unit::getManaBase(){
   return this->manaBase;
}

double Unit::getCurrentMana(){
   return this->currentMana;
}

double Unit::getManaRegen(){
   return this->manaRegen;
}

double Unit::getHealthBase(){
   return this->healthBase;
}

double Unit::getCurrentHealth(){
   return this->currentHealth;
}

double Unit::getHealthRegen(){
   return this->healthRegen;
}

AttackType Unit::getAttackType(){
   return this->attackType;
}

double Unit::getRange(){
   return this->range;
}

double Unit::getBaseDamage(){
   return this->baseDamage;
}

double Unit::getCritChance(){
   return this->critChance;
}

double Unit::getCritMultiplier(){
   return this->critMultiplier;
}

double Unit::getCritBonus(){
   return this->critBonus;
}

double Unit::getMissileArc(){
   return this->missileArc;
}

double Unit::getSplashRange(){
   return this->splashRange;
}

Spritesheet* Unit::getSprite(){
   return this->sprite;
}

QString Unit::getSpritePath(){
   return this->spritePath;
}

QString Unit::getSpriteXMLPath(){
   return this->spriteXMLPath;
}

QPixmap Unit::getIcon(){
   return this->icon;
}

QString Unit::getIconPath(){
   return this->iconPath;
}

QPointF Unit::getProjectileOrigin(){
    return this->projectileOrigin;
}

MovementType Unit::getMoveType()
{
    return this->moveType;
}

double Unit::getBaseMoveSpeed(){
   return this->baseMoveSpeed;
}

double Unit::getAcceleration(){
   return this->acceleration;
}

bool Unit::getHasCollision(){
    return this->hasCollision;
}

void Unit::debug()
{
    qDebug() << "Unit: " << this->getName();
    qDebug() << "   intellect: " << intellect;
    qDebug() << "   strength: " << strength;
    qDebug() << "   agility: " << agility;
    qDebug() << "   constitution: " << constitution;
    qDebug() << "   spirit: " << spirit;
    qDebug() << "   manaType: " << manaType;
    qDebug() << "   manaBase: " << manaBase;
    qDebug() << "   currentMana: " << currentMana;
    qDebug() << "   manaRegen: " << manaRegen;
    qDebug() << "   healthBase: " << healthBase;
    qDebug() << "   currentHealth: " << currentHealth;
    qDebug() << "   healthRegen: " << healthRegen;
    qDebug() << "   attackType: " << attackType;
    qDebug() << "   range: " << range;
    qDebug() << "   baseDamage: " << baseDamage;
    qDebug() << "   critChance: " << critChance;
    qDebug() << "   critMultiplier: " << critMultiplier;
    qDebug() << "   critBonus: " << critBonus;
    qDebug() << "   missileArc: " << missileArc;
    qDebug() << "   splashRange: " << splashRange;
    qDebug() << "   sprite: " << sprite;
    qDebug() << "   spritePath: " << spritePath;
    qDebug() << "   spriteXMLPath: " << spriteXMLPath;
    qDebug() << "   icon: " << icon;
    qDebug() << "   iconPath: " << iconPath;
    qDebug() << "   projectileOrigin: " << projectileOrigin;
    qDebug() << "   movementType: " << moveType;
    qDebug() << "   baseMoveSpeed: " << baseMoveSpeed;
    qDebug() << "   acceleration: " << acceleration;
    qDebug() << "   hasCollision: " << hasCollision;
}

QString Unit::getObjectUID() const
{
    return objectUID;
}

void Unit::setObjectUID(const QString &value)
{
    objectUID = value;
}

QString Unit::getEntityUID() const
{
    return entityUID;
}

void Unit::setEntityUID(const QString &value)
{
    entityUID = value;
}
