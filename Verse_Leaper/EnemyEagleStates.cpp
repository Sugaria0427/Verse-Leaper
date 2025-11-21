#include "EnemyEagleStates.h"
#include "GameObjFactory.h"
#include "Enemy_sub.h"
#include "ResourceManager.h"
#include "GameObjectManager.h"

EnemyEaglePatrolState::EnemyEaglePatrolState(GameObject* owner) : StateNode(owner)
{
    this->patrolTimer_ = Timer();
    this->patrolTimer_.setWaitTime(2000);
    this->patrolTimer_.setOneShot(false);
    this->patrolTimer_.setCallback(
        [this]() {
            if (this->isMoveRight_) {
                this->getOwner()->setSpeedX(-0.5);
                this->isMoveRight_ = false;
            }
            else {
                this->getOwner()->setSpeedX(0.5);
                this->isMoveRight_ = true;
            }
        }
    );
}
void EnemyEaglePatrolState::onEnter() {
    Eagle* eagle = dynamic_cast<Eagle*>(this->getOwner());
	Player* player = dynamic_cast<Player*>(GameObjManager::instance()->getPlayer());
    this->patrolTimer_.restart();
    this->isMoveRight_ = false;
    this->getOwner()->setSpeedX(-0.5);
    if (this->getOwner()->getSpeed().getX() >= 0)
        this->getOwner()->setAtlas(ResourceManager::Instance().getAtlas(AtlasType::atlasEnemyEagleFlyRight));
    else
        this->getOwner()->setAtlas(ResourceManager::Instance().getAtlas(AtlasType::atlasEnemyEagleFlyLeft));
}
void EnemyEaglePatrolState::update(int delta) {
    Eagle* eagle = dynamic_cast<Eagle*>(this->getOwner());
    Player* player = dynamic_cast<Player*>(GameObjManager::instance()->getPlayer());
    if (player && eagle->getPatrolRange().isPointOn(player->getBoxCenterX(), player->getBoxCenterY()) && !isPlayedFly) {
        eagleFlyChannel = Mix_PlayChannel(-1, ResourceManager::Instance().getSound(SoundType::eagleFly), -1);
        isPlayedFly=true;
    }
    else if(player && !eagle->getPatrolRange().isPointOn(player->getBoxCenterX(), player->getBoxCenterY())) {
        if(eagleFlyChannel != -1)
		    Mix_HaltChannel(eagleFlyChannel);
		isPlayedFly = false;
    }
    if (eagle->getInvincible()) {
        eagle->setState("Hurt");
        return;
    }
    this->patrolTimer_.update(delta);
    if (this->getOwner()->getSpeed().getX() >= 0)
        this->getOwner()->setAtlas(ResourceManager::Instance().getAtlas(AtlasType::atlasEnemyEagleFlyRight));
    else
        this->getOwner()->setAtlas(ResourceManager::Instance().getAtlas(AtlasType::atlasEnemyEagleFlyLeft));
}
void EnemyEaglePatrolState::onExit() {
	Mix_HaltChannel(eagleFlyChannel);
    isPlayedFly = false;
}

EnemyEagleHurtState::EnemyEagleHurtState(GameObject* owner) : StateNode(owner) {
    this->hurtTimer = new Timer();
    this->hurtTimer->setWaitTime(500);
}
void EnemyEagleHurtState::onEnter() {
    hurtTimer->restart();   // 重置受击计时器
    if (GameObjManager::instance()->getPlayer()->getBoxCenterX() < this->getOwner()->getBoxCenterX()) {
        this->getOwner()->setSpeedX(1);
    }
    else {
        this->getOwner()->setSpeedX(-1);
    }
	eagleHawkChannel = Mix_PlayChannel(-1, ResourceManager::Instance().getSound(SoundType::eagleHawk), 0);
}
void EnemyEagleHurtState::update(int delta) {
    this->hurtTimer->update(delta);
    Eagle* eagle = dynamic_cast<Eagle*>(this->getOwner());
    if (this->getOwner()->IsDead()) {
        eagle->setState("Dead");
        return;
    }
    else if (hurtTimer->isShotted()) {
        eagle->setState("Patrol");
        return;
    }
}
void EnemyEagleHurtState::onExit() {
	Mix_HaltChannel(eagleHawkChannel);
}

EnemyEagleDeadState::EnemyEagleDeadState(GameObject* owner) : StateNode(owner) {}
void EnemyEagleDeadState::onEnter() {
    Eagle* eagle = dynamic_cast<Eagle*>(this->getOwner());
    dieChannel = Mix_PlayChannel(-1, ResourceManager::Instance().getSound(SoundType::die), 0);
    eagle->setSpeed(0, 0);
    eagle->setAtlas(ResourceManager::Instance().getAtlas(AtlasType::atlasEnemyEagleDead));
}
void EnemyEagleDeadState::update(int delta) {
    Eagle* enemy = dynamic_cast<Eagle*>(this->getOwner());
    DropItem* dropItem = nullptr;
    if (enemy->willDrop()) {
        // 产生掉落物
        dropItem = GameObjFactory::instance()->createDropItem(Tag::DropItem_Potion, enemy->getBoxX(), enemy->getBoxY());
        dropItem->drop(enemy->getBoxX(), enemy->getBoxY());
        GameObjManager::instance()->addGameObj(dropItem);
        enemy->setWillDrop(false);
        enemy->setExist(false);
    }
}
void EnemyEagleDeadState::onExit() {
	Mix_HaltChannel(dieChannel);
}
