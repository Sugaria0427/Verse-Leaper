#pragma once
#include "StateNode.h"
#include "Timer.h"

class EnemyDogPatrolState :
    public StateNode
{
public:
    EnemyDogPatrolState(GameObject* owner);
    ~EnemyDogPatrolState() = default;
    void onEnter() override;
    void update(int delta) override;
    void onExit() override;
private:
    Timer patrolTimer_;
    bool isMoveRight_ = false;
};

class EnemyDogHurtState :
    public StateNode
{
public:
    EnemyDogHurtState(GameObject* owner);
    ~EnemyDogHurtState() = default;
    void onEnter() override;
    void update(int delta) override;
    void onExit() override;
private:
    Timer* hurtTimer;
};

class EnemyDogDeadState :
    public StateNode
{
public:
    EnemyDogDeadState(GameObject* owner);
    ~EnemyDogDeadState() = default;
    void onEnter() override;
    void update(int delta) override;
    void onExit() override;
private:
    int dieChannel = -1;
};

class EnemyDogGobakState :
    public StateNode
{
public:
    EnemyDogGobakState(GameObject* owner);
    ~EnemyDogGobakState() = default;
    void onEnter() override;
    void update(int delta) override;
    void onExit() override;
private:
    int dogGobackChannel = -1;
};

class EnemyDogChaseState :
    public StateNode
{
public:
    EnemyDogChaseState(GameObject* owner) : StateNode(owner) {}
    ~EnemyDogChaseState() = default;
    void onEnter() override;
    void update(int delta) override;
    void onExit() override;
private:
	int dogChaseChannel = -1;
	int dogRunChannel = -1;
};