#include "Maps.h"
#include "SDL_mixer.h"
#include "GameObjFactory.h"
#include "ResourceManager.h"

/// InitialMap
InitialMap::InitialMap(int width, int height) : Map(width, height) {
    this->gameObjVec_ = {
        // 背景
        GameObjFactory::instance()->createPosterBG(Tag::Poster_BG_Initial, width, height),
        //跳板
        GameObjFactory::instance()->createBlock(Tag::Block_JumpPad, 3 * 150, 11 * 150),         
        GameObjFactory::instance()->createBlock(Tag::Block_JumpPad, 10 * 150, 11 * 150),
        // Next传送块
        GameObjFactory::instance()->createBlock(Tag::Block_TeleportNext, 42 * 150, 3 * 150),
    };
    // 草皮
    GameObjFactory::instance()->createBlockAreaInMap(Tag::Block_IceGrass, 0 * 150, 11 * 150, 1, 3, this->gameObjVec_);
    GameObjFactory::instance()->createBlockAreaInMap(Tag::Block_IceGrass, 4 * 150, 6 * 150, 1, 6, this->gameObjVec_);
    GameObjFactory::instance()->createBlockAreaInMap(Tag::Block_IceGrass, 11 * 150, 11 * 150, 1, 11, this->gameObjVec_);
    GameObjFactory::instance()->createBlockAreaInMap(Tag::Block_IceGrass, 35 * 150, 5 * 150, 1, 7, this->gameObjVec_);
    // 浮空平台
    GameObjFactory::instance()->createBlockAreaInMap(Tag::Block_IceGrass, 12 * 150, 6 * 150, 1, 3, this->gameObjVec_);
    GameObjFactory::instance()->createBlockAreaInMap(Tag::Block_IceGrass, 17 * 150, 7 * 150, 1, 3, this->gameObjVec_);
    GameObjFactory::instance()->createBlockAreaInMap(Tag::Block_IceGrass, 22 * 150, 8 * 150, 1, 3, this->gameObjVec_);
    GameObjFactory::instance()->createBlockAreaInMap(Tag::Block_IceGrass, 27 * 150, 7 * 150, 1, 2, this->gameObjVec_);
    GameObjFactory::instance()->createBlockAreaInMap(Tag::Block_IceGrass, 31 * 150, 6 * 150, 1, 2, this->gameObjVec_);
    // 土壤
    GameObjFactory::instance()->createBlockAreaInMap(Tag::Block_IceGrassUnder, 0 * 150, 12 * 150, 1, 22, this->gameObjVec_);
    GameObjFactory::instance()->createBlockAreaInMap(Tag::Block_IceGrassUnder, 4 * 150, 7 * 150, 6, 6, this->gameObjVec_);
    GameObjFactory::instance()->createBlockAreaInMap(Tag::Block_IceGrassUnder, 35 * 150, 6 * 150, 7, 7, this->gameObjVec_);
    // 死亡区
    GameObjFactory::instance()->createBlockAreaInMap(Tag::Block_Dead, 0 * 150, 15 * 150, 2, 42, this->gameObjVec_);
    CollisionManager::instance()->clearCollisionBoxVec();
}

void InitialMap::onEnter() {
    MapManager::instance()->setCurrentMap("InitialMap");
    GameObjManager::instance()->switchObjVec();
    // 根据传入的Flag设置玩家进入地图的位置
    switch (MapManager::instance()->getTeleportFlag()) {
    case MapManager::TeleportFlag::Prior:
        GameObjManager::instance()->getPlayer()->setBoxX(41 * 150);
        GameObjManager::instance()->getPlayer()->setBoxY(3 * 150);
        GameObjManager::instance()->getPlayer()->setSpeed(0, 0);
        break;
    case MapManager::TeleportFlag::Null:
        break;
    default:
        throw "InitialMap::onEnter: Unknown Flag";
        break;
    }
    MapManager::instance()->setTeleportFlag(MapManager::TeleportFlag::Null);
	// BGM播放
    Mix_ResumeMusic();
    Mix_PlayMusic(ResourceManager::Instance().getMusic(MusicType::initialBgm), -1);
}

