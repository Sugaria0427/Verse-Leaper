#pragma once
#include<string>

class GameObject;

class StateNode
{
public:
    StateNode(GameObject* owner) :owner_(owner) {}
    ~StateNode() = default;
    virtual void onEnter() {}
    virtual void update(int delta) {}
    virtual void onExit() {}
    GameObject* getOwner() { return owner_; }
protected:
    GameObject* owner_;
};

