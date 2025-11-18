#include "BossStates.h"
#include "GameObject.h"
#include "GameObjectManager.h"
#include "ResourceManager.h"
#include "Enemy_sub.h"
#include "Player.h"

int random_int(int min, int max) {
    return rand() % (max - min + 1) + min;
}

BossIdleState::BossIdleState(GameObject* owner) : StateNode(owner)
{
    this->idleTimer_ = Timer();
    this->idleTimer_.setWaitTime(1000);
}

void BossIdleState::onEnter() {
    // 重置idle计时器
    this->idleTimer_.restart();
    // 设置图集
    this->getOwner()->setAtlas(ResourceManager::Instance().getAtlas(AtlasType::atlasEnemyBossIdle));
    // 设置速度为0
    this->getOwner()->setSpeed(0, 0);
}

void BossIdleState::update(int delta) {
    this->idleTimer_.update(delta);
    EnemyBoss* boss = dynamic_cast<EnemyBoss*>(this->getOwner());
    Player* player = dynamic_cast<Player*>(GameObjManager::instance()->getPlayer());
    if (this->idleTimer_.isShotted()) {
        if (boss->getLaserRange().isPointOn(player->getBoxCenterX(), player->getBoxCenterY())) {
            // 闲置时间到且玩家在激光范围内，切换到激光攻击状态
            boss->setState("Laser");
        }
        else {
            int randomNum = random_int(1, 2);
            switch(randomNum) {
                case 1:
                    // 闲置时间到且玩家不在激光范围内，切换到弹幕攻击状态
                    boss->setState("Barrage");
                    break;
                case 2:
                    // 闲置时间到且玩家不在激光范围内，切换到移动状态
                    boss->setState("Move");
                    break;
            }
        }
    }
}

void BossIdleState::onExit() {}

BossLaserState::BossLaserState(GameObject* owner) : StateNode(owner)
{
    this->laserTimer_ = Timer();
    this->laserTimer_.setWaitTime(2800);
    this->laserStartupTimer_ = Timer();
    this->laserStartupTimer_.setWaitTime(1000);
}

void BossLaserState::onEnter() {
    EnemyBoss* boss = dynamic_cast<EnemyBoss*>(this->getOwner());
    // 重置计时器
    this->laserTimer_.restart();
    this->laserStartupTimer_.restart();
    // 设置图集
    boss->setAtlas(ResourceManager::Instance().getAtlas(AtlasType::atlasEnemyBossLaser));
    // 设置速度为0
    boss->setSpeed(0, 0);
    // 发射激光
    boss->getLaserBox()->speed = Vector2(-2, 0);    // 激光向左移动
    boss->getLaserBox()->setBoxPosition(boss->getBoxX(), boss->getBoxY());
    boss->getLaserBox()->setCollidable(false);  // 激光等前摇结束后发射
}

void BossLaserState::update(int delta) {
    EnemyBoss* boss = dynamic_cast<EnemyBoss*>(this->getOwner());
    this->laserTimer_.update(delta);
    this->laserStartupTimer_.update(delta);
    if (laserStartupTimer_.isShotted()) {
        boss->getLaserBox()->setCollidable(true);   // 前摇结束，激光发射
        if(willFireLaser) {
            // 播放激光发射音效
            bossLasserChannel = Mix_PlayChannel(-1, ResourceManager::Instance().getSound(SoundType::bossLasser), 0);
            bossFireChannel = Mix_PlayChannel(-1, ResourceManager::Instance().getSound(SoundType::bossFire), 0);
            willFireLaser = false;
		}
    }
    if (this->laserTimer_.isShotted()) {
        // 激光攻击时间到，切换到虚弱状态
        EnemyBoss* boss = dynamic_cast<EnemyBoss*>(this->getOwner());
        boss->setState("Weak");
    }
}

void BossLaserState::onExit() {
    // 关闭激光
    EnemyBoss* boss = dynamic_cast<EnemyBoss*>(this->getOwner());
    boss->getLaserBox()->setCollidable(false);
	willFireLaser = true;
	// 停止激光音效
	Mix_HaltChannel(bossLasserChannel);
	Mix_HaltChannel(bossFireChannel);
}

BossWeakState::BossWeakState(GameObject* owner) : StateNode(owner)
{
    this->weakTimer_ = Timer();
    this->weakTimer_.setWaitTime(2000);
}

void BossWeakState::onEnter() {
    EnemyBoss* boss = dynamic_cast<EnemyBoss*>(this->getOwner());
    // 重置计时器
    this->weakTimer_.restart();
    // 设置图集
    boss->setAtlas(ResourceManager::Instance().getAtlas(AtlasType::atlasEnemyBossWeak));
    // 设置速度为0
    boss->setSpeed(0, 0);
	// 播放虚弱音效
	bossWeakChannel = Mix_PlayChannel(-1, ResourceManager::Instance().getSound(SoundType::bossWeak), 0);
}