void InitialMap::onUpdate(int delta) {
    // 根据踩到的传送块设置Flag并切换地图
    switch (MapManager::instance()->getTeleportFlag()) {
    case MapManager::TeleportFlag::Prior:
        MapManager::instance()->switchMap("InitialMap");
        break;
    case MapManager::TeleportFlag::Next:
        MapManager::instance()->switchMap("TowerMap");
        break;
    }
}
void InitialMap::onExit() {
    Mix_HaltChannel(-1); // 停止所有音效播放
	Mix_HaltMusic(); // 停止BGM播放
}


/// TowerMap
TowerMap::TowerMap(int width, int height) : Map(width, height) {
    this->gameObjVec_ = {
       GameObjFactory::instance()->createPosterBG(Tag::Poster_BG_Tower, width, height),
       GameObjFactory::instance()->createPoster(Tag::Poster_smallTower, -1 * 150, -5 * 150, 7 * 150, 12 * 150),
       GameObjFactory::instance()->createPoster(Tag::Poster_mainTower, 7 * 150, -3 * 150 + 40, 11 * 150, 12 * 150 - 40),
       GameObjFactory::instance()->createBlock(Tag::Block_TeleportPrior, -1 * 150, 5 * 150),    // Prior传送块
       GameObjFactory::instance()->createBlock(Tag::Block_TeleportNext, 22 * 150, 8 * 150),     // Next传送块
       GameObjFactory::instance()->createBell(Tag::Bell, 12 * 150, 3 * 150),    // 钟
       GameObjFactory::instance()->createDrum(Tag::Drum, 12 * 150, 8 * 150),    // 鼓
       GameObjFactory::instance()->createNpc(Tag::Npc_OldMan, 1 * 150, 4 * 150),    // 鼓
        // 怪物
        GameObjFactory::instance()->createEnemy(Tag::Enemy_Dog, 13 * 150, 7 * 150),
    };
    // 塔雾
    GameObjFactory::instance()->createBlockAreaInMap(Tag::Block_TowerMist, 16 * 150, 1 * 150, 8, 1, this->gameObjVec_);
    // 木板
    GameObjFactory::instance()->createBlockAreaInMap(Tag::Block_Board, 11 * 150, 5 * 150, 1, 3, this->gameObjVec_);
    // 草皮
    GameObjFactory::instance()->createBlockAreaInMap(Tag::Block_Grass, 0 * 150, 6 * 150, 1, 5, this->gameObjVec_);
    GameObjFactory::instance()->createBlockAreaInMap(Tag::Block_Grass, 7 * 150, 9 * 150, 1, 15, this->gameObjVec_);
    // 土壤
    GameObjFactory::instance()->createBlockAreaInMap(Tag::Block_GrassUnder, 0 * 150, 7 * 150, 4, 5, this->gameObjVec_);
    GameObjFactory::instance()->createBlockAreaInMap(Tag::Block_GrassUnder, 5 * 150, 10 * 150, 1, 17, this->gameObjVec_);
    // 跳板
    GameObjFactory::instance()->createBlockAreaInMap(Tag::Block_JumpPad, 5 * 150, 9 * 150, 1, 2, this->gameObjVec_);
    // 空气墙
    GameObjFactory::instance()->createBlockAreaInMap(Tag::Block_Air, 7 * 150, 6 * 150, 1, 2, this->gameObjVec_);
    GameObjFactory::instance()->createBlockAreaInMap(Tag::Block_Air, 9 * 150, 5 * 150, 1, 2, this->gameObjVec_);
    GameObjFactory::instance()->createBlockAreaInMap(Tag::Block_Air, 14 * 150, 5 * 150, 1, 2, this->gameObjVec_);
    GameObjFactory::instance()->createBlockAreaInMap(Tag::Block_Air, 10 * 150, 1 * 150, 1, 6, this->gameObjVec_);
}

