#pragma once
#include <unordered_map>
#include <string>
#include "StateNode.h"
class StateMacine
{
public:
    StateMacine() = default;
    ~StateMacine() = default;
    // ¹¦ÄÜº¯Êý
    void switchTo(std::string stateNodeName);
    void update(int delta);

    // getters&setters
    void addStateNode(std::string stateNodeName, StateNode* stateNode);
    StateNode* getStateNode(std::string stateNodeName);

    StateNode* getCurrentState();
    void setCurrentState(std::string stateNodeName);

    void setInitState(std::string stateNodeName) {
        this->setCurrentState(stateNodeName);
        this->currentState->onEnter();
    }
private:
    std::unordered_map<std::string, StateNode*> stateNodePool;
    StateNode* currentState = nullptr;
};

