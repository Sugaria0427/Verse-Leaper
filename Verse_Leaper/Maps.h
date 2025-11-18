#pragma once
#include"Map.h"

class InitialMap : public Map 
{
public:
    InitialMap(int width, int height);
    ~InitialMap() {}
    void onEnter() override;
    void onUpdate(int delta) override;
    void onExit() override;
};

class TowerMap : public Map
{
public:
    TowerMap(int width, int height);
    ~TowerMap() {}
    void onEnter() override;
    void onUpdate(int delta) override;
    void onExit() override;
};

class TransitionMap : public Map 
{
public:
    TransitionMap(int width, int height);
    ~TransitionMap() {}
    void onEnter() override;
    void onUpdate(int delta) override;
    void onExit() override;
};

class CloudMap : public Map
{
public:
    CloudMap(int width, int height);
    ~CloudMap() {}
    void onEnter() override;
    void onUpdate(int delta) override;
    void onExit() override;
};

class TigerMap : public Map 
{
public:
    TigerMap(int width, int height);
    ~TigerMap() {}
    void onEnter() override;
    void onUpdate(int delta) override;
    void onExit() override;
};

class BossMap : public Map 
{
public:
    BossMap(int width, int height);
    ~BossMap() {}
    void onEnter() override;
    void onUpdate(int delta) override;
    void onExit() override;
};