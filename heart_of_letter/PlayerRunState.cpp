#include "PlayerRunState.h"
#include "Player.h"
#include"ResourceManager.h"


void PlayerRunState::onEnter() {
    Player* player = dynamic_cast<Player*>(this->getOwner());
    if (player->getSpeed().getX() >= 0)
        player->setAtlas(ResourceManager::Instance().getAtlas(AtlasType::atlasPlayerRunRight));
    else
        player->setAtlas(ResourceManager::Instance().getAtlas(AtlasType::atlasPlayerRunLeft));
    // 播放走路音效
    runSoundChannel = Mix_PlayChannel(-1, ResourceManager::Instance().getSound(SoundType::run), -1);
}

void PlayerRunState::update(int delta) {
    Player* player = dynamic_cast<Player*>(this->getOwner());
    if (player->willJump()) 
        player->setState("Jump");
    else if(player->willUseArrow())
        player->setState("Arrow");
    else if (player->getSpeed().getX() == 0) 
        player->setState("Idle");
}

void PlayerRunState::onExit() {
    // 停止走路音效
    Mix_HaltChannel(runSoundChannel);
}
