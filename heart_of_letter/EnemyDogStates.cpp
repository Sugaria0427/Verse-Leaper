#include "EnemyDogStates.h"
#include "GameObjFactory.h"
#include "Enemy_sub.h"
#include "Box.h"
#include "ResourceManager.h"

EnemyDogPatrolState::EnemyDogPatrolState(GameObject* owner) : StateNode(owner)
{
    this->patrolTimer_ = Timer();
    this->patrolTimer_.setWaitTime(2000);
    this->patrolTimer_.setOneShot(false);
    this->patrolTimer_.setCallback(
        [this]() {
            if (this->isMoveRight_) 
                this->getOwner()->setSpeedX(-0.5);
            else 
                this->getOwner()->setSpeedX(0.5);
            this->isMoveRight_ = !this->isMoveRight_;
        }
    );
}
void EnemyDogPatrolState::onEnter() {
    Enemy* enemy = dynamic_cast<Enemy*>(this->getOwner());
    this->patrolTimer_.restart();
    this->isMoveRight_ = false;
    this->getOwner()->setSpeedX(-0.5);
    if (this->getOwner()->getSpeed().getX() >= 0)
        this->getOwner()->setAtlas(ResourceManager::Instance().getAtlas(AtlasType::atlasEnemyDogRunRight));
    else
        this->getOwner()->setAtlas(ResourceManager::Instance().getAtlas(AtlasType::atlasEnemyDogRunLeft));
    if (enemy->getInitPosition().getX() != enemy->getBoxX())
        enemy->setState("Goback");  // 如果不在初始位置，切换到回归状态
}
void EnemyDogPatrolState::update(int delta) {
    EnemyDog* dog = dynamic_cast<EnemyDog*>(this->getOwner());
    Player* player = dynamic_cast<Player*>(GameObjManager::instance()->getPlayer());
    if (dog->getInvincible()) {
        dog->setState("Hurt");
        return;
    }
    else if (dog->getChaseRange().isPointOn(player->getBoxCenterX(), player->getBoxCenterY())) {
        dog->setState("Chase");
        return;
    }
    this->patrolTimer_.update(delta);
    if (this->getOwner()->getSpeed().getX() >= 0)
        this->getOwner()->setAtlas(ResourceManager::Instance().getAtlas(AtlasType::atlasEnemyDogRunRight));
    else
        this->getOwner()->setAtlas(ResourceManager::Instance().getAtlas(AtlasType::atlasEnemyDogRunLeft));
}
void EnemyDogPatrolState::onExit() {}

EnemyDogHurtState::EnemyDogHurtState(GameObject* owner) : StateNode(owner) {
    this->hurtTimer = new Timer();
    this->hurtTimer->setWaitTime(500);
}
void EnemyDogHurtState::onEnter() {
    this->hurtTimer->restart();
    if (GameObjManager::instance()->getPlayer()->getBoxCenterX() < this->getOwner()->getBoxCenterX()) {
        this->getOwner()->setSpeedX(1);
    }
    else {
        this->getOwner()->setSpeedX(-1);
    }
}
void EnemyDogHurtState::update(int delta) {
    this->hurtTimer->update(delta);
    Enemy* enemy = dynamic_cast<Enemy*>(this->getOwner());
    if (this->getOwner()->IsDead()) {
        enemy->setState("Dead");
        return;
    }
    else if (this->hurtTimer->isShotted()) {
        enemy->setState("Patrol");
        return;
    }
}
void EnemyDogHurtState::onExit() {}

