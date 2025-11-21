#include "Drum.h"
#include "GameObjFactory.h"
#include "GameObjectManager.h"
#include <iostream>

Drum::Drum(Tag _tag, Animation* _animation, Box* _box) :
	GameObject(_tag, _animation, _box)
{
	initDrum();
}

Drum::Drum(const Drum& obj) : GameObject(obj), drumBox(nullptr) {
	initDrum();
}

void Drum::update(int delta) {
	if (isExist_) {
		if (drumBox) {
			drumBox->setBox(this->getBoxX(), this->getBoxY(), this->getBoxWidth(), this->getBoxHeight());
		}
	}
	if(this->willDrop()) {
		DropItem* dropItem = GameObjFactory::instance()->createDropItem(Tag::DropItem_Sword, this->getBoxX(), this->getBoxY());
		dropItem->drop(this->getBoxX(), this->getBoxY());
		GameObjManager::instance()->addGameObj(dropItem);
		this->setWillDrop(false);
	}
}

GameObject* Drum::clone() { return new Drum(*this); }

void Drum::initDrum()
{
	drumBox = CollisionManager::instance()->creatCollisionBox(this, box->getX(), box->getY(), box->getWidth(), box->getHeight());
	drumBox->setLayerSrc(CollisionBox::Layer::Null);
	drumBox->setLayerDst(CollisionBox::Layer::Bell);
	drumBox->setOnCollide(
		[this](CollisionBox* boxDst) {
			std::cout << "Drum collided with Bell" << std::endl;
			this->setWillDrop(true);
			for (GameObject* obje : GameObjManager::instance()->getVec()) {
				if (obje->getTag() == Tag::Enemy_Dog && obje->isExist()) {
					obje->setExist(false);
				}
			}
			this->setExist(false);
		}
	);
	drumBox->setCollidable(true);
}

