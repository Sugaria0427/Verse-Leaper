#pragma once
#include <iostream>
#include "GameObject.h"
#include "StateMachine.h"

class Entity :
    public GameObject
{
public:
    Entity(Tag tag_, Animation* _animation, Box* _NpcBox, int _HP = 0, int _AD = 0, int _MaxHP = 0);
    Entity(const Entity& src)
        : GameObject(src)
    {
        initEntityBox();
    }
    ~Entity() override {}
    // 接口
    void update(int delta) override;
    // getters&setters
    void setExist(bool isExist_) override {
        this->isExist_ = isExist_;
        entityBox->setCollidable(isExist_);
    }
    StateMachine& getStateMachine() { return stateMachine; }
    void setState(std::string state);
	void setOnFloor(bool onFloor) { isOnFloor_ = onFloor; }
	bool isOnFloor() const { return isOnFloor_; }
    // 获取碰撞箱
    CollisionBox* getCollisionBox() {
        if (entityBox) {
            return entityBox;
        }
        return nullptr;
    }
    void initEntityBox();

    Vector2 getInitPosition() const { return initPosition; }
    void setInitPosition(const Vector2& position) { initPosition = position; }
protected:
    CollisionBox* entityBox = nullptr;
    StateMachine stateMachine;
    bool isOnFloor_ = false;
    Vector2 initPosition = { 0,0 };
};