void TowerMap::onEnter() {
    MapManager::instance()->setCurrentMap("TowerMap");
    GameObjManager::instance()->switchObjVec();
    // 根据传入的Flag设置玩家位置
    switch (MapManager::instance()->getTeleportFlag()) {
    case MapManager::TeleportFlag::Prior:
        GameObjManager::instance()->getPlayer()->setBoxX(21 * 150);
        GameObjManager::instance()->getPlayer()->setBoxY(7 * 150);
        GameObjManager::instance()->getPlayer()->setSpeed(0, 0);
        break;
    case MapManager::TeleportFlag::Next:
        GameObjManager::instance()->getPlayer()->setBoxX(0 * 150);
        GameObjManager::instance()->getPlayer()->setBoxY(4 * 150);
        GameObjManager::instance()->getPlayer()->setSpeed(0, 0);
        break;
    case MapManager::TeleportFlag::Null:
        break;
    default:
        throw "TowerMap::onEnter: Unknown Flag";
        break;
    }
    MapManager::instance()->setTeleportFlag(MapManager::TeleportFlag::Null);
    // BGM播放
    Mix_ResumeMusic();
    Mix_PlayMusic(ResourceManager::Instance().getMusic(MusicType::initialBgm), -1);
}

void TowerMap::onUpdate(int delta) {
    switch (MapManager::instance()->getTeleportFlag()) {
    case MapManager::TeleportFlag::Prior:
        MapManager::instance()->switchMap("InitialMap");
        break;
    case MapManager::TeleportFlag::Next:
        MapManager::instance()->switchMap("TransitionMap");
        break;
    }
}

void TowerMap::onExit() {
    Mix_HaltChannel(-1); // 停止所有音效播放
    Mix_HaltMusic(); // 停止BGM播放
}

