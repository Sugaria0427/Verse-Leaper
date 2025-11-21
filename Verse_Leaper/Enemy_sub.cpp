#include "Enemy_sub.h"
#include "Panel.h"
#include "EnemyDogStates.h"
#include "EnemyEagleStates.h"
#include "EnemyTigerStates.h"
#include "BossStates.h"
#include "GameObjectManager.h"
#include "ResourceManager.h"

Dog::Dog(Tag _tag, Animation* _animation, Box* _EnemyBox) : Enemy(_tag, _animation, _EnemyBox) {
    initDog();
}

Dog::Dog(const Dog& dog) : Enemy(dog), chaseRange(dog.chaseRange) { 
    initDog(); 
}

void Dog::initDog()
{
    // 初始化chaseRange
    this->chaseRange = Box(this->getBoxCenterX() - chaseRange.getWidth() / 2,
        this->getBoxCenterY() - chaseRange.getHeight() / 2,
        1000, 500);
    this->setHP(3);
    this->setAD(1);
    /// 有限状态机
    {
        stateMachine = StateMachine();
        stateMachine.addStateNode("Patrol", new EnemyDogPatrolState(this));
        stateMachine.addStateNode("Chase", new EnemyDogChaseState(this));
        stateMachine.addStateNode("Goback", new EnemyDogGobakState(this));
        stateMachine.addStateNode("Dead", new EnemyDogDeadState(this));
        stateMachine.addStateNode("Hurt", new EnemyDogHurtState(this));
        stateMachine.setInitState("Patrol");
    }
}

void Dog::update(int delta) {
    if (isExist()) {
        Enemy::update(delta);
        // 更新追逐范围
        this->chaseRange.setBoxPosition(
            this->getBoxCenterX() - chaseRange.getWidth() / 2,
            this->getBoxCenterY() - chaseRange.getHeight() / 2
        );
    }
}

Eagle::Eagle(Tag _tag, Animation* _animation, Box* _EnemyBox) : Enemy(_tag, _animation, _EnemyBox) {
    initEagle();
}

Eagle::Eagle(const Eagle& Eagle) : Enemy(Eagle) { 
    initEagle(); 
}

void Eagle::initEagle()
{
    // 初始化patorlRange
    this->patrolRange = Box(this->getBoxCenterX() - patrolRange.getWidth() / 2,
        this->getBoxCenterY() - patrolRange.getHeight() / 2,
        2000, 2000);
    this->setHP(2);
    this->setAD(1);
    this->setGravity(0, 0); // 飞行敌人不受重力影响
    /// 有限状态机
    {
        stateMachine = StateMachine();
        stateMachine.addStateNode("Patrol", new EnemyEaglePatrolState(this));
        stateMachine.addStateNode("Dead", new EnemyEagleDeadState(this));
        stateMachine.addStateNode("Hurt", new EnemyEagleHurtState(this));
        stateMachine.setInitState("Patrol");
    }
}

void Eagle::update(int delta)
{
    if (isExist()) {
        Enemy::update(delta);
        // 更新巡逻范围
        this->patrolRange.setBoxPosition(
            this->getBoxCenterX() - patrolRange.getWidth() / 2,
            this->getBoxCenterY() - patrolRange.getHeight() / 2
        );
	}
}

Tiger::Tiger(Tag _tag, Animation* _animation, Box* _EnemyBox) : Enemy(_tag, _animation, _EnemyBox) {
    initTiger();
}

Tiger::Tiger(const Tiger& tiger)
    : Enemy(tiger), attackRange(tiger.attackRange), jumpRange(tiger.jumpRange) {
    initTiger();
}

void Tiger::initTiger()
{
    // 初始化攻击动画
    this->biteBoxAnimation = Animation(ResourceManager::Instance().getAtlas(AtlasType::atlasEnemyTigerBiteBoxRight), 300);
    // 设置攻击碰撞箱
    this->biteBox = CollisionManager::instance()->creatCollisionBox(this, 0, 0, 250, 250);
    this->biteBox->setLayerSrc(CollisionBox::Layer::Null);
    this->biteBox->setLayerDst(CollisionBox::Layer::Player);
    this->biteBox->setOnCollide(
        [this](CollisionBox* boxDst) {
            GameObjManager::instance()->getPlayer()->decreaseHP(2);
        }
    );
    this->biteBox->setCollidable(false);
    /// 基础属性
    {
        this->setHP(6);
        this->setAD(1);
        this->attackRange = Box(this->getBoxCenterX() - attackRange.getWidth() / 2,
            this->getBoxCenterY() - attackRange.getHeight() / 2,
            1200, 1000
        );
        this->jumpRange = Box(this->getBoxCenterX() - jumpRange.getWidth() / 2,
            this->getBoxCenterY() - jumpRange.getHeight() / 2,
            2700, 1000
        );
    }
    /// 有限状态机
    {
        stateMachine = StateMachine();
        stateMachine.addStateNode("Idle", new EnemyTigerIdleState(this));
        stateMachine.addStateNode("Attack", new EnemyTigerAttackState(this));
        stateMachine.addStateNode("Move", new EnemyTigerMoveState(this));
        stateMachine.addStateNode("Jump", new EnemyTigerJumpState(this));
        stateMachine.addStateNode("Dead", new EnemyTigerDeadState(this));
        stateMachine.setInitState("Idle");
    }
}

