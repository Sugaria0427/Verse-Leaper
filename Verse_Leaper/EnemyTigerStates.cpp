#include "EnemyTigerStates.h"
#include "GameObjectManager.h"
#include "ResourceManager.h"
#include "GameObjFactory.h"
#include "GameObject.h"
#include "Enemy_sub.h"
#include "Player.h"


EnemyTigerIdleState::EnemyTigerIdleState(GameObject* owner) : StateNode(owner) {
    this->idleTimer_ = Timer();
    this->idleTimer_.setWaitTime(1000);
}

void EnemyTigerIdleState::onEnter() {
    // 重置idle计时器
    this->idleTimer_.restart();
    // 设置图集朝向主角
    if (GameObjManager::instance()->getPlayer()) {
        double playerX = GameObjManager::instance()->getPlayer()->getBoxCenterX();
        if (this->getOwner()->getBoxCenterX() >= playerX) {
            this->getOwner()->setAtlas(ResourceManager::Instance().getAtlas(AtlasType::atlasEnemyTigerIdleLeft));
        }
        else {
            this->getOwner()->setAtlas(ResourceManager::Instance().getAtlas(AtlasType::atlasEnemyTigerIdleRight));
        }
    }
    else this->getOwner()->setAtlas(ResourceManager::Instance().getAtlas(AtlasType::atlasEnemyTigerIdleLeft));
    // 设置速度为0
    this->getOwner()->setSpeed(0, 0);
}

void EnemyTigerIdleState::update(int delta) {
    // 更新计时器
    this->idleTimer_.update(delta);
    // 检查状态切换
    Tiger* tiger = dynamic_cast<Tiger*>(this->getOwner());
    Player* player = dynamic_cast<Player*>(GameObjManager::instance()->getPlayer());
    if (tiger->IsDead()) 
        tiger->setState("Dead");
    else if (this->idleTimer_.isShotted()) 
    {
        if (tiger->getAttackRange().isPointOn(player->getBoxCenterX(), player->getBoxCenterY())) 
            tiger->setState("Attack");
        else if (tiger->getJumpRange().isPointOn(player->getBoxCenterX(), player->getBoxCenterY())) 
            tiger->setState("Jump");
    }
}

void EnemyTigerIdleState::onExit() {}

EnemyTigerAttackState::EnemyTigerAttackState(GameObject* owner) : StateNode(owner) {
    this->attackStartup_ = Timer();
    this->attackStartup_.setWaitTime(1000);
    this->attackTimer_ = Timer();
    this->attackTimer_.setWaitTime(2000);
}

void EnemyTigerAttackState::onEnter() {
    Tiger* tiger = dynamic_cast<Tiger*>(this->getOwner());
    // 重置attack计时器
    this->attackStartup_.restart();
    this->attackTimer_.restart();

    // 设置攻击朝向主角
    double playerX = GameObjManager::instance()->getPlayer()->getBoxCenterX();
    if (tiger->getBoxCenterX() >= playerX) {
        // 设置图集
        tiger->setAtlas(ResourceManager::Instance().getAtlas(AtlasType::atlasEnemyTigerAttackLeft));
        // 设置咬击碰撞箱位置
        tiger->getBiteBox()->setBoxPosition(
            tiger->getBoxX() - tiger->getBiteBox()->getWidth() * 0.7, 
            tiger->getBoxY() + tiger->getBiteBox()->getHeight() * 0.5
        );
    }
    else {
        tiger->setAtlas(ResourceManager::Instance().getAtlas(AtlasType::atlasEnemyTigerAttackRight));
        tiger->getBiteBox()->setBoxPosition(
            tiger->getBoxX() + tiger->getBoxWidth() * 0.9,
            tiger->getBoxY() + tiger->getBoxHeight() * 0.5
        );
    }
    // 设置速度为0
    tiger->setSpeed(0, 0);
}

void EnemyTigerAttackState::update(int delta) {
    // 更新计时器
    this->attackStartup_.update(delta);
    this->attackTimer_.update(delta);
    // 检查攻击前摇结束
    Tiger* tiger = dynamic_cast<Tiger*>(this->getOwner());
    if (this->attackStartup_.isShotted()) {
        tiger->getBiteBox()->setCollidable(true);   // 攻击前摇结束后开启咬击碰撞箱
        // 播放攻击音效
        if (!isPlayedAttack) {
            tigerAttackChannel = Mix_PlayChannel(-1, ResourceManager::Instance().getSound(SoundType::tigerAttack), 0);
            isPlayedAttack = true;
        }
    }
    // 检查状态切换
    if (tiger->IsDead()) 
        tiger->setState("Dead");
    else if (this->attackTimer_.isShotted())
        tiger->setState("Move");    // 攻击结束后切换回Move状态
}

