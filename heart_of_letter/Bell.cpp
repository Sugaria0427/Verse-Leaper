#include "Bell.h"

Bell::Bell(Tag _tag, Animation* _animation, Box* _BellBox)
	: Entity(_tag, _animation, _BellBox) {
	this->setGravity(0, 0);
	bellBox = CollisionManager::instance()->creatCollisionBox(this, this->box->getX(), this->box->getY(), this->box->getWidth(), this->box->getHeight());
	this->bellBox->setLayerSrc(CollisionBox::Layer::Bell);
	this->bellBox->setLayerDst(CollisionBox::Layer::Null);
	bellBox->setCollidable(true);
}

Bell::Bell(const Bell& bell)
    : Entity(bell)
{
	bellBox = CollisionManager::instance()->creatCollisionBox(this, this->box->getX(), this->box->getY(), this->box->getWidth(), this->box->getHeight());
	this->bellBox->setLayerSrc(CollisionBox::Layer::Bell);
	this->bellBox->setLayerDst(CollisionBox::Layer::Null);
	bellBox->setCollidable(true);
}

void Bell::update(int delta)
{
	Entity::update(delta);
	if (isExist_) {
		if (bellBox) {
			bellBox->setBox(this->getBoxX(), this->getBoxY(), this->getBoxWidth(), this->getBoxHeight());
		}
	}
}