GameObject* Tiger::clone() {
    this->initEntityBox();
    this->initEnemy();
    this->initTiger();
    return this;
}

void Tiger::update(int delta) {
    if (isExist()) {
        this->biteBoxAnimation.updateIdxFrame(delta);
        Enemy::update(delta);
        // 更新攻击范围和跳跃范围
        this->attackRange.setBoxPosition(
            this->getBoxCenterX() - attackRange.getWidth() / 2,
            this->getBoxCenterY() - attackRange.getHeight() / 2
        );
        this->jumpRange.setBoxPosition(
            this->getBoxCenterX() - jumpRange.getWidth() / 2,
            this->getBoxCenterY() - jumpRange.getHeight() / 2
        );
    }
}

void Tiger::draw(SDL_Renderer* SDL_renderer) {
    Enemy::draw(SDL_renderer);
    //// 绘制跳跃范围（绿色）
    //SDL_SetRenderDrawColor(SDL_renderer, 0, 255, 0, 255);
    //SDL_Rect rect = SDL_Rect{
    //        (int)((attackRange.getX() - Panel::Instance().getCamera()->getX()) * Panel::Instance().getCamera()->getZoom()),
    //        (int)((attackRange.getY() - Panel::Instance().getCamera()->getY()) * Panel::Instance().getCamera()->getZoom()),
    //        (int)(attackRange.getWidth() * Panel::Instance().getCamera()->getZoom()),
    //        (int)(attackRange.getHeight() * Panel::Instance().getCamera()->getZoom())
    //};
    //SDL_RenderDrawRect(SDL_renderer, &rect);
    //// 绘制跳跃范围（蓝色）
    //SDL_SetRenderDrawColor(SDL_renderer, 0, 255, 0, 255);
    //rect = SDL_Rect{
    //        (int)((jumpRange.getX() - Panel::Instance().getCamera()->getX()) * Panel::Instance().getCamera()->getZoom()),
    //        (int)((jumpRange.getY() - Panel::Instance().getCamera()->getY()) * Panel::Instance().getCamera()->getZoom()),
    //        (int)(jumpRange.getWidth() * Panel::Instance().getCamera()->getZoom()),
    //        (int)(jumpRange.getHeight() * Panel::Instance().getCamera()->getZoom())
    //};
    //SDL_RenderDrawRect(SDL_renderer, &rect);
    // 绘制攻击
    SDL_Texture* swordTex = biteBoxAnimation.getFrameTexture();
    if (biteBox->canCollide()) {
        SDL_Rect* rect = biteBox->getWindowRect(Panel::Instance().getCamera());
        SDL_RenderCopyEx(SDL_renderer, swordTex, nullptr, rect, 0, nullptr, biteBoxAnimation.getAtlas()->getFlip());
        delete rect;
    }
}

Boss::Boss(Tag _tag, Animation* _animation, Box* _EnemyBox) : Enemy(_tag, _animation, _EnemyBox)
{
    initBoss();
}

Boss::Boss(const Boss& tiger) : Enemy(tiger)
{
    initBoss();
}