void EnemyTigerAttackState::onExit() {
    Tiger* tiger = dynamic_cast<Tiger*>(this->getOwner());
    tiger->getBiteBox()->setCollidable(false);      // 退出攻击状态时关闭咬击碰撞箱
	isPlayedAttack = false;
	Mix_HaltChannel(tigerAttackChannel);
}

EnemyTigerMoveState::EnemyTigerMoveState(GameObject* owner) : StateNode(owner)
{
    moveTimer_ = Timer();
    moveTimer_.setWaitTime(1000);
}

void EnemyTigerMoveState::onEnter() {
    moveTimer_.restart();
    Tiger* tiger = dynamic_cast<Tiger*>(this->getOwner());
    Player* player = dynamic_cast<Player*>(GameObjManager::instance()->getPlayer());
    if (!tiger->getAttackRange().isPointOn(player->getBoxCenterX(), player->getBoxCenterY())) {
        if (tiger->getBoxCenterX() >= player->getBoxCenterX()) {
            tiger->setAtlas(ResourceManager::Instance().getAtlas(AtlasType::atlasEnemyTigerMoveLeft));
            tiger->setSpeedX(-1);
        }
        else {
            tiger->setAtlas(ResourceManager::Instance().getAtlas(AtlasType::atlasEnemyTigerMoveRight));
            tiger->setSpeedX(1);
        }
    }
    else {
        if (tiger->getBoxCenterX() >= player->getBoxCenterX()) {
            tiger->setAtlas(ResourceManager::Instance().getAtlas(AtlasType::atlasEnemyTigerRetreatLeft));
            tiger->setSpeedX(1);
        }
        else {
            tiger->setAtlas(ResourceManager::Instance().getAtlas(AtlasType::atlasEnemyTigerRetreatRight));
            tiger->setSpeedX(-1);
        }
    }
	// 播放奔跑音效
	tigerRunChannel = Mix_PlayChannel(-1, ResourceManager::Instance().getSound(SoundType::tigerRun), -1);
}

void EnemyTigerMoveState::update(int delta) {
    moveTimer_.update(delta);
    if(moveTimer_.isShotted()) {
        Tiger* tiger = dynamic_cast<Tiger*>(this->getOwner());
        tiger->setState("Idle");    // 移动结束后切换回Idle状态
    }
}

void EnemyTigerMoveState::onExit() {
	Mix_HaltChannel(tigerRunChannel);
}

EnemyTigerJumpState::EnemyTigerJumpState(GameObject* owner) : StateNode(owner) {
}

void EnemyTigerJumpState::onEnter() {
    Tiger* tiger = dynamic_cast<Tiger*>(this->getOwner());
    Player* player = dynamic_cast<Player*>(GameObjManager::instance()->getPlayer());
    // 设置跳跃朝向主角
    if (tiger->getBoxCenterX() >= player->getBoxCenterX()) {
        tiger->setAtlas(ResourceManager::Instance().getAtlas(AtlasType::atlasEnemyTigerJumpLeft));
        tiger->setSpeedX(-2.5);
    }
    else {
        tiger->setAtlas(ResourceManager::Instance().getAtlas(AtlasType::atlasEnemyTigerJumpRight));
        tiger->setSpeedX(2.5);
    }
    tiger->setSpeedY(-30); // 设置初始跳跃速度
	// 播放跳跃音效
	tigerJumpChannel = Mix_PlayChannel(-1, ResourceManager::Instance().getSound(SoundType::tigerJump), 0);
}

void EnemyTigerJumpState::update(int delta) {
    Tiger* tiger = dynamic_cast<Tiger*>(this->getOwner());
    if (tiger->isOnFloor())
        tiger->setState("Attack");  // 落地后切换到Attack状态
}

void EnemyTigerJumpState::onExit() {
	Mix_HaltChannel(tigerJumpChannel);
}

EnemyTigerDeadState::EnemyTigerDeadState(GameObject* owner) : StateNode(owner) {}

void EnemyTigerDeadState::onEnter() {
    Tiger* tiger = dynamic_cast<Tiger*>(this->getOwner());
    Mix_PlayChannel(-1, ResourceManager::Instance().getSound(SoundType::die), 0);
    tiger->setSpeed(0, 0);
    tiger->setAtlas(ResourceManager::Instance().getAtlas(AtlasType::atlasEnemyTigerDead));
}
void EnemyTigerDeadState::update(int delta) {
    Tiger* enemy = dynamic_cast<Tiger*>(this->getOwner());
    DropItem* dropItem = nullptr;
    if (enemy->willDrop()) {
        // 产生掉落物
        dropItem = GameObjFactory::instance()->createDropItem(Tag::DropItem_Alcohol, enemy->getBoxX(), enemy->getBoxY());
        dropItem->drop(enemy->getBoxX(), enemy->getBoxY());
        GameObjManager::instance()->addGameObj(dropItem);
        enemy->setWillDrop(false);
        enemy->setExist(false);
    }
}
void EnemyTigerDeadState::onExit() {
}