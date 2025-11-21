#include "StateMachine.h"

void StateMachine::switchTo(std::string stateNodeName) {
    currentState->onExit();
    this->setCurrentState(stateNodeName);
    currentState->onEnter();
}

void StateMachine::update(int delta) {
    if(currentState)
        currentState->update(delta);
}

void StateMachine::addStateNode(std::string stateNodeName, StateNode* stateNode) {
    stateNodePool[stateNodeName] = stateNode;
}

StateNode* StateMachine::getStateNode(std::string stateNodeName)
{
    if (stateNodePool.find(stateNodeName) != stateNodePool.end()) {
        return stateNodePool[stateNodeName];
    }
    else {
        return nullptr;
    }
}

StateNode* StateMachine::getCurrentState()
{
    return currentState;
}

void StateMachine::setCurrentState(std::string stateNodeName)
{
    if (stateNodePool.find(stateNodeName) != stateNodePool.end()) {
        currentState = stateNodePool[stateNodeName];
    }
    else {
        throw stateNodeName;
    }
}