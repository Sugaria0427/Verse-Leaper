#pragma once
#include "StateNode.h"
class PlayerRunState :
    public StateNode
{
public:
    PlayerRunState(GameObject* owner) : StateNode(owner) {}
    ~PlayerRunState() = default;
    void onEnter() override;
    void update(int delta) override;
    void onExit() override;
private:
    int runSoundChannel = -1;
};

