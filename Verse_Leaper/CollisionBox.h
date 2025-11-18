#pragma once
#include<functional>
#include "Box.h"
#include "Vector2.h"

class GameObject;

class CollisionBox :
    public Box
{
friend class CollisionManager;

public:
	enum class Layer
	{
		Entity,
		Arrow,
		Player,
		Npc,
		Enemy,
		Interact,
		Block,
		HurtBox,
		HitBox,
		Bell,
		Drum,
		Null
	};
	Layer layerSrc = Layer::Null;	// 本身所属层
	Layer layerDst = Layer::Null;	// 可以碰撞层
	// getters&setters
	bool canCollide() const { return this->isCollisionExsist; }
	void setCollidable(bool collidable_) { this->isCollisionExsist = collidable_; }
	void setLayerSrc(Layer src) { this->layerSrc = src; }
	void setLayerDst(Layer dst) { this->layerDst = dst; }
	GameObject* getOwner() const { return this->owner; }
	// 回调函数：碰撞后会怎样由其他函数方法注入
	void setOnCollide(std::function<void(CollisionBox*)> function) {
		this->onCollide = function;
	}
	std::function<void(CollisionBox*)> onCollide = NULL;
	
	void getOverlapLength(int& xLength, int& yLength, CollisionBox* box);	// 获得自身与另一个box的投影重叠长度
	bool isAnotherCollide(CollisionBox* box);	// 判断另一个box是否在this内

	Vector2 speed = Vector2();
private:
	CollisionBox(int x, int y, int width, int height) : Box(x, y, width, height) {}
	~CollisionBox() = default;
	bool isCollisionExsist = true;
	GameObject* owner = nullptr;
};

