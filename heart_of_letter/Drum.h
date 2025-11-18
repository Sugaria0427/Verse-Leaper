#pragma once
#include "GameObject.h"

class Drum :
	public GameObject
{
public:

	// ctor&dtor
	Drum(Tag _tag, Animation* _animation, Box* _box);
	Drum(const Drum& obj);

	void setWillDrop(bool willDrop) { this->willDrop_ = willDrop; }
	bool willDrop() const { return this->willDrop_; }

	// ½Ó¿Ú
	void update(int delta) override;
	GameObject* clone() override;
	void beDeleted() { delete this; }
	void setExist(bool isExist) override {
		this->isExist_ = isExist;
		drumBox->setCollidable(isExist_);
	}
	void initDrum();
private:
	bool willDrop_ = false;
	CollisionBox* drumBox = nullptr;	
};

