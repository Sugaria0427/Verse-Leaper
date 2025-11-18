#include "GameObjectManager.h"
#include "Player.h"
#include "ResourceManager.h"

GameObjManager* GameObjManager::gameObjManager = nullptr;

GameObjManager* GameObjManager::instance() {
    if (!gameObjManager) {
        gameObjManager = new GameObjManager();
    }
    return gameObjManager;
}

void GameObjManager::clearVecWithoutPlayer()
{
    GameObject* player = nullptr;
    for (GameObject* obj : gameObjVec) {
        if (obj) {
            if (obj->getTag() == Tag::Player) player = obj;
            else obj->beDeleted();
        }
    }
    gameObjVec.clear();
    gameObjVec.push_back(player);
}

void GameObjManager::clearVec()
{
    for (GameObject* obj : gameObjVec) {
        if (obj) obj->beDeleted();
    }
    gameObjVec.clear();
    this->clearVecWithoutPlayer();
}

void GameObjManager::switchObjVec() {
    // 清理现有对象
    CollisionManager::instance()->clearCollisionBoxVec();
    this->clearVecWithoutPlayer();
    if (this->getPlayer() == nullptr) {
        Player* palyer = new Player(Tag::Player,
            new Animation(ResourceManager::Instance().getAtlas(AtlasType::atlasPlayerIdleRight), 100),
            new Animation(ResourceManager::Instance().getAtlas(AtlasType::atlasHitBoxRight), 100),
            new Animation(ResourceManager::Instance().getAtlas(AtlasType::atlasArrowRight), 100),
            new Box(0, 0, 110, 230),
            10,
            1,
            10
        );
        GameObjManager::instance()->initPlayer(palyer);
        GameObjManager::instance()->setInitPlayer(true);
    }
    else {
        Player* player = dynamic_cast<Player*>(GameObjManager::instance()->getPlayer()); 
        player->initPlayerCollisionBox();
    }
    // 更换地图对象
    std::vector<GameObject*> vecSrc = MapManager::instance()->getCurrentMap()->getGameObjVec();
    for (GameObject* objSrc : vecSrc) {
        GameObject* objDst = objSrc->clone();
        this->gameObjVec.push_back(objDst);
    }
}

