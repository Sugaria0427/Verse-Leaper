#pragma once
#include "Entity.h"

class DropItem :
    public Entity
{
public:
    // ctor&dtor
    DropItem(Tag tag, Animation* _animation, Box* _DropItemBox);
    DropItem(const DropItem& dropItem);
    ~DropItem() override = default;
    GameObject* clone() override { return new DropItem(*this); }
    void beDeleted() override { delete this; }
    // ½Ó¿Ú
    void update(int delta) override;

    void drop(int x, int y);
    void setExist(bool isExist_) override;

    void initDropItem();
protected:
    CollisionBox* interactBox;
	bool willPickUp = true;
};