void BossWeakState::update(int delta) {
    weakTimer_.update(delta);
    if(weakTimer_.isShotted()) {
        // 虚弱状态时间到，切换到移动状态
        EnemyBoss* boss = dynamic_cast<EnemyBoss*>(this->getOwner());
        boss->setState("Move");
    }
}

void BossWeakState::onExit() {
	// 停止播放
	Mix_HaltChannel(bossWeakChannel);
}

BossMoveState::BossMoveState(GameObject* owner) : StateNode(owner)
{
    this->moveTimer_ = Timer();
    this->moveTimer_.setWaitTime(2000);
}

void BossMoveState::onEnter() {
    EnemyBoss* boss = dynamic_cast<EnemyBoss*>(this->getOwner());
    Player* player = dynamic_cast<Player*>(GameObjManager::instance()->getPlayer());
    // 重置计时器
    this->moveTimer_.restart();
    // 设置图集
    boss->setAtlas(ResourceManager::Instance().getAtlas(AtlasType::atlasEnemyBossIdle));
    // 设置速度
    if(player->getBoxCenterY() > boss->getBoxCenterY() - boss->getBoxHeight() / 4)
        boss->setSpeed(0, 8);   // 玩家在boss下方，向下移动
    else
        boss->setSpeed(0, -8);  // 玩家在boss上方，向上移动
	// 播放移动音效
	bossMoveChannel = Mix_PlayChannel(-1, ResourceManager::Instance().getSound(SoundType::bossMove), 0);
}

void BossMoveState::update(int delta) {
    // 更新计时器
    this->moveTimer_.update(delta);
    // 检查是否到达目标位置或时间到
    EnemyBoss* boss = dynamic_cast<EnemyBoss*>(this->getOwner());
    Player* player = dynamic_cast<Player*>(GameObjManager::instance()->getPlayer());
    if (this->moveTimer_.isShotted() || boss->getLaserRange().isPointOn(player->getBoxCenterX(), player->getBoxCenterY())) {
        // 移动状态时间到，切换回闲置状态
        EnemyBoss* boss = dynamic_cast<EnemyBoss*>(this->getOwner());
        boss->setState("Idle");
    }
}

void BossMoveState::onExit() {
    Mix_HaltChannel(bossMoveChannel); 
}

BossBarrageState::BossBarrageState(GameObject* owner) : StateNode(owner)
{
    this->barrageTimer_ = Timer();
    this->barrageTimer_.setWaitTime(2800);
    this->barrageStartupTimer_ = Timer();
    this->barrageStartupTimer_.setWaitTime(1000);
}

void BossBarrageState::onEnter() {
    EnemyBoss* boss = dynamic_cast<EnemyBoss*>(this->getOwner());
    // 重置计时器
    this->barrageTimer_.restart();
    this->barrageStartupTimer_.restart();
    // 设置图集
    boss->setAtlas(ResourceManager::Instance().getAtlas(AtlasType::atlasEnemyBossBarrage));
    // 设置速度为0
    boss->setSpeed(0, 0);
    // 发射弹幕攻击
    for (CollisionBox* box : boss->getBarrageBoxes()) {
        box->speed = Vector2(-2, 0);    // 激光向左移动
        box->setBoxPosition(boss->getBoxX(), random_int(5, 20) * 150);   // 随机高度发射弹幕
        box->setCollidable(false);  // 激光等前摇结束后发射
    }
}

void BossBarrageState::update(int delta) {
    EnemyBoss* boss = dynamic_cast<EnemyBoss*>(this->getOwner());
    this->barrageTimer_.update(delta);
    this->barrageStartupTimer_.update(delta);
    if (barrageStartupTimer_.isShotted()) {
        for (CollisionBox*& box : boss->getBarrageBoxes()) {
            box->setCollidable(true);   // 前摇结束，弹幕发射
        }
		// 播放弹幕音效
        if(willFireBarrage) {
            bossBarrageChannel = Mix_PlayChannel(-1, ResourceManager::Instance().getSound(SoundType::bossBarrage), 0);
		    willFireBarrage = false;
        }
	}
    if (this->barrageTimer_.isShotted()) {
        // 激光攻击时间到，切换到虚弱状态
        EnemyBoss* boss = dynamic_cast<EnemyBoss*>(this->getOwner());
        boss->setState("Weak");
    }
}

void BossBarrageState::onExit() {
    EnemyBoss* boss = dynamic_cast<EnemyBoss*>(this->getOwner());
    for (CollisionBox* box : boss->getBarrageBoxes()) {
        box->setCollidable(false);   // 关闭弹幕
    }
	willFireBarrage = true;
	Mix_HaltChannel(bossBarrageChannel);
}
