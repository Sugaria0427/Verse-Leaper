#pragma once
#include<vector>
#include"CollisionBox.h"

class GameObject;

class CollisionManager
{
public:
    // 单例模式获取实例对象
    static CollisionManager* instance();
    // 创建与销毁CollisionBox由collisionManager负责
    CollisionBox* creatCollisionBox(GameObject* owner, int x, int y, int width, int height);
    CollisionBox* clone(CollisionBox& box);
    void deleteCollisionBox(CollisionBox*& box);
    void clearCollisionBoxVec();

    void onDebugDraw(SDL_Renderer* SDL_renderer);
    void updateCollision();
private:
    CollisionManager() {}
    static CollisionManager* collisionManager;
    std::vector<CollisionBox*> collisionBoxVec;
};

