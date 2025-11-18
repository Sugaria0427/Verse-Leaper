#include "MapManager.h"

MapManager* MapManager::mapManager_ = nullptr;

MapManager* MapManager::instance() {
    if (!mapManager_) 
        mapManager_ = new MapManager();
    return mapManager_;
}

void MapManager::setInitialMap(std::string mapName)
{
    if(mapPool_.find(mapName) != mapPool_.end())
        currentMap_ = mapPool_[mapName];
    else 
        throw std::runtime_error("MapManager::setInitialMap: mapName not found");
    currentMap_->onEnter();
}

void MapManager::switchMap(std::string mapName)
{
    if (mapPool_.find(mapName) == mapPool_.end())
        throw std::runtime_error("MapManager::switchMap: map is null");
    else {
        this->currentMap_->onExit();
        this->currentMap_ = mapPool_[mapName];
        this->currentMap_->onEnter();
    }
}

void MapManager::switchMap(Map* map)
{
    if(!map)
        throw std::runtime_error("MapManager::switchMap: map is null");
    else {
        this->currentMap_->onExit();
        this->currentMap_ = map;
        this->currentMap_->onEnter();
    }
}

void MapManager::setCurrentMap(std::string mapName) {
    currentMap_ = mapPool_[mapName];
}

Map* MapManager::getCurrentMap() {
    return currentMap_;
}

Map* MapManager::getMap(std::string mapName)
{
    if(mapPool_.find(mapName) == mapPool_.end())
        throw std::runtime_error("MapManager::getMap: mapName not found");
    return mapPool_[mapName];
}

void MapManager::addMap(std::string mapName, Map* map)
{
    this->mapPool_[mapName] = map;
}
