#include "Entity.h"

Entity::Entity(Tag tag_, Animation* _animation, Box* _NpcBox, int _HP, int _AD, int _MaxHP) : GameObject(tag_, _animation, _NpcBox, _HP, _AD, _MaxHP){
    initEntityBox();
}

void Entity::update(int delta) {
    if (isExist_) {
        // 状态机更新
        stateMacine.update(delta);

        this->setOnFloor(false);
        // 下坠
        this->setSpeedY(this->getSpeed().getY() + this->getGravity().getY());  // 累加速度
        // 更新位置坐标
        updatePosition();
        // 更新动画
        this->animation->updateIdxFrame(delta);
        // 碰撞箱移动
        this->entityBox->setBoxPosition(this->getBoxX(), this->getBoxY());
    }
}

void Entity::initEntityBox()
{
    initPosition = {(double)this->getBoxX(), (double)this->getBoxY()};
    entityBox = CollisionManager::instance()->creatCollisionBox(this, this->box->getX(), this->box->getY(), this->box->getWidth(), this->box->getHeight());
    this->entityBox->setLayerSrc(CollisionBox::Layer::Entity);
    this->entityBox->setLayerDst(CollisionBox::Layer::Block);
    entityBox->setOnCollide(
        [this](CollisionBox* boxDst) {
            // 获得两碰撞箱坐标轴投影重叠长度
            int xLength, yLength;
            this->getCollisionBox()->getOverlapLength(xLength, yLength, boxDst);
            // 获得两box的中心点
            int srcCenterX = (this->box->getX() + this->box->getWidth()) / 2;
            int srcCenterY = (this->box->getY() + this->box->getHeight()) / 2;
            int dstCenterX = (boxDst->getX() + boxDst->getWidth()) / 2;
            int dstCenterY = (boxDst->getY() + boxDst->getHeight()) / 2;
            if (yLength < xLength) {
                if (srcCenterY < dstCenterY) {
                    this->setBoxY(boxDst->getY() - this->getBoxHeight());
                    this->entityBox->setBoxPosition(this->entityBox->getX(), boxDst->getY() - this->getBoxHeight());
					this->setOnFloor(true);
                }
                else {
                    this->setBoxY(boxDst->getY() + boxDst->getHeight());
                    this->entityBox->setBoxPosition(this->entityBox->getX(), boxDst->getY() + boxDst->getHeight());
                }
                this->setSpeedY(0);
            }
            else {
                if (srcCenterX > dstCenterX) {
                    this->setBoxX(boxDst->getX() + boxDst->getWidth());
                    this->entityBox->setBoxPosition(boxDst->getX() + boxDst->getWidth(), this->entityBox->getY());
                }
                else {
                    this->setBoxX(boxDst->getX() - this->getBoxWidth());
                    this->entityBox->setBoxPosition(boxDst->getX() - this->getBoxWidth(), this->entityBox->getY());
                }
                this->setSpeedX(0);
            }
        }
    );
    entityBox->setCollidable(true);
    if (!this->isExist()) 
        entityBox->setCollidable(false);
}
