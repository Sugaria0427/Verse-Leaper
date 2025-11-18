#pragma once
#include "StateNode.h"
#include "Timer.h"
#include "Box.h"

class EnemyTigerIdleState :
    public StateNode
{
public:
    EnemyTigerIdleState(GameObject* owner);
    ~EnemyTigerIdleState() = default;
    void onEnter() override;
    void update(int delta) override;
    void onExit() override;
private:
    Timer idleTimer_;
};

class EnemyTigerAttackState :
    public StateNode
{
public:
    EnemyTigerAttackState(GameObject* owner);
    ~EnemyTigerAttackState() = default;
    void onEnter() override;
    void update(int delta) override;
    void onExit() override;
private:
    Timer attackStartup_;
    Timer attackTimer_;
    int tigerAttackChannel = -1;
	bool isPlayedAttack = false;
};

class EnemyTigerMoveState :
    public StateNode
{
public:
    EnemyTigerMoveState(GameObject* owner);
    ~EnemyTigerMoveState() = default;
    void onEnter() override;
    void update(int delta) override;
    void onExit() override;
private:
    Timer moveTimer_;
	int tigerRunChannel = -1;
};

class EnemyTigerJumpState :
    public StateNode
{
public:
    EnemyTigerJumpState(GameObject* owner);
    ~EnemyTigerJumpState() = default;
    void onEnter() override;
    void update(int delta) override;
    void onExit() override;
private:
	int tigerJumpChannel = -1;
};

class EnemyTigerDeadState :
    public StateNode
{
public:
    EnemyTigerDeadState(GameObject* owner);
    ~EnemyTigerDeadState() = default;
    void onEnter() override;
    void update(int delta) override;
    void onExit() override;
private:
	int dieChannel = -1;
};