/// TransitionMap
TransitionMap::TransitionMap(int width, int height) : Map(width, height) {
    this->gameObjVec_ = {
       // 贴图
       GameObjFactory::instance()->createPosterBG(Tag::Poster_BG_Transition, width, height),
       GameObjFactory::instance()->createPoster(Tag::Poster_tree, 0 * 150, 12 * 150, 8 * 150, 6 * 150),
       GameObjFactory::instance()->createPoster(Tag::Poster_tree, 8 * 150, 11 * 150, 8 * 150, 6 * 150),
       GameObjFactory::instance()->createPoster(Tag::Poster_wall, 21 * 150, 13 * 150, 8 * 150, 3 * 150),
       // NPC
       GameObjFactory::instance()->createNpc(Tag::Npc_SuShi_Old_giveArrow, 26 * 150, 14 * 150),
       GameObjFactory::instance()->createNpc(Tag::Npc_SuShi_Old_alcohol, 26 * 150, 14 * 150),
       // 传送块
       GameObjFactory::instance()->createBlock(Tag::Block_TeleportExtra, 46 * 150, 12 * 150),
       GameObjFactory::instance()->createBlock(Tag::Block_TeleportNext, -1 * 150, 3 * 150),
       GameObjFactory::instance()->createBlock(Tag::Block_TeleportPrior, -1 * 150, 17 * 150),
       // 存档点
       GameObjFactory::instance()->createBlock(Tag::Block_SavePoint, 28 * 150, 15 * 150),
       // 怪物
       GameObjFactory::instance()->createEnemy(Tag::Enemy_Eagle, 11 * 150, 12 * 150),
       GameObjFactory::instance()->createEnemy(Tag::Enemy_Eagle, 12 * 150, 9 * 150),
       GameObjFactory::instance()->createEnemy(Tag::Enemy_Eagle, 39 * 150, 12 * 150),
    };
    // 雾
    GameObjFactory::instance()->createBlockAreaInMap(Tag::Block_Mist_SuShi_Arrow, 28 * 150, 10 * 150, 6, 1, this->gameObjVec_);
    // 草皮
    GameObjFactory::instance()->createBlockAreaInMap(Tag::Block_Grass, 0 * 150, 18 * 150, 1, 6, this->gameObjVec_);
    GameObjFactory::instance()->createBlockAreaInMap(Tag::Block_Grass, 8 * 150, 17 * 150, 1, 12, this->gameObjVec_);
    GameObjFactory::instance()->createBlockAreaInMap(Tag::Block_Grass, 21 * 150, 16 * 150, 1, 5, this->gameObjVec_);
    GameObjFactory::instance()->createBlockAreaInMap(Tag::Block_Grass, 27 * 150, 16 * 150, 1, 5, this->gameObjVec_);
    GameObjFactory::instance()->createBlockAreaInMap(Tag::Block_Grass, 33 * 150, 16 * 150, 1, 1, this->gameObjVec_);
    GameObjFactory::instance()->createBlockAreaInMap(Tag::Block_Grass, 36 * 150, 15 * 150, 1, 4, this->gameObjVec_);
    GameObjFactory::instance()->createBlockAreaInMap(Tag::Block_Grass, 43 * 150, 13 * 150, 1, 3, this->gameObjVec_);
    // 土壤
    GameObjFactory::instance()->createBlockAreaInMap(Tag::Block_GrassUnder, 0 * 150, 19 * 150, 1, 6, this->gameObjVec_);
    GameObjFactory::instance()->createBlockAreaInMap(Tag::Block_GrassUnder, 8 * 150, 18 * 150, 2, 12, this->gameObjVec_);
    GameObjFactory::instance()->createBlockAreaInMap(Tag::Block_GrassUnder, 21 * 150, 17 * 150, 3, 11, this->gameObjVec_);
    GameObjFactory::instance()->createBlockAreaInMap(Tag::Block_GrassUnder, 36 * 150, 16 * 150, 4, 5, this->gameObjVec_);
    GameObjFactory::instance()->createBlockAreaInMap(Tag::Block_GrassUnder, 43 * 150, 14 * 150, 6, 3, this->gameObjVec_);
    // 云
    GameObjFactory::instance()->createBlockAreaInMap(Tag::Block_Cloud2, 21 * 150, 12 * 150, 1, 3, this->gameObjVec_);
    // 天空上的：草皮
    GameObjFactory::instance()->createBlockAreaInMap(Tag::Block_Grass, 14 * 150, 11 * 150, 1, 5, this->gameObjVec_);
    GameObjFactory::instance()->createBlockAreaInMap(Tag::Block_Grass, 10 * 150, 7 * 150, 1, 2, this->gameObjVec_);
    GameObjFactory::instance()->createBlockAreaInMap(Tag::Block_Grass, 0 * 150, 6 * 150, 1, 8, this->gameObjVec_);
    // 跳跃板
    GameObjFactory::instance()->createBlockAreaInMap(Tag::Block_JumpPad, 26 * 150, 16 * 150, 1, 1, this->gameObjVec_);
    GameObjFactory::instance()->createBlockAreaInMap(Tag::Block_JumpPad, 13 * 150, 11 * 150, 1, 1, this->gameObjVec_);
    GameObjFactory::instance()->createBlockAreaInMap(Tag::Block_JumpPad, 40 * 150, 15 * 150, 1, 1, this->gameObjVec_);
    // 死亡区
    GameObjFactory::instance()->createBlockAreaInMap(Tag::Block_Dead, 0 * 150, 22 * 150, 2, 46, this->gameObjVec_);
}

void TransitionMap::onEnter() {
    // 切换游戏对象管理器中的对象列表为当前地图的对象列表
    MapManager::instance()->setCurrentMap("TransitionMap");
    GameObjManager::instance()->switchObjVec();
    // 根据传入的Flag设置玩家位置
    switch (MapManager::instance()->getTeleportFlag()) {
    case MapManager::TeleportFlag::Prior:   
        // 从CloudMap传送过来
        GameObjManager::instance()->getPlayer()->setBoxX(0 * 150);
        GameObjManager::instance()->getPlayer()->setBoxY(4 * 150);
        GameObjManager::instance()->getPlayer()->setSpeed(0, 0);
        break;
    case MapManager::TeleportFlag::Next:
        // 从TowerMap传送过来
        GameObjManager::instance()->getPlayer()->setBoxX(0 * 150);
        GameObjManager::instance()->getPlayer()->setBoxY(16 * 150);
        GameObjManager::instance()->getPlayer()->setSpeed(0, 0);
        break;
    case MapManager::TeleportFlag::Extra:
        // 从TigerMap传送过来
        GameObjManager::instance()->getPlayer()->setBoxX(45 * 150);
        GameObjManager::instance()->getPlayer()->setBoxY(11 * 150);
        GameObjManager::instance()->getPlayer()->setSpeed(0, 0);
        break;
    case MapManager::TeleportFlag::Null:
        GameObjManager::instance()->getPlayer()->setSpeed(0, 0);
        break;
    default:
        throw "TransitionMap::onEnter: Unknown Flag";
        break;
    }
    MapManager::instance()->setTeleportFlag(MapManager::TeleportFlag::Null);
    // BGM播放
    Mix_ResumeMusic();
    Mix_PlayMusic(ResourceManager::Instance().getMusic(MusicType::initialBgm), -1);
}

