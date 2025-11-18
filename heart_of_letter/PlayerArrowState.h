#pragma once
#include "StateNode.h"
#include "Timer.h"
class PlayerArrowState :
    public StateNode
{
public:
    PlayerArrowState(GameObject* owner);
    ~PlayerArrowState() = default;
    void onEnter() override;
    void update(int delta) override;
    void onExit() override {}
private:
    Timer usingArrowTimer_;
};
