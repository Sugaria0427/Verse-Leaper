#include "Player.h"
#include "PlayerIdleState.h"
#include "PlayerRunState.h"
#include "PlayerJumpState.h"
#include "PlayerArrowState.h"
#include "Panel.h"
#include "ResourceManager.h"

Player::Player(Tag _tag, Animation* _animation, Animation* swordAnimation_, Animation* arrowAnimation_, Box* _playerBox, int initHP, int initAD, int MaxHP)
    : Entity(_tag, _animation, _playerBox, initHP, initAD, MaxHP), swordAnimation_(swordAnimation_), arrowAnimation_(arrowAnimation_) {
    this->initPlayerCtor();
    this->initPlayerCollisionBox();
}
void Player::initPlayerCollisionBox(){
    if (hasInited_) this->initEntityBox();
    else hasInited_ = true;
    /// 碰撞箱
    {
        //剑气碰撞箱
        swordBox = CollisionManager::instance()->creatCollisionBox(this, box->getX(), box->getY(), box->getWidth(), box->getHeight());
        this->swordBox->setLayerSrc(CollisionBox::Layer::HitBox);
        this->swordBox->setLayerDst(CollisionBox::Layer::Enemy);
        swordBox->setOnCollide(
            [this](CollisionBox* boxDst) {
                std::cout << "剑气碰撞了Enemy" << std::endl;
                boxDst->getOwner()->decreaseHP(this->getAD());
            }
        );
        this->swordBox->setCollidable(false);
        //弓箭碰撞箱
        arrowBox_enemy = CollisionManager::instance()->creatCollisionBox(this, box->getX(), box->getY() + 20, 100, 30);
        this->arrowBox_enemy->setLayerSrc(CollisionBox::Layer::Arrow);
        this->arrowBox_enemy->setLayerDst(CollisionBox::Layer::Enemy);
        arrowBox_enemy->setOnCollide(
            [this](CollisionBox* boxDst) {
                std::cout << "弓箭碰撞了Enemy" << std::endl;
                boxDst->getOwner()->decreaseHP(this->getAD() * 2);
                this->arrowBox_enemy->setCollidable(false);
                this->arrowBox_block->setCollidable(false);
            }
        );
        this->arrowBox_enemy->setCollidable(false);
        arrowBox_block = CollisionManager::instance()->creatCollisionBox(this, box->getX(), box->getY() + 20, 100, 30);
        this->arrowBox_block->setLayerSrc(CollisionBox::Layer::Arrow);
        this->arrowBox_block->setLayerDst(CollisionBox::Layer::Block);
        arrowBox_block->setOnCollide(
            [this](CollisionBox* boxDst) {
                std::cout << "弓箭碰撞了Block" << std::endl;
                this->arrowBox_enemy->setCollidable(false);
                this->arrowBox_block->setCollidable(false);
            }
        );
        this->arrowBox_block->setCollidable(false);
        //互动碰撞箱
        interactBox = CollisionManager::instance()->creatCollisionBox(this, box->getX(), box->getY(), box->getWidth(), box->getHeight());
        this->interactBox->setLayerSrc(CollisionBox::Layer::Player);
        this->interactBox->setLayerDst(CollisionBox::Layer::Interact);
        interactBox->setOnCollide(
            [this](CollisionBox* boxDst) {
                std::cout << "Player碰撞了DropItem" << std::endl;
            }
        );
        this->interactBox->setCollidable(true);
        // 受击碰撞箱
        hurtBox = CollisionManager::instance()->creatCollisionBox(this, box->getX(), box->getY(), box->getWidth(), box->getHeight());
        this->hurtBox->setLayerSrc(CollisionBox::Layer::Player);
        this->hurtBox->setLayerDst(CollisionBox::Layer::Enemy);
        hurtBox->setOnCollide(
            [this](CollisionBox* boxDst) {
                std::cout << "player收到enemy的伤害" << std::endl;
                if (!boxDst->getOwner()->IsDead()) {
                    this->decreaseHP(boxDst->getOwner()->getAD());
                }
            }
        );
        this->hurtBox->setCollidable(true);
    }
}
void Player::initPlayerCtor()
{
    this->lastSavePointMap_ = MapManager::instance()->getCurrentMap();
    /// 有限状态机
    {
        stateMacine = StateMacine();
        stateMacine.addStateNode("Idle", new PlayerIdleState(this));
        stateMacine.addStateNode("Run", new PlayerRunState(this));
        stateMacine.addStateNode("Jump", new PlayerJumpState(this));
        stateMacine.addStateNode("Arrow", new PlayerArrowState(this));
        stateMacine.setInitState("Idle");
    }
    
    /// 持续时间计时器
    {
        // 酒持续时间计时器
        alcoholDur = new Timer();
        this->alcoholDur->setWaitTime(15000); // 酒持续时间为15秒
        this->alcoholDur->setOneShot(false);
        this->alcoholDur->setCallback(
            [this]() {
                this->setUsingAlcohol(false);
                this->setAD(1);
                for (GameObject* obj : GameObjManager::instance()->getVec()) {
                    if (obj->getTag() == Tag::Block_Cloud1 && obj->isExist()) {
                        obj->setExist(false);
                    }
                    if (obj->getTag() == Tag::Block_Cloud2 && obj->isExist()) {
                        obj->setExist(false);
                    }
                }
            }
        );
        // 弓箭持续时间计时器
        arrowDur = new Timer();
        this->arrowDur->setWaitTime(5000);
        this->arrowDur->setCallback(
            [this]() {
                this->setUsingArrow(false);
                this->setAD(1);
            }
        );
        // 无敌持续时间计时器
        invincibleDur = new Timer();
        this->invincibleDur->setWaitTime(500);
        this->invincibleDur->setOneShot(true);
        this->invincibleDur->setCallback(
            [this]()
            {
                isInvincible = false;
            }
        );
    }

    /// 冷却
    {
        // 剑冷却
        swordCD = new Timer();
        this->swordCD->setWaitTime(400);   // cd
        this->swordCD->pause();            // 暂停
        this->swordCD->setCallback(
            [this]() {  // 攻击冷却结束
                this->setUsingSword(false); // 设置可攻击
                this->swordCD->pause();     // 暂停冷却计时器
            }
        );
        // 酒冷却
        alcoholCD = new Timer();
        this->alcoholCD->setWaitTime(20000);
        this->alcoholCD->setCallback(
            [this]() {
                isInAlcoholCD = false;
                this->alcoholCD->pause();
            }
        );
        // 弓冷却
        arrowCD = new Timer();
        this->arrowCD->setWaitTime(3000);
        this->arrowCD->setCallback(
            [this]() {
                isInArrowCD_ = false;
                this->arrowCD->pause();
            }
        );
		// 药瓶冷却
		potionCD = new Timer();
		this->potionCD->setWaitTime(5000);
		this->potionCD->setCallback(
			[this]() {
				isInPotionCD_ = false;
                this->potionCD->pause();
			}
		);
	}

    // 设置动画callback
    swordAnimation_->setCallback(
        [this]() {
            this->swordBox->setCollidable(false);
        }
    );
}

