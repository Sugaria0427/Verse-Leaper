#pragma once
#include "GameObject.h"

class Block :
    public GameObject
{
public:
    // ctor & dtor
    Block(Tag _tag, Animation* _animation, Box* _Box);
    Block(const Block& block);
    ~Block() override;
    GameObject* clone() override;
    void beDeleted() override;
    // getters&setters
    void setExist(bool isExist_) override {
        this->isExist_ = isExist_;
        collisionBox->setCollidable(isExist_);
    }
    CollisionBox* getCollisionBox() { return collisionBox; }
    void update(int delta) override;
    void initCollisionBox();
private:
    CollisionBox* collisionBox = nullptr;
	CollisionBox* boardBox = nullptr;
};

