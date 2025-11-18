#include "StateMacine.h"

void StateMacine::switchTo(std::string stateNodeName) {
    currentState->onExit();
    this->setCurrentState(stateNodeName);
    currentState->onEnter();
}

void StateMacine::update(int delta) {
    if(currentState)
        currentState->update(delta);
}

void StateMacine::addStateNode(std::string stateNodeName, StateNode* stateNode) {
    stateNodePool[stateNodeName] = stateNode;
}

StateNode* StateMacine::getStateNode(std::string stateNodeName)
{
    if (stateNodePool.find(stateNodeName) != stateNodePool.end()) {
        return stateNodePool[stateNodeName];
    }
    else {
        return nullptr;
    }
}

StateNode* StateMacine::getCurrentState()
{
    return currentState;
}

void StateMacine::setCurrentState(std::string stateNodeName)
{
    if (stateNodePool.find(stateNodeName) != stateNodePool.end()) {
        currentState = stateNodePool[stateNodeName];
    }
    else {
        throw stateNodeName;
    }
}