void Player::update(int delta) {
    if (isExist_) {
        // 根据不同移动方向切换面朝方向
        if (this->speed.getX() < 0)
            this->setFacingRight(false);
        else if (this->speed.getX() > 0)
            this->setFacingRight(true);
        // 碰撞箱更新
        Entity::update(delta);
        if (swordBox->canCollide()) 
            this->swordAnimation_->updateIdxFrame(delta);
        if (arrowBox_enemy->canCollide()) {
            this->arrowAnimation_->updateIdxFrame(delta);
            this->arrowBox_enemy->setBox(
                arrowBox_enemy->getX() + arrowBox_enemy->speed.getX() * delta,
                arrowBox_enemy->getY() + arrowBox_enemy->speed.getY() * delta,
                arrowBox_enemy->getWidth(),
                arrowBox_enemy->getHeight()
            );
            this->arrowBox_block->setBox(
                arrowBox_block->getX() + arrowBox_block->speed.getX() * delta,
                arrowBox_block->getY() + arrowBox_block->speed.getY() * delta,
                arrowBox_block->getWidth(),
                arrowBox_block->getHeight()
            );
        }
        this->interactBox->setBox(
            this->getBoxX(), 
            this->getBoxY(), 
            this->getBoxWidth(), 
            this->getBoxHeight()
        );
        this->hurtBox->setBox(
            this->getBoxX(),
            this->getBoxY(),
            this->getBoxWidth(),
            this->getBoxHeight()
		);
        // 计时器更新
        if (this->isUsingAlcohol()) this->alcoholDur->update(delta);
        if (this->isUsingArrow()) this->arrowDur->update(delta);
        if (this->isInvincible) this->invincibleDur->update(delta);
        this->arrowCD->update(delta);
        this->swordCD->update(delta);
        this->alcoholCD->update(delta);
        this->potionCD->update(delta);
    }
}

