#pragma once
#include "Entity.h"

class Bell:
	public Entity
{
public:
    Bell(Tag _tag, Animation* _animation, Box* _BellBox);
    Bell(const Bell& bell);
    ~Bell() override = default;

    GameObject* clone() override { return new Bell(*this); }
    void beDeleted() override { delete this; }
    void update(int delta) override;
private:
	CollisionBox* bellBox = nullptr;
};
