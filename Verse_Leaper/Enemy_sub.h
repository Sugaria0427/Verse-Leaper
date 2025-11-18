#pragma once
#include "Enemy.h"
class EnemyDog :
    public Enemy
{
public:
    EnemyDog(Tag _tag, Animation* _animation, Box* _EnemyBox);
    EnemyDog(const EnemyDog& dog);
    ~EnemyDog() {}
    void initDog();
    GameObject* clone() override { return new EnemyDog(*this); }
    void update(int delta) override;

    Box& getChaseRange() { return chaseRange; }
    void setChaseRange(int x, int y, int width, int height) { chaseRange.setBox(x, y, width, height); }
private:
    Box chaseRange = Box();
};

class EnemyEagle :
    public Enemy
{
public:
    EnemyEagle(Tag _tag, Animation* _animation, Box* _EnemyBox);
    EnemyEagle(const EnemyEagle& Eagle);
    ~EnemyEagle() {}
    void initEagle();
    void update(int delta) override;
    GameObject* clone() override { return new EnemyEagle(*this); }

    Box& getPatrolRange() { return patrolRange; }
private:
    Box patrolRange = Box();
};

class EnemyTiger :
    public Enemy
{
public:
    EnemyTiger(Tag _tag, Animation* _animation, Box* _EnemyBox);
    EnemyTiger(const EnemyTiger& tiger);
    ~EnemyTiger() {}
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

class EnemyBoss :
    public Enemy
{
public:
    EnemyBoss(Tag _tag, Animation* _animation, Box* _EnemyBox);
    EnemyBoss(const EnemyBoss& boss);
    ~EnemyBoss() {}
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

