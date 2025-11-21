#pragma once
#include "Entity.h"
class Npc :
    public Entity
{
public:
    Npc(Tag _tag, Animation* _animation, Box* _NpcBox) : Entity(_tag, _animation, _NpcBox) {}
    Npc(const Npc& npc) : Entity(npc) {}
    ~Npc() override = default;
    GameObject* clone() override { return new Npc(*this); }
    void beDeleted() override { delete this; }
};