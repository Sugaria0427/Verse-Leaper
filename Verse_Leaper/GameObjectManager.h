#pragma once
#include <vector>

class GameObject;

class GameObjManager
{
public:
    // 单例模式获取实例对象
    static GameObjManager* instance();
    std::vector<GameObject*> getVec() { return gameObjVec; }
    GameObject* getPlayer() { return gameObjVec[0]; }
    
    void initPlayer(GameObject* player) { gameObjVec[0] = player; }
    
    void addGameObj(GameObject* obj) { gameObjVec.push_back(obj); }

    void clearVecWithoutPlayer();
    void clearVec();

    void switchObjVec();

    bool hasInitPlayer() const { return hasInitPlayer_; }
    void setInitPlayer(bool hasInitPlayer) { hasInitPlayer_ = hasInitPlayer; }
private:
    GameObjManager() {
        GameObject* player = nullptr;
        gameObjVec.push_back(player);
    }
    ~GameObjManager() = default;
    static GameObjManager* gameObjManager;
    std::vector<GameObject*> gameObjVec;
    bool hasInitPlayer_ = false;
};