EnemyDogDeadState::EnemyDogDeadState(GameObject* owner) : StateNode(owner) {}
void EnemyDogDeadState::onEnter() {
    Enemy* enemy = dynamic_cast<Enemy*>(this->getOwner());
    dieChannel = Mix_PlayChannel(-1, ResourceManager::Instance().getSound(SoundType::die), 0);
    enemy->setSpeed(0, 0);
    enemy->setAtlas(ResourceManager::Instance().getAtlas(AtlasType::atlasEnemyDogDead));
}
void EnemyDogDeadState::update(int delta) {
    Enemy* enemy = dynamic_cast<Enemy*>(this->getOwner());
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
void EnemyDogDeadState::onExit() {
    Mix_HaltChannel(dieChannel);
}

EnemyDogGobakState::EnemyDogGobakState(GameObject* owner) : StateNode(owner) {}
void EnemyDogGobakState::onEnter() {
    Enemy* enemy = dynamic_cast<Enemy*>(this->getOwner());
    if (this->getOwner()->getSpeed().getX() >= 0)
        this->getOwner()->setAtlas(ResourceManager::Instance().getAtlas(AtlasType::atlasEnemyDogRunRight));
    else
        this->getOwner()->setAtlas(ResourceManager::Instance().getAtlas(AtlasType::atlasEnemyDogRunLeft));
    dogGobackChannel = Mix_PlayChannel(-1, ResourceManager::Instance().getSound(SoundType::dogGoback), 0);
}
void EnemyDogGobakState::update(int delta) {
    Enemy* enemy = dynamic_cast<Enemy*>(this->getOwner());
    if (enemy->getInvincible()) {
        enemy->setState("Hurt");
        return;
    }

    // 获取初始位置和当前位置
    float initX = enemy->getInitPosition().getX();
    float currentX = enemy->getBoxX();
    // 误差阈值（根据游戏单位调整，例如1.0f）
    const float threshold = 10.0f;

    if (currentX > initX + threshold) {
        // 当前位置在初始位置右侧，且超出阈值，向左移动
        enemy->setSpeedX(-1);
    }
    else if (currentX < initX - threshold) {
        // 当前位置在初始位置左侧，且超出阈值，向右移动
        enemy->setSpeedX(1);
    }
    else {
        // 在阈值范围内，认为已到达，停止移动并切换到巡逻状态
        enemy->setSpeedX(0);  // 确保停止移动
        enemy->setState("Patrol");
        return;
    }

    // 切换动画图集（保持不变）
    if (this->getOwner()->getSpeed().getX() >= 0)
        this->getOwner()->setAtlas(ResourceManager::Instance().getAtlas(AtlasType::atlasEnemyDogRunRight));
    else
        this->getOwner()->setAtlas(ResourceManager::Instance().getAtlas(AtlasType::atlasEnemyDogRunLeft));
}
void EnemyDogGobakState::onExit() {
	Mix_HaltChannel(dogGobackChannel);
}

void EnemyDogChaseState::onEnter() {
    EnemyDog* dog = dynamic_cast<EnemyDog*>(this->getOwner());
    dog->getChaseRange().setBoxPosition(dog->getBoxCenterX() - dog->getChaseRange().getWidth() / 2,
        dog->getBoxCenterY() - dog->getChaseRange().getHeight() / 2);
	dogRunChannel = Mix_PlayChannel(-1, ResourceManager::Instance().getSound(SoundType::dogRun), 0);
	dogChaseChannel = Mix_PlayChannel(-1, ResourceManager::Instance().getSound(SoundType::dogChase), 0);
}
void EnemyDogChaseState::update(int delta) {
    // 获取敌人和玩家对象
    EnemyDog* dog = dynamic_cast<EnemyDog*>(this->getOwner());
    Player* player = dynamic_cast<Player*>(GameObjManager::instance()->getPlayer());
    // 更新追逐范围
    dog->getChaseRange().setBoxPosition(dog->getBoxCenterX() - dog->getChaseRange().getWidth() / 2,
        dog->getBoxCenterY() - dog->getChaseRange().getHeight() / 2);
    if (dog->getInvincible()) {
        dog->setState("Hurt");    // 切换到受伤状态
        return;
    }
    else if (!dog->getChaseRange().isPointOn(player->getBoxCenterX(), player->getBoxCenterY())) {
        dog->setState("Goback");  // 超出追逐范围，切换到回归状态
        return;
    }
    // 追逐玩家
    if (player->getBoxCenterX() > dog->getBoxCenterX())
        dog->setSpeedX(0.2);
    else if (player->getBoxCenterX() < dog->getBoxCenterX())
        dog->setSpeedX(-0.2);
    else dog->setSpeedX(0);
    // 设置动画图集
    if (this->getOwner()->getSpeed().getX() >= 0)
        this->getOwner()->setAtlas(ResourceManager::Instance().getAtlas(AtlasType::atlasEnemyDogRunRight));
    else
        this->getOwner()->setAtlas(ResourceManager::Instance().getAtlas(AtlasType::atlasEnemyDogRunLeft));
}
void EnemyDogChaseState::onExit() {
    Mix_HaltChannel(dogRunChannel);
	Mix_HaltChannel(dogChaseChannel);
}