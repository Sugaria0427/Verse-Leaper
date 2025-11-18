#pragma once
#include "StateNode.h"
class PlayerIdleState :
    public StateNode
{
public:
    PlayerIdleState(GameObject* owner) : StateNode(owner) {}
    ~PlayerIdleState() = default;
    void onEnter() override;
    void update(int delta) override;
    void onExit() override {}
};