void TransitionMap::onUpdate(int delta) {
    switch (MapManager::instance()->getTeleportFlag()) {
    case MapManager::TeleportFlag::Prior:
        MapManager::instance()->switchMap("TowerMap");
        break;
    case MapManager::TeleportFlag::Next:
        MapManager::instance()->switchMap("CloudMap");
        break;
    case MapManager::TeleportFlag::Extra:
        MapManager::instance()->switchMap("TigerMap");
        break;
    }
}

void TransitionMap::onExit() {
    Mix_HaltChannel(-1); // 停止所有音效播放
    Mix_HaltMusic(); // 停止BGM播放
}


/// TigerMap
TigerMap::TigerMap(int width, int height) : Map(width, height) {
    this->gameObjVec_ = {
        GameObjFactory::instance()->createPosterBG(Tag::Poster_BG_Tiger, width, height),
        GameObjFactory::instance()->createEnemy(Tag::Enemy_Tiger, 14 * 150, 2 * 150),
        GameObjFactory::instance()->createBlock(Tag::Block_TeleportExtra, -1 * 150, 5 * 150),
    };
    // 草皮
    GameObjFactory::instance()->createBlockAreaInMap(Tag::Block_Grass, 0 * 150, 8 * 150, 1, 26, this->gameObjVec_);
    // 土壤
    GameObjFactory::instance()->createBlockAreaInMap(Tag::Block_GrassUnder, 0 * 150, 9 * 150, 1, 26, this->gameObjVec_);
    GameObjFactory::instance()->createBlockAreaInMap(Tag::Block_GrassUnder, 26 * 150, 0 * 150, 10, 2, this->gameObjVec_);

    CollisionManager::instance()->clearCollisionBoxVec();
}

void TigerMap::onEnter() {
    // 切换游戏对象管理器中的对象列表为当前地图的对象列表
    MapManager::instance()->setCurrentMap("TigerMap");
    GameObjManager::instance()->switchObjVec();
    // 根据传入的Flag设置玩家位置
    switch (MapManager::instance()->getTeleportFlag()) {
    case MapManager::TeleportFlag::Extra:
        GameObjManager::instance()->getPlayer()->setBoxX(0 * 150);
        GameObjManager::instance()->getPlayer()->setBoxY(3 * 150);
        GameObjManager::instance()->getPlayer()->setSpeed(0, 0);
        break;
    default:
        throw "InitialMap::onEnter: Unknown Flag";
        break;
    }
    MapManager::instance()->setTeleportFlag(MapManager::TeleportFlag::Null);
    // BGM播放
    Mix_ResumeMusic();
    Mix_PlayMusic(ResourceManager::Instance().getMusic(MusicType::tigerBgm), -1);
}

void TigerMap::onUpdate(int delta) {
    switch (MapManager::instance()->getTeleportFlag()) {
    case MapManager::TeleportFlag::Extra:
        MapManager::instance()->switchMap("TransitionMap");
        break;
    }
}

void TigerMap::onExit() {
    Mix_HaltChannel(-1); // 停止所有音效播放
	Mix_HaltMusic(); // 停止BGM播放
}