void Boss::initBoss()
{
    this->setGravity(0, 0); // Boss不受重力影响
    // 初始化攻击动画
    this->laserBoxAnimation = Animation(ResourceManager::Instance().getAtlas(AtlasType::atlasLaser), 500);
    this->barrageBoxAnimation = Animation(ResourceManager::Instance().getAtlas(AtlasType::atlasBarrage), 500);
    // 设置攻击碰撞箱
    this->laserBox = CollisionManager::instance()->creatCollisionBox(this, 0, 0, 500, 500);
    this->laserBox->setLayerSrc(CollisionBox::Layer::Null);
    this->laserBox->setLayerDst(CollisionBox::Layer::Player);
    this->laserBox->setOnCollide(
        [this](CollisionBox* boxDst) {
            GameObjManager::instance()->getPlayer()->decreaseHP(2);
        }
    );
    this->laserBox->setCollidable(false);
    // 设置弹幕碰撞箱
    barrageBoxes = { nullptr, nullptr, nullptr };
    for (CollisionBox*& barrage : barrageBoxes) {
        barrage = CollisionManager::instance()->creatCollisionBox(this, 0, 0, 200, 200);
        barrage->setLayerSrc(CollisionBox::Layer::Null);
        barrage->setLayerDst(CollisionBox::Layer::Player);
        barrage->setOnCollide(
            [this](CollisionBox* boxDst) {
                GameObjManager::instance()->getPlayer()->decreaseHP(1);
            }
        );
        barrage->setCollidable(false);
    }
    /// 基础属性
    this->setHP(2);
    this->setAD(1);
    this->laserRange = Box(this->getBoxCenterX() - laserRange.getWidth() / 2,
        this->getBoxCenterY() - this->getBoxHeight(),
        10000, 100
    );
    /// 有限状态机
    {
        stateMachine = StateMachine();
        stateMachine.addStateNode("Idle", new BossIdleState(this));
        stateMachine.addStateNode("Laser", new BossLaserState(this));
        stateMachine.addStateNode("Weak", new BossWeakState(this));
        stateMachine.addStateNode("Move", new BossMoveState(this));
        stateMachine.addStateNode("Barrage", new BossBarrageState(this));
        stateMachine.addStateNode("Dead", new BossDeadState(this));
        stateMachine.setInitState("Idle");
    }
}

GameObject* Boss::clone() {
    this->initEntityBox();
    this->initEnemy();
    this->initBoss();
    return this;
}

void Boss::update(int delta) {
    if (isExist()) {
        Enemy::update(delta);
        // 更新激光范围位置
        this->laserRange.setBoxPosition(
            this->getBoxCenterX() - laserRange.getWidth() / 2,
            this->getBoxCenterY() - this->getBoxHeight() / 3
        );
        // 更新激光位置
        if (laserBox->canCollide()) {
            this->laserBoxAnimation.updateIdxFrame(delta);
            this->laserBox->setBox(
                laserBox->getX() + laserBox->speed.getX() * delta,
                laserBox->getY() + laserBox->speed.getY() * delta,
                laserBox->getWidth(),
                laserBox->getHeight()
            );
        }
        // 更新弹幕位置
        for (CollisionBox*& barrage : barrageBoxes) {
            if (barrage->canCollide()) {
                this->barrageBoxAnimation.updateIdxFrame(delta);
                barrage->setBox(
                    barrage->getX() + barrage->speed.getX() * delta,
                    barrage->getY() + barrage->speed.getY() * delta,
                    barrage->getWidth(),
                    barrage->getHeight()
                );
            }
        }

    }
}

void Boss::draw(SDL_Renderer* SDL_renderer) {
    Enemy::draw(SDL_renderer);
    //// 绘制激光范围（绿色）
    //SDL_SetRenderDrawColor(SDL_renderer, 0, 255, 0, 255);
    //SDL_Rect rect = SDL_Rect{
    //    (int)((laserRange.getX() - Panel::Instance().getCamera()->getX()) * Panel::Instance().getCamera()->getZoom()),
    //    (int)((laserRange.getY() - Panel::Instance().getCamera()->getY()) * Panel::Instance().getCamera()->getZoom()),
    //    (int)(laserRange.getWidth() * Panel::Instance().getCamera()->getZoom()),
    //    (int)(laserRange.getHeight() * Panel::Instance().getCamera()->getZoom())
    //};
    //SDL_RenderDrawRect(SDL_renderer, &rect);
    // 绘制激光
    SDL_Texture* laserTex = laserBoxAnimation.getFrameTexture();
    if (laserBox->canCollide()) {
        SDL_Rect* rect = laserBox->getWindowRect(Panel::Instance().getCamera());
        SDL_RenderCopyEx(SDL_renderer, laserTex, nullptr, rect, 0, nullptr, laserBoxAnimation.getAtlas()->getFlip());
        delete rect;
    }
    // 绘制弹幕
    SDL_Texture* barrageTex = barrageBoxAnimation.getFrameTexture();
    for (CollisionBox*& barrage : barrageBoxes) {
        SDL_Texture* rect = barrageBoxAnimation.getFrameTexture();
        if (barrage->canCollide()) {
            SDL_Rect* rect = barrage->getWindowRect(Panel::Instance().getCamera());
            SDL_RenderCopyEx(SDL_renderer, barrageTex, nullptr, rect, 0, nullptr, barrageBoxAnimation.getAtlas()->getFlip());
            delete rect;
        }
    }

}
