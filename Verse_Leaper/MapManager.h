#pragma once
#include <vector>
#include <iostream>
#include <unordered_map>
#include "Map.h"
#include "Tag.h"

class GameObject;

class MapManager
{
public:
    enum class TeleportFlag
    {
        Next,
        Prior,
        Extra,
        Null
    };
    static MapManager* instance();

    void update(int delta) {
        if(!currentMap_)
            throw std::runtime_error("No current map set in MapManager.");
        currentMap_->onUpdate(delta);
    }

    void creatMaps();

    void setInitialMap(std::string mapName);
    void switchMap(std::string mapName);
    void switchMap(Map* map);
    // getters&setters
	void setCurrentMap(std::string map);
    Map* getCurrentMap();
    
    Map* getMap(std::string mapName);
    void addMap(std::string mapName, Map* map);

    Vector2 getMapSize() const { return currentMap_ ? currentMap_->getMapSize() : Vector2(0, 0); }

    void setTeleportFlag(TeleportFlag flag) { this->flag_ = flag; }
    TeleportFlag getTeleportFlag() const { return flag_; }
private:
    MapManager() = default;
    ~MapManager() = default;
    static MapManager* mapManager_;
    std::unordered_map<std::string, Map*> mapPool_;
    Map* currentMap_ = nullptr;
    TeleportFlag flag_ = TeleportFlag::Null;
};