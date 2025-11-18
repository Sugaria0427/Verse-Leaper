#pragma once
#include "StateNode.h"
#include "Timer.h"
class EnemyEaglePatrolState :
    public StateNode
{
public:
    EnemyEaglePatrolState(GameObject* owner);
    ~EnemyEaglePatrolState() = default;
    void onEnter() override;
    void update(int delta) override;
    void onExit() override;
private:
    Timer patrolTimer_;
    bool isMoveRight_ = false;
    bool isPlayedFly = false;
	int eagleFlyChannel = -1;
};

class EnemyEagleHurtState :
    public StateNode
{
public:
    EnemyEagleHurtState(GameObject* owner);
    ~EnemyEagleHurtState() = default;
    void onEnter() override;
    void update(int delta) override;
    void onExit() override;
private:
    Timer* hurtTimer;
	int eagleHawkChannel = -1;
};

class EnemyEagleDeadState :
    public StateNode
{
public:
    EnemyEagleDeadState(GameObject* owner);
    ~EnemyEagleDeadState() = default;
    void onEnter() override;
    void update(int delta) override;
    void onExit() override;
private:
	int dieChannel = -1;
};