/// CloudMap
CloudMap::CloudMap(int width, int height) : Map(width, height) {
    this->gameObjVec_ = {
       GameObjFactory::instance()->createPosterBG(Tag::Poster_BG_Cloud, width, height),
       GameObjFactory::instance()->createPoster(Tag::Poster_mainTower, 1 * 150, 7 * 150, 12 * 150, 17 * 150),
       GameObjFactory::instance()->createBlock(Tag::Block_TeleportNext, 37 * 150, 1 * 150),     // Next传送块
       GameObjFactory::instance()->createBlock(Tag::Block_TeleportPrior, 37 * 150, 19 * 150),   // Prior传送块
       GameObjFactory::instance()->createBlock(Tag::Block_SavePoint, 35 * 150, 20 * 150),       // 存档点
       GameObjFactory::instance()->createBlock(Tag::Block_SavePoint, 35 * 150, 3 * 150),       // 存档点
    };
    // 空气墙
    GameObjFactory::instance()->createBlockAreaInMap(Tag::Block_Air, 4 * 150, 9 * 150, 1, 4, this->gameObjVec_);
    // 草皮
    GameObjFactory::instance()->createBlockAreaInMap(Tag::Block_Grass, 34 * 150, 21 * 150, 2, 3, this->gameObjVec_);
    GameObjFactory::instance()->createBlockAreaInMap(Tag::Block_Grass, 34 * 150, 4 * 150, 2, 3, this->gameObjVec_);
    // 云：第一层
    GameObjFactory::instance()->createBlockAreaInMap(Tag::Block_Cloud1, 29 * 150, 20 * 150, 1, 3, this->gameObjVec_);
    GameObjFactory::instance()->createBlockAreaInMap(Tag::Block_Cloud1, 29 * 150, 19 * 150, 1, 1, this->gameObjVec_);
    GameObjFactory::instance()->createBlockAreaInMap(Tag::Block_Cloud1, 24 * 150, 17 * 150, 1, 2, this->gameObjVec_);
    GameObjFactory::instance()->createBlockAreaInMap(Tag::Block_Cloud1, 25 * 150, 18 * 150, 1, 2, this->gameObjVec_);
    GameObjFactory::instance()->createBlockAreaInMap(Tag::Block_Cloud1, 19 * 150, 16 * 150, 1, 3, this->gameObjVec_);
    GameObjFactory::instance()->createBlockAreaInMap(Tag::Block_Cloud1, 20 * 150, 15 * 150, 1, 1, this->gameObjVec_);
    GameObjFactory::instance()->createBlockAreaInMap(Tag::Block_Cloud1, 16 * 150, 14 * 150, 1, 2, this->gameObjVec_);
    GameObjFactory::instance()->createBlockAreaInMap(Tag::Block_Cloud1, 16 * 150, 13 * 150, 1, 1, this->gameObjVec_);
    GameObjFactory::instance()->createBlockAreaInMap(Tag::Block_Cloud1, 12 * 150, 12 * 150, 1, 2, this->gameObjVec_);
    GameObjFactory::instance()->createBlockAreaInMap(Tag::Block_Cloud1, 11 * 150, 11 * 150, 1, 1, this->gameObjVec_);
    GameObjFactory::instance()->createBlockAreaInMap(Tag::Block_Cloud1, 9 * 150, 10 * 150, 1, 1, this->gameObjVec_);
    // 云：第二层
    GameObjFactory::instance()->createBlockAreaInMap(Tag::Block_Cloud1, 11 * 150, 5 * 150, 1, 3, this->gameObjVec_);
    GameObjFactory::instance()->createBlockAreaInMap(Tag::Block_Cloud1, 13 * 150, 6 * 150, 1, 1, this->gameObjVec_);
    GameObjFactory::instance()->createBlockAreaInMap(Tag::Block_Cloud1, 17 * 150, 6 * 150, 1, 1, this->gameObjVec_);
    GameObjFactory::instance()->createBlockAreaInMap(Tag::Block_Cloud1, 16 * 150, 7 * 150, 1, 3, this->gameObjVec_);
    GameObjFactory::instance()->createBlockAreaInMap(Tag::Block_Cloud1, 20 * 150, 5 * 150, 1, 2, this->gameObjVec_);
    GameObjFactory::instance()->createBlockAreaInMap(Tag::Block_Cloud1, 21 * 150, 4 * 150, 1, 2, this->gameObjVec_);
    GameObjFactory::instance()->createBlockAreaInMap(Tag::Block_Cloud1, 25 * 150, 5 * 150, 1, 3, this->gameObjVec_);
    GameObjFactory::instance()->createBlockAreaInMap(Tag::Block_Cloud1, 27 * 150, 4 * 150, 1, 1, this->gameObjVec_);
    GameObjFactory::instance()->createBlockAreaInMap(Tag::Block_Cloud1, 30 * 150, 5 * 150, 1, 2, this->gameObjVec_);
    GameObjFactory::instance()->createBlockAreaInMap(Tag::Block_Cloud1, 30 * 150, 6 * 150, 1, 1, this->gameObjVec_);
    GameObjFactory::instance()->createBlockAreaInMap(Tag::Block_Cloud1, 30 * 150, 7 * 150, 1, 1, this->gameObjVec_);
    // 跳跃板
    GameObjFactory::instance()->createBlockAreaInMap(Tag::Block_JumpPad, 8 * 150, 9 * 150, 1, 1, this->gameObjVec_);
    // 死亡区
    GameObjFactory::instance()->createBlockAreaInMap(Tag::Block_Dead, 0 * 150, 24 * 150, 2, 37, this->gameObjVec_);
}

