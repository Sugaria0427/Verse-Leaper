#pragma once
#include<vector>
#include"Vector2.h"
#include"Tag.h"

class GameObject;

class Map
{
public:
    Map(int width, int height) : mapSize_{ (double)width, (double)height } {}
    ~Map() = default;
    virtual void onEnter() {}
    virtual void onUpdate(int delta) {}
    virtual void onExit() {}
    std::vector<GameObject*>& getGameObjVec() { return gameObjVec_; }
    Vector2 getMapSize() const { return mapSize_; }
protected:
    std::vector<GameObject*> gameObjVec_;
    Vector2 mapSize_{ 100, 100 };
};