void Player::decreaseHP(int _damage){
    if (!isInvincible) {
        HP -= _damage;
		Mix_PlayChannel(-1, ResourceManager::Instance().getSound(SoundType::grunt), 0);
        if (HP <= 0 && !isDead_) {
            this->setIsDead(true);
        }
        this->invincibleDur->restart();
        isInvincible = true;
    }
}

void Player::useSword()
{
    if (!this->isUsingSword()) {
        // 攻击冷却
        this->setUsingSword(true);
        this->getAttackCD()->restart();
        this->getAttackCD()->resume();
        // 根据Player面朝方向选择图集
        if (this->getIsFacingRight()) {
            this->getSwordAnimation()->setAtlas(ResourceManager::Instance().getAtlas(AtlasType::atlasHitBoxRight));
        }
        else {
            this->getSwordAnimation()->setAtlas(ResourceManager::Instance().getAtlas(AtlasType::atlasHitBoxLeft));
        }
        this->getSwordAnimation()->reset();
        // 使hitbox存在
        this->getSwordBox()->setCollidable(true);
        // 调整位置
        if (this->getIsFacingRight()) {
            this->getSwordBox()->setBox(
                this->getBoxX(),
                this->getBoxY() + this->getBoxHeight() * 0.2,
                this->getBoxWidth() * 3,
                this->getBoxHeight() / 1.5);
        }
        else {
            this->getSwordBox()->setBox(
                this->getBoxX() - this->getBoxWidth() * 2.0,
                this->getBoxY() + this->getBoxHeight() * 0.2,
                this->getBoxWidth() * 3,
                this->getBoxHeight() / 1.5
            );
        }
        // 播放攻击音效
        Mix_PlayChannel(-1, ResourceManager::Instance().getSound(SoundType::hit), 0);
    }
}


void Player::useAlcohol() {
    if (!isInAlcoholCD) {
       for(GameObject* obj : GameObjManager::instance()->getVec()){
            if(obj->getTag() == Tag::Block_Cloud1 && !obj->isExist()){
                obj->setExist(true);
            }
            if (obj->getTag() == Tag::Block_Cloud2 && !obj->isExist()) {
                obj->setExist(true);
            }
        }
        this->setUsingAlcohol(true);
        this->setAD(5);
        isInAlcoholCD = true;
        alcoholCD->restart();
        alcoholCD->resume();
		this->setIsUsedAlcohol(true);
    }
}

