#pragma once
#include "Entity.h"
#include "GameObjectManager.h"
#include"Timer.h"

class Enemy :
    public Entity
{
public:
    // ctor&dtor
    Enemy(Tag _tag, Animation* _animation, Box* _EnemyBox);
    Enemy(const Enemy& enemy);
    ~Enemy() override {}
    GameObject* clone() override { return new Enemy(*this); }
    void beDeleted() override { delete this; }

	// getters&setters
	void setInvincible(bool invincible) { isInvincible = invincible; }
	bool getInvincible() const { return isInvincible; }
	void setWillDrop(bool willDrop) { willDrop_ = willDrop; }
	bool willDrop() const { return willDrop_; }

    // ½Ó¿Ú
    void draw(SDL_Renderer* SDL_renderer) override;
    void update(int delta) override;
    void setExist(bool isExist_) override {
        this->isExist_ = isExist_;
        hurtBox->setCollidable(isExist_);
		entityBox->setCollidable(isExist_);
    }
    // ÉËº¦¼õÑª
    void decreaseHP(int _damage) override;

    void initEnemy();
private:
    CollisionBox* hurtBox = nullptr;
    Timer* invincibleDur;
    bool isInvincible = false;
	bool willDrop_ = false;
};
