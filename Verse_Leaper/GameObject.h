#pragma once
#include <SDL_mixer.h>
#include"Drawable.h"
#include"Updatable.h"
#include"Animation.h"
#include"Box.h"
#include"Vector2.h"
#include"Camera.h"
#include"Tag.h"

#include"CollisionManager.h"
#include<iostream>

class GameObject :
    public Drawable, public Updatable
{
public:
    // ctor&dtor
    GameObject(Tag tag_, Animation* _animation, Box* _box, int _HP = 0, int _AD = 0, int _MaxHP = 0);
    GameObject(const GameObject& obj);
    virtual ~GameObject();
    // ½Ó¿Ú
    void draw(SDL_Renderer* SDL_renderer) override;
    void update(int delta) override = 0;
    // º¯Êý
    virtual GameObject* clone() = 0;
    virtual void beDeleted() = 0;
    // getters&setters
    Tag getTag() const { return this->tag; }

    bool isExist() { return this->isExist_; }
    virtual void setExist(bool isExist) { this->isExist_ = isExist; }

	bool IsDead() const { return isDead_; }
	void setIsDead(bool isDead) { 
        if (!isDead) {
            this->setHP(8);
        }
        isDead_ = isDead; 
    }

	void setArrow(bool hasArrow) { hasArrow_ = hasArrow; }
	bool hasArrow() const { return hasArrow_; }
	void setSword(bool hasSword) { hasSword_ = hasSword; }
	bool hasSword() const { return hasSword_; }
	void setAlcohol(bool hasAlcohol) { hasAlcohol_ = hasAlcohol; } 
	bool hasAlcohol() const { return hasAlcohol_; }
	void setDoubleJumpSkill(bool hasDoubleJumpSkill) { hasDoubleJumpSkill_ = hasDoubleJumpSkill; }
	bool hasDoubleJumpSkill() const { return hasDoubleJumpSkill_; }
	void setPotion(bool hasPotion) { this->hasPotion = hasPotion; }
	bool getPotion() const { return hasPotion; }

    Animation* getAnimation() const { return animation; }

    bool isRunning() const { return speed.getX() != 0; }
    Vector2 getSpeed() const { return speed; }
    void setSpeed(double x, double y) { speed = Vector2(x, y); }
    void setSpeed(Vector2 &vec2) { speed = vec2; }
    void setSpeedX(double x) { speed.setX(x); }
    void setSpeedY(double y) { speed.setY(y); }
    void setSpeedUnit();
    void addSpeed(double x, double y) { speed += Vector2(x, y); }
	void setJumpSpeed(int jumpSpeed) { JumpSpeed = jumpSpeed; }
	int getJumpSpeed() const { return JumpSpeed; }
    void jump();

    Vector2 getGravity() const { return gravity; }
    void setGravity(double x, double y) { gravity = Vector2(x, y); }

    Box* getBox() { return box; }
    int getBoxX() { return box->getX(); }
    int getBoxCenterX() { return box->getX() + box->getWidth() / 2; }
    int getBoxY() { return box->getY(); }
    int getBoxCenterY() { return box->getY() + box->getHeight() / 2; }
    int getBoxWidth() { return box->getWidth(); }
    int getBoxHeight() { return box->getHeight(); }
    void setBoxY(int y) { box->setY(y); }
    void setBoxX(int x) { box->setX(x); }

    void setAtlas(Atlas* atlas) { this->animation->setAtlas(atlas); }

	int getPotionCount() const { return PotionCount; }
    void setPotionCount(int potionCount) { PotionCount = potionCount; }
	int getMaxHP() const { return MaxHP; }
	void setMaxHP(int _MaxHP) { MaxHP = _MaxHP; }
    int getHP() const { return HP; }
    void setHP(int _HP) { HP = _HP; }
    int getAD() const { return AD; }
    void setAD(int _AD) { AD = _AD; }
    virtual void decreaseHP(int _damage) {}
    virtual void die() {}

    virtual void initPlayerCtor() {}

protected:
    Tag tag;
    bool isExist_ = true;
	bool isDead_ = false;
	bool hasArrow_ = false;
	bool hasSword_ = false;
	bool hasAlcohol_ = false;
	bool hasDoubleJumpSkill_ = false;
	bool hasPotion = true;
    Animation* animation;
    Box* box;
    Vector2 speed = Vector2(0, 0);
    Vector2 gravity = Vector2(0, 1);
	int PotionCount = 0;
	int JumpSpeed = -25;
    int MaxHP;
    int HP;
    int AD;
    void updatePosition();
};