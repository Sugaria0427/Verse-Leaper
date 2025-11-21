#pragma once
#include "Enemy.h"

class Dog :
    public Enemy
{
public:
    Dog(Tag _tag, Animation* _animation, Box* _EnemyBox);
    Dog(const Dog& dog);
    ~Dog() {}
    void initDog();
    GameObject* clone() override { return new Dog(*this); }
    void update(int delta) override;

    Box& getChaseRange() { return chaseRange; }
    void setChaseRange(int x, int y, int width, int height) { chaseRange.setBox(x, y, width, height); }
private:
    Box chaseRange = Box();
};

class Eagle :
    public Enemy
{
public:
    Eagle(Tag _tag, Animation* _animation, Box* _EnemyBox);
    Eagle(const Eagle& Eagle);
    ~Eagle() {}
    void initEagle();
    void update(int delta) override;
    GameObject* clone() override { return new Eagle(*this); }

    Box& getPatrolRange() { return patrolRange; }
private:
    Box patrolRange = Box();
};

class Tiger :
    public Enemy
{
public:
    Tiger(Tag _tag, Animation* _animation, Box* _EnemyBox);
    Tiger(const Tiger& tiger);
    ~Tiger() {}
    void initTiger();
    GameObject* clone() override;
    void update(int delta) override;
    void draw(SDL_Renderer* SDL_renderer) override;
    void beDeleted() override {}
    CollisionBox* getBiteBox() { return biteBox; }

    Box& getAttackRange() { return attackRange; }
    Box& getJumpRange() { return jumpRange; }
private:
    Animation biteBoxAnimation;
    CollisionBox* biteBox = nullptr;
    Box attackRange = Box();
    Box jumpRange = Box();
};

class Boss :
    public Enemy
{
public:
    Boss(Tag _tag, Animation* _animation, Box* _EnemyBox);
    Boss(const Boss& boss);
    ~Boss() {}
    void initBoss();
    GameObject* clone() override;
    void update(int delta) override;
    void draw(SDL_Renderer* SDL_renderer) override;
    void beDeleted() override {}

    Box& getLaserRange() { return laserRange; }
    CollisionBox* getLaserBox() { return laserBox; }
    std::vector<CollisionBox*>& getBarrageBoxes() { return barrageBoxes; }
private:
    Animation laserBoxAnimation;
    Animation barrageBoxAnimation;
    CollisionBox* laserBox = nullptr;
    std::vector<CollisionBox*> barrageBoxes;
    Box laserRange = Box();
};

