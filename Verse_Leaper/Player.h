#pragma once
#include"GameObjectManager.h"
#include"Entity.h"
#include"Camera.h"
#include"Timer.h"
#include"Image.h"
#include"Map.h"

class Player : public Entity
{
public:
    // ctor & dtor
    Player(Tag _tag, Animation* _animation, Animation* swordAnimation_, Animation * arrowAnimation_, Box* _playerBox, int initHP, int initAD, int initMaxHP);
    ~Player() override {
        delete swordAnimation_;
    }
    GameObject* clone() override { return nullptr; }
    void beDeleted() override { delete this; }
	void initPlayerCollisionBox();
    void initPlayerCtor() override;
    // ½Ó¿Ú
    void update(int delta) override;
    void draw(SDL_Renderer* SDL_renderer) override;
    // getters&setters
    void setExist(bool isExist_) override {
        this->isExist_ = isExist_;
        collisionBox->setCollidable(isExist_);
    }

    bool willJump() const { return willJump_; }
    void setWillJump(bool willJump) { willJump_ = willJump; }

    bool willUseArrow() const { return willUseArrow_; }
    void setWillUseArrow(bool willUseArrow) { willUseArrow_ = willUseArrow; }

    bool getIsFacingRight() const { return isFacingRight; }
    void setFacingRight(bool _isFacingRight) { isFacingRight = _isFacingRight; }

	bool getIsInvincible() const { return isInvincible; }
	void setIsInvincible(bool isInvincible) { this->isInvincible = isInvincible; }

    bool isUsingAlcohol() const { return isUsingAlcohol_; }
    void setUsingAlcohol(bool isUsingAlcohol) { this->isUsingAlcohol_ = isUsingAlcohol; }
    bool isUsingArrow() const { return isUsingArrow_; }
    void setUsingArrow(bool isUsingArrow) { this->isUsingArrow_ = isUsingArrow; }
    bool isUsingSword() const { return isUsingSword_; }
    void setUsingSword(bool isUsingSword) { this->isUsingSword_ = isUsingSword; }
	void setCanDoubleJump(bool canDoubleJump) { this->canDoubleJump_ = canDoubleJump; }
	bool canDoubleJump() const { return canDoubleJump_; }
	bool isUsedAlcohol() const { return isUsedAlcohol_; }
	void setIsUsedAlcohol(bool isUsedAlcohol) { this->isUsedAlcohol_ = isUsedAlcohol; }

    bool isInArrowCD() const { return isInArrowCD_; }

    Vector2 getLastSavePointPosition() const { return lastSavePointPosition_; }
    void setLastSavePointPosition(const Vector2& position) { lastSavePointPosition_ = position; }
    Map* getLastSavePointMap() const { return lastSavePointMap_; }
    void setLastSavePointMap(Map* map) { lastSavePointMap_ = map; }

    Animation* getSwordAnimation() const { return swordAnimation_; }
    Animation* getArrowAnimation() const { return arrowAnimation_; }

    CollisionBox* getCollisionBox();
    CollisionBox* getSwordBox();
    CollisionBox* getArrowBox_block();
    CollisionBox* getArrowBox_enemy();
    void setArrowBoxExist(bool isExist);
    void setSwordBoxExist(bool isExist);

    void setArrowSpeed(Vector2 speed_);

    CollisionBox* getHurtBox();

    Timer* getAlcoholCD() { return alcoholDur; }
    Timer* getAttackCD() { return swordCD; }
	Timer* getPotionCD() { return potionCD; }

    void decreaseHP(int _damage);
    void useSword();
    void useAlcohol();
    void useArrow();
	void usePotion();
    void drawSkill(int x, int y, int width, int height, SDL_Renderer* renderer, Image* image, const char* path);
    void drawSkillcd(int x, int y, int width, int height, Timer* timer, SDL_Renderer* renderer);
	void drawPotionSkill(int x, int y, int width, int height, SDL_Renderer* renderer, Image* image);
	void drawHP(int x, int y, int width, int height, SDL_Renderer* SDL_renderer, Image* image1, 
        Image* image2, const char* path1, const char* path2);

private:
    bool willJump_ = false;
    bool willUseArrow_ = false;
    bool hasInited_ = false;
    bool isFacingRight = true;
    bool isInvincible = false;
	bool isUsingAlcohol_ = false;
	bool isUsingArrow_ = false;
    bool isUsingSword_ = false;
	bool isUsedAlcohol_ = false;
    bool isInAlcoholCD = false;
    bool isInArrowCD_ = false;
	bool isInPotionCD_ = false;
	bool canDoubleJump_ = false;
    Vector2 lastSavePointPosition_ = Vector2(0, 0);
    Map* lastSavePointMap_ = nullptr;
    Animation* swordAnimation_;
    Animation* arrowAnimation_;
    Image* alcoholImage = nullptr;
	Image* bowImage = nullptr;
	Image* BloodImage1 = nullptr;
	Image* BloodImage2 = nullptr;
	Image* potionImage = nullptr;
    CollisionBox* collisionBox = nullptr;
    CollisionBox* swordBox = nullptr;
    CollisionBox* arrowBox_enemy = nullptr;
    CollisionBox* arrowBox_block = nullptr;
    CollisionBox* interactBox = nullptr;
    CollisionBox* hurtBox = nullptr;
    Timer* alcoholDur;
	Timer* arrowDur;
	Timer* alcoholCD;
	Timer* arrowCD;
    Timer* swordCD;
    Timer* potionCD;
    Timer* invincibleDur;
};