void CloudMap::onEnter() {
    MapManager::instance()->setCurrentMap("CloudMap");
    GameObjManager::instance()->switchObjVec();
    // 根据传入的Flag设置玩家位置
    switch (MapManager::instance()->getTeleportFlag()) {
    case MapManager::TeleportFlag::Prior:
        GameObjManager::instance()->getPlayer()->setBoxX(36 * 150);
        GameObjManager::instance()->getPlayer()->setBoxY(2 * 150);
        GameObjManager::instance()->getPlayer()->setSpeed(0, 0);
        break;
    case MapManager::TeleportFlag::Next:
        GameObjManager::instance()->getPlayer()->setBoxX(36 * 150);
        GameObjManager::instance()->getPlayer()->setBoxY(19 * 150);
        GameObjManager::instance()->getPlayer()->setSpeed(0, 0);
        break;
    case MapManager::TeleportFlag::Null:
        break;
    default:
        throw "CloudMap::onEnter: Unknown Flag";
        break;
    }
    MapManager::instance()->setTeleportFlag(MapManager::TeleportFlag::Null);
    // BGM播放
    Mix_ResumeMusic();
    Mix_PlayMusic(ResourceManager::Instance().getMusic(MusicType::initialBgm), -1);
}

void CloudMap::onUpdate(int delta) {
    switch (MapManager::instance()->getTeleportFlag()) {
    case MapManager::TeleportFlag::Prior:
        MapManager::instance()->switchMap("TransitionMap");
        break;
    case MapManager::TeleportFlag::Next:
        MapManager::instance()->switchMap("BossMap");
        break;
    }
}

void CloudMap::onExit() {
    Mix_HaltChannel(-1); // 停止所有音效播放
    Mix_HaltMusic(); // 停止BGM播放
}

/// BossMap
BossMap::BossMap(int width, int height) : Map(width, height)
{
    this->gameObjVec_ = {
        GameObjFactory::instance()->createPosterBG(Tag::Poster_BG_Boss, width, height),
        GameObjFactory::instance()->createEnemy(Tag::Enemy_Boss, 28 * 150, 12 * 150),
        GameObjFactory::instance()->createBlock(Tag::Block_TeleportPrior, -1 * 150, 16 * 150),
    };
    // 草皮
    GameObjFactory::instance()->createBlockAreaInMap(Tag::Block_Grass, 0 * 150, 19 * 150, 1, 9, this->gameObjVec_);
    GameObjFactory::instance()->createBlockAreaInMap(Tag::Block_Grass, 10 * 150, 19 * 150, 1, 8, this->gameObjVec_);
    GameObjFactory::instance()->createBlockAreaInMap(Tag::Block_Grass, 20 * 150, 19 * 150, 1, 8, this->gameObjVec_);
    GameObjFactory::instance()->createBlockAreaInMap(Tag::Block_Grass, 3 * 150, 15 * 150, 1, 4, this->gameObjVec_);
    GameObjFactory::instance()->createBlockAreaInMap(Tag::Block_Grass, 21 * 150, 15 * 150, 1, 5, this->gameObjVec_);
    GameObjFactory::instance()->createBlockAreaInMap(Tag::Block_Grass, 4 * 150, 10 * 150, 1, 8, this->gameObjVec_);
    // 土壤
    GameObjFactory::instance()->createBlockAreaInMap(Tag::Block_GrassUnder, 0 * 150, 20 * 150, 1, 28, this->gameObjVec_);
    // 云
    GameObjFactory::instance()->createBlockAreaInMap(Tag::Block_Cloud1, 12 * 150, 15 * 150, 1, 5, this->gameObjVec_);
    GameObjFactory::instance()->createBlockAreaInMap(Tag::Block_Cloud1, 15 * 150, 11 * 150, 1, 1, this->gameObjVec_);
    GameObjFactory::instance()->createBlockAreaInMap(Tag::Block_Cloud1, 17 * 150, 12 * 150, 1, 1, this->gameObjVec_);
    GameObjFactory::instance()->createBlockAreaInMap(Tag::Block_Cloud1, 19 * 150, 13 * 150, 1, 1, this->gameObjVec_);
    GameObjFactory::instance()->createBlockAreaInMap(Tag::Block_Cloud1, 15 * 150, 5 * 150, 1, 2, this->gameObjVec_);
    GameObjFactory::instance()->createBlockAreaInMap(Tag::Block_Cloud1, 19 * 150, 5 * 150, 1, 3, this->gameObjVec_);
    GameObjFactory::instance()->createBlockAreaInMap(Tag::Block_Cloud1, 21 * 150, 6 * 150, 1, 1, this->gameObjVec_);
    GameObjFactory::instance()->createBlockAreaInMap(Tag::Block_Cloud1, 24 * 150, 5 * 150, 1, 4, this->gameObjVec_);
    GameObjFactory::instance()->createBlockAreaInMap(Tag::Block_Cloud1, 26 * 150, 6 * 150, 1, 2, this->gameObjVec_);
    GameObjFactory::instance()->createBlockAreaInMap(Tag::Block_Cloud1, 27 * 150, 7 * 150, 1, 1, this->gameObjVec_);
    // 跳跃板
    GameObjFactory::instance()->createBlockAreaInMap(Tag::Block_JumpPad, 8 * 150, 19 * 150, 1, 2, this->gameObjVec_);
    GameObjFactory::instance()->createBlockAreaInMap(Tag::Block_JumpPad, 18 * 150, 19 * 150, 1, 2, this->gameObjVec_);
    GameObjFactory::instance()->createBlockAreaInMap(Tag::Block_JumpPad, 2 * 150, 15 * 150, 1, 1, this->gameObjVec_);
    GameObjFactory::instance()->createBlockAreaInMap(Tag::Block_JumpPad, 12 * 150, 10 * 150, 1, 1, this->gameObjVec_);
    // 死亡区
    GameObjFactory::instance()->createBlockAreaInMap(Tag::Block_Dead, 0 * 150, 25 * 150, 2, 36, this->gameObjVec_);
    CollisionManager::instance()->clearCollisionBoxVec();
}

void BossMap::onEnter() {
    // 切换游戏对象管理器中的对象列表为当前地图的对象列表
    MapManager::instance()->setCurrentMap("BossMap");
    GameObjManager::instance()->switchObjVec();
    // 根据传入的Flag设置玩家位置
    switch (MapManager::instance()->getTeleportFlag()) {
    case MapManager::TeleportFlag::Next:
        GameObjManager::instance()->getPlayer()->setBoxX(0 * 150);
        GameObjManager::instance()->getPlayer()->setBoxY(17 * 150);
        GameObjManager::instance()->getPlayer()->setSpeed(0, 0);
        break;
    default:
        throw "InitialMap::onEnter: Unknown Flag";
        break;
    }
    MapManager::instance()->setTeleportFlag(MapManager::TeleportFlag::Null);
	// BGM播放
    Mix_ResumeMusic();
	Mix_PlayMusic(ResourceManager::Instance().getMusic(MusicType::bossBgm), -1);
}

void BossMap::onUpdate(int delta) {
    switch (MapManager::instance()->getTeleportFlag()) {
    case MapManager::TeleportFlag::Prior:
        MapManager::instance()->switchMap("CloudMap");
        break;
    }
}

void BossMap::onExit() {
    Mix_HaltChannel(-1); // 停止所有音效播放
	Mix_HaltMusic(); // 停止BGM播放
}


