#pragma once
#include "StateNode.h"
#include "Timer.h"

class BossIdleState :
    public StateNode
{
public:
    BossIdleState(GameObject* owner);
    ~BossIdleState() = default;
    void onEnter() override;
    void update(int delta) override;
    void onExit() override;
private:
    Timer idleTimer_;
};

class BossLaserState :
    public StateNode
{
public:
    BossLaserState(GameObject* owner);
    ~BossLaserState() = default;
    void onEnter() override;
    void update(int delta) override;
    void onExit() override;
private:
    Timer laserStartupTimer_;
    Timer laserTimer_;
	int bossLasserChannel = -1;
	int bossFireChannel = -1;
	bool willFireLaser = true;
};

class BossBarrageState :
    public StateNode
{
public:
    BossBarrageState(GameObject* owner);
    ~BossBarrageState() = default;
    void onEnter() override;
    void update(int delta) override;
    void onExit() override;
private:
    Timer barrageStartupTimer_;
    Timer barrageTimer_;
	int bossBarrageChannel = -1;
    bool willFireBarrage = true;
};

class BossWeakState :
    public StateNode
{
public:
    BossWeakState(GameObject* owner);
    ~BossWeakState() = default;
    void onEnter() override;
    void update(int delta) override;
    void onExit() override;
private:
    Timer weakTimer_;
	int bossWeakChannel = -1;
};

class BossMoveState :
    public StateNode
{
public:
    BossMoveState(GameObject* owner);
    ~BossMoveState() = default;
    void onEnter() override;
    void update(int delta) override;
    void onExit() override;
private:
    Timer moveTimer_;
	int bossMoveChannel = -1;
};
