#include "DropItem.h"

DropItem::DropItem(Tag tag_, Animation* _animation, Box* _DropItemBox)
    : Entity(tag_, _animation, _DropItemBox)
{
    initDropItem();
}

DropItem::DropItem(const DropItem& dropItem)
    : Entity(dropItem)
{
    initDropItem();
}

void DropItem::update(int delta) {
    if (isExist_) {
        Entity::update(delta);
        this->interactBox->setBox(
            this->getBoxX(),
            this->getBoxY(),
            this->getBoxWidth(),
            this->getBoxHeight()
        );
    }
}

void DropItem::drop(int x, int y)
{
    this->setBoxX(x);
    this->setBoxY(y);
    Vector2 dropSpeed(0, -10);
    this->setSpeed(dropSpeed);
}

void DropItem::setExist(bool isExist_)
{
	Entity::setExist(isExist_);
    interactBox->setCollidable(isExist_);
}

void DropItem::initDropItem()
{
    //»¥¶¯Åö×²Ïä
    interactBox = CollisionManager::instance()->creatCollisionBox(this, box->getX(), box->getY(), box->getWidth(), box->getHeight());
    this->interactBox->setLayerSrc(CollisionBox::Layer::Interact);
    this->interactBox->setLayerDst(CollisionBox::Layer::Player);
    interactBox->setOnCollide(
        [this](CollisionBox* boxDst) {
            switch (this->getTag()) {
            case Tag::DropItem_Alcohol:
                std::cout << "DropItemÅö×²ÁËPlayer" << std::endl;
                boxDst->getOwner()->setAlcohol(true);
                break;
            case Tag::DropItem_Arrow:
                std::cout << "DropItemÅö×²ÁËPlayer" << std::endl;
                boxDst->getOwner()->setArrow(true);
                break;
            case Tag::DropItem_Sword:
                std::cout << "DropItemÅö×²ÁËPlayer" << std::endl;
                boxDst->getOwner()->setSword(true);
                break;
            case Tag::DropItem_DoubleJump:
                std::cout << "DropItemÅö×²ÁËPlayer" << std::endl;
                boxDst->getOwner()->setDoubleJumpSkill(true);
                break;
            case Tag::DropItem_Potion:
                if (willPickUp) {
                    std::cout << "DropItemÅö×²ÁËPlayer" << std::endl;
				    if (boxDst->getOwner()->getPotionCount() < 3) {
 					    boxDst->getOwner()->setPotionCount(boxDst->getOwner()->getPotionCount() + 1);
                    }
					this->willPickUp = false;
                }
				break;
            }
            this->setExist(false);
        }
    );
    this->interactBox->setCollidable(true);
}
