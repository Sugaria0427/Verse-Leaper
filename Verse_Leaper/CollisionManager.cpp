#include "CollisionManager.h"
#include "Panel.h"

CollisionManager* CollisionManager::collisionManager = nullptr;

CollisionManager* CollisionManager::instance()
{
    if (!collisionManager) {
       collisionManager = new CollisionManager();
    }
    return collisionManager;
}

void CollisionManager::updateCollision() {
    for (CollisionBox* boxSrc : collisionBoxVec) {
        if (!(boxSrc->canCollide()) || boxSrc->layerDst == CollisionBox::Layer::Null) { 
            continue;   // 拿出来src碰撞框无法碰撞其它的，则无需判断是否碰撞
        }
        for (CollisionBox* boxDst : collisionBoxVec) {
            if (!(boxDst->canCollide()) || boxDst->layerSrc == CollisionBox::Layer::Null || boxSrc == boxDst) {
                continue;   // 拿出来的dst碰撞框无法被其他的碰撞，或者src == dst（自己碰自己），也无需判断是否碰撞
            }
            if (boxSrc->layerDst == boxDst->layerSrc) {
                // 判断是否碰撞
                if (boxSrc->isAnotherCollide(boxDst) && boxSrc->onCollide != NULL) {
                    boxSrc->onCollide(boxDst);
                }
            }
        }
    }
}

CollisionBox* CollisionManager::creatCollisionBox(GameObject* owner, int x, int y, int width, int height)
{
    CollisionBox* box = new CollisionBox(x, y, width, height);
    collisionBoxVec.push_back(box);
	box->owner = owner;
    return box;
}

CollisionBox* CollisionManager::clone(CollisionBox& box) {
    return creatCollisionBox(box.getOwner(), box.getX(), box.getY(), box.getWidth(), box.getHeight());
}

void CollisionManager::deleteCollisionBox(CollisionBox* &box) {
    if (box) {
        delete box;
        box = nullptr;
    }
}

void CollisionManager::clearCollisionBoxVec()
{
    for (CollisionBox* box : this->collisionBoxVec) {
        this->deleteCollisionBox(box);
    }
    this->collisionBoxVec.clear();
}

void CollisionManager::onDebugDraw(SDL_Renderer* SDL_renderer)
{
    // 设置绘制颜色（红色）
    SDL_SetRenderDrawColor(SDL_renderer, 255, 0, 0, 255);
    
    for (CollisionBox* box : collisionBoxVec) {
        if (box->isCollisionExsist) {
            // 绘制矩形边框
            SDL_Rect* rect = box->getWindowRect(Panel::Instance().getCamera());
            SDL_RenderDrawRect(SDL_renderer, rect);
			delete rect;
        }
    }
}
