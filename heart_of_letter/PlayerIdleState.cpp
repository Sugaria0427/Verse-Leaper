#include "PlayerIdleState.h"
#include "Player.h"
#include "ResourceManager.h"

void PlayerIdleState::onEnter() {
    Player* player = dynamic_cast<Player*>(this->getOwner());
    if(player->getIsFacingRight()) 
        player->setAtlas(ResourceManager::Instance().getAtlas(AtlasType::atlasPlayerIdleRight));
    else
        player->setAtlas(ResourceManager::Instance().getAtlas(AtlasType::atlasPlayerIdleLeft));
}

void PlayerIdleState::update(int delta) {
    Player* player = dynamic_cast<Player*>(this->getOwner());
    if (player->willJump())
        player->setState("Jump");
    else if(player->willUseArrow())
        player->setState("Arrow");
    else if (player->getSpeed().getX() != 0)
        player->setState("Run");
}
