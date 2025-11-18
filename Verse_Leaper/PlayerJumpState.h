#pragma once
#include "StateNode.h"
class PlayerJumpState :
    public StateNode
{
public:
    PlayerJumpState(GameObject* owner) : StateNode(owner) {}
    ~PlayerJumpState() = default;
    void onEnter() override;
    void update(int delta) override;
    void onExit() override;
private:
    int jumpChannel = -1;
};

