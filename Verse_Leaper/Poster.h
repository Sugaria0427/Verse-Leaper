#pragma once
#include "GameObject.h"
class Poster :
    public GameObject
{
public:
    // ctor & dtor
    Poster(Tag _tag, Animation* _animation, Box* _Box) : GameObject(_tag, _animation, _Box) {}
    Poster(const Poster& poster) : GameObject(poster) {}
    ~Poster() {}
    void update(int delta) override { this->animation->updateIdxFrame(delta); }
    GameObject* clone() override { return new Poster(*this); }
    void beDeleted() override { delete this; }
private:
};