void Player::useArrow() {
    if (!isInArrowCD_) {
        arrowCD->restart();
        arrowCD->resume();
        isInArrowCD_ = true;

        // 根据Player面朝方向选择图集
        if (this->getIsFacingRight()) {
            this->getArrowAnimation()->setAtlas(ResourceManager::Instance().getAtlas(AtlasType::atlasArrowRight));
            this->setArrowSpeed(Vector2(1, 0));
        }
        else {
            this->getArrowAnimation()->setAtlas(ResourceManager::Instance().getAtlas(AtlasType::atlasArrowLeft));
            this->setArrowSpeed(Vector2(-1, 0));
        }
        this->getArrowAnimation()->reset();
        // 使存在
        this->setArrowBoxExist(true);
        // 调整位置
        if (this->getIsFacingRight()) {
            this->getArrowBox_block()->setBox(
                this->getBoxX() + this->getBoxWidth(),
                this->getBoxY() + this->getBoxHeight() * 0.2,
                this->getArrowBox_block()->getWidth(),
                this->getArrowBox_block()->getHeight()
            );
            this->getArrowBox_enemy()->setBox(
                this->getBoxX() + this->getBoxWidth(),
                this->getBoxY() + this->getBoxHeight() * 0.2,
                this->getArrowBox_enemy()->getWidth(),
                this->getArrowBox_enemy()->getHeight()
            );
        }
        else {
            this->getArrowBox_block()->setBox(
                this->getBoxX() - this->getArrowBox_block()->getWidth(),
                this->getBoxY() + this->getBoxHeight() * 0.2,
                this->getArrowBox_block()->getWidth(),
                this->getArrowBox_block()->getHeight()
            );
            this->getArrowBox_enemy()->setBox(
                this->getBoxX() - this->getArrowBox_enemy()->getWidth(),
                this->getBoxY() + this->getBoxHeight() * 0.2,
                this->getArrowBox_enemy()->getWidth(),
                this->getArrowBox_enemy()->getHeight()
            );
        }
        // 播放攻击音效
        Mix_PlayChannel(-1, ResourceManager::Instance().getSound(SoundType::arrow), 0);
    }
}

void Player::usePotion()
{
    if(this->getPotionCount() > 0 && this->getHP() < this->getMaxHP() && !isInPotionCD_) {
        potionCD->restart();
        potionCD->resume();
        this->setHP(this->getHP() + 1);
        if(this->getHP() > this->getMaxHP()){
            this->setHP(this->getMaxHP());
        }
        this->setPotionCount(this->getPotionCount() - 1);
		isInPotionCD_ = true;
	}
}

void Player::drawSkillcd(int x, int y, int width, int height, Timer* timer, SDL_Renderer* renderer)
{
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    float ratio = static_cast<float>(timer->getPassTime()) / timer->getWaitTime();
    int cdWidth = (int)(width * (1.0f - ratio));
    SDL_Rect cdRect = { x, y, cdWidth, height };
    SDL_SetRenderDrawColor(renderer, 128, 128, 128, 128);
    SDL_RenderFillRect(renderer, &cdRect);
}

void Player::drawPotionSkill(int x, int y, int width, int height, SDL_Renderer* renderer, Image* image)
{
    if (this->getPotionCount() == 0) {
        image = new Image("image\\potion_0.bmp");
    }
    else if (this->getPotionCount() == 1) {
        image = new Image("image\\potion_1.bmp");
    }
    else if (this->getPotionCount() == 2) {
        image = new Image("image\\potion_2.bmp");
    }
	else if (this->getPotionCount() == 3) {
        image = new Image("image\\potion_3.bmp");
    }
    SDL_Rect rect = { x, y, width, height };
    SDL_RenderCopy(renderer, image->getImgTexture(), nullptr, &rect);
	delete image;
}

void Player::drawSkill(int x, int y, int width, int height, SDL_Renderer* renderer, Image* image, const char* path)
{
    image = new Image(path);
    SDL_Rect rect = { x, y, width, height };
    SDL_RenderCopy(renderer, image->getImgTexture(), nullptr, &rect);
	delete image;
}

void Player::drawHP(int x, int y, int width, int height, SDL_Renderer* SDL_renderer, Image* image1, Image* image2, const char* path1, const char* path2)
{
	image1 = new Image(path1);
    image2 = new Image(path2);
    for(int i = 0; i < getMaxHP(); i++) {
        SDL_Rect rect = { x + i * (width + 5), y, width, height };
        SDL_RenderCopy(SDL_renderer, image1->getImgTexture(), nullptr, &rect);
	}
    for (int i = 0; i < getHP(); i++) {
        SDL_Rect rect = { x + i * (width + 5), y, width, height };
        SDL_RenderCopy(SDL_renderer, image2->getImgTexture(), nullptr, &rect);
    }
	delete image1;
	delete image2;
}

void Player::draw(SDL_Renderer* SDL_renderer) {
    GameObject::draw(SDL_renderer);
    /// 主角血条绘制
	this->drawHP(0, 0, 20, 20, SDL_renderer, BloodImage1, BloodImage2, "image\\blood_0.bmp", "image\\blood_1.bmp");
    // 剑气绘制
    SDL_Texture* swordTex = swordAnimation_->getFrameTexture();
    if(swordBox->canCollide()){
        SDL_Rect* rect = swordBox->getWindowRect(Panel::Instance().getCamera());
        SDL_RenderCopyEx(SDL_renderer, swordTex, nullptr, rect, 0, nullptr, swordAnimation_->getAtlas()->getFlip());
        delete rect;
    }
    // 弓箭绘制
    SDL_Texture* arrowTex = arrowAnimation_->getFrameTexture();
    if(arrowBox_enemy->canCollide()){
        SDL_Rect* rect = arrowBox_enemy->getWindowRect(Panel::Instance().getCamera());
        SDL_RenderCopyEx(SDL_renderer, arrowTex, nullptr, rect, 0, nullptr, arrowAnimation_->getAtlas()->getFlip());
        delete rect;
    }
    // 绘制技能
    if (hasAlcohol_) drawSkill(1055, 645, 75, 75, SDL_renderer, alcoholImage, "image\\Alcohol.bmp");
    if (hasArrow_) drawSkill(1130, 645, 75, 75, SDL_renderer, bowImage, "image\\bow.bmp");
	if (hasPotion) drawPotionSkill(1205, 645, 75, 75, SDL_renderer, potionImage);
    // 技能冷却
    if (isInAlcoholCD) drawSkillcd(1055, 645, 75, 75, alcoholCD, SDL_renderer);
    if (isInArrowCD_) drawSkillcd(1130, 645, 75, 75, arrowCD, SDL_renderer);
	if (isInPotionCD_) drawSkillcd(1205, 645, 75, 75, potionCD, SDL_renderer);
}

CollisionBox* Player::getCollisionBox() {
    if (collisionBox) {
        return collisionBox;
    }
    return nullptr;
}

CollisionBox* Player::getSwordBox() {
    if (swordBox) {
        return swordBox;
    }
    return nullptr;
}

CollisionBox* Player::getArrowBox_block() {
    if (arrowBox_block) {
        return arrowBox_block;
    }
    return nullptr;
}

CollisionBox* Player::getArrowBox_enemy() {
    if (arrowBox_enemy) {
        return arrowBox_enemy;
    }
    return nullptr;
}

void Player::setArrowBoxExist(bool isExist) {
    this->arrowBox_enemy->setCollidable(isExist);
    this->arrowBox_block->setCollidable(isExist);
}

void Player::setSwordBoxExist(bool isExist) {
    this->swordBox->setCollidable(isExist);
}

void Player::setArrowSpeed(Vector2 speed_) {
    this->arrowBox_enemy->speed = speed_;
    this->arrowBox_block->speed = speed_;
}

CollisionBox* Player::getHurtBox() {
    if (hurtBox) {
        return hurtBox;
    }
    return nullptr;
}
