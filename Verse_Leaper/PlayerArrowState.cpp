#include "PlayerArrowState.h"
#include "Player.h"
#include"ResourceManager.h"

PlayerArrowState::PlayerArrowState(GameObject* owner) : StateNode(owner) {
    usingArrowTimer_ = Timer();
    usingArrowTimer_.setWaitTime(200);
}

void PlayerArrowState::onEnter() {
    // 重置射箭计时器
    this->usingArrowTimer_.restart();
    // 切换射箭图集
    Player* player = dynamic_cast<Player*>(this->getOwner());
    if (player->getIsFacingRight())
        player->setAtlas(ResourceManager::Instance().getAtlas(AtlasType::atlasPlayerUseArrowRight));
    else
        player->setAtlas(ResourceManager::Instance().getAtlas(AtlasType::atlasPlayerUseArrowLeft));
    // 执行射箭动作
    player->useArrow();
    player->getBox()->setBox(player->getBoxX(), player->getBoxY(), player->getBoxWidth() + 50, player->getBoxHeight());
}

void PlayerArrowState::update(int delta) {
    // 更新射箭计时器
    usingArrowTimer_.update(delta);
    // 检查射箭动作是否完成
    Player* player = dynamic_cast<Player*>(this->getOwner());
    if (player->willJump()) player->setWillJump(false);         // 取消跳跃请求
    if (player->willUseArrow()) player->setWillUseArrow(false); // 取消射箭请求
    if (usingArrowTimer_.isShotted()) {
        player->getBox()->setBox(player->getBoxX(), player->getBoxY(), player->getBoxWidth() - 50, player->getBoxHeight());
        player->setState("Idle");   // 切换回待机状态
    }
}