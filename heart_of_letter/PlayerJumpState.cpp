#include "PlayerJumpState.h"
#include "Player.h"
#include "ResourceManager.h"

void PlayerJumpState::onEnter() {
    Player* player = dynamic_cast<Player*>(this->getOwner());
    player->setWillJump(false);
    player->jump();
    player->setCanDoubleJump(true);
}

void PlayerJumpState::update(int delta) {
    Player* player = dynamic_cast<Player*>(this->getOwner());
    if (player->willUseArrow()) player->setWillUseArrow(false); // 取消射箭请求
    if (player->willJump()) {
        // 执行二段跳
        player->setWillJump(false); // 取消跳跃请求
        if (player->canDoubleJump() && player->hasDoubleJumpSkill()) {
            player->jump();
            player->setCanDoubleJump(false);
        }
    }
    else if (player->isRunning()) {
        if(player->isOnFloor())
            player->setState("Run");
        else {
            if (player->getIsFacingRight())
                player->setAtlas(ResourceManager::Instance().getAtlas(AtlasType::atlasPlayerRunRight));
            else
                player->setAtlas(ResourceManager::Instance().getAtlas(AtlasType::atlasPlayerRunLeft));
        }
    }
    else if(!player->isRunning()) {
        if(player->isOnFloor())
            player->setState("Idle");
        else {
            if (player->getIsFacingRight())
                player->setAtlas(ResourceManager::Instance().getAtlas(AtlasType::atlasPlayerIdleRight));
            else
                player->setAtlas(ResourceManager::Instance().getAtlas(AtlasType::atlasPlayerIdleLeft));
        }
    }
}

void PlayerJumpState::onExit() {}
