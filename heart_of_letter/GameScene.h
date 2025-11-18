#pragma once
#include <vector>
#include "SceneManager.h"
#include "GameObjectManager.h"
#include "Player.h"
#include "Npc.h"
#include "Block.h"
#include "Enemy.h"
#include "DropItem.h"
#include "CollisionManager.h"
#include "MapManager.h"
#include "DialogueBox.h"
#include "GameObjFactory.h"

class GameScene :
    public Scene
{
public:
    GameScene(Image* backgroundImage, std::vector<Button*>& btnVec)
        : Scene(backgroundImage, btnVec) {}
    ~GameScene() = default;
    // 接口
    void draw(SDL_Renderer* SDL_renderer) override;
    void update(int delta) override;
    // 处理状态与事件
    void handleEvent(SDL_Event& event) override;
    void handleState(MouseInput& msInput) override;
    // 进入与退出
    void onEnter() override;
    void onExit() override;
private:
    DialogueBox* dialogueBox = nullptr;
    bool isCameraFollowing_ = true;
    bool isRunning = false;
    bool isFalling = false;
    int doubleJumpCount = 0;
    void drawGameObj(SDL_Renderer* SDL_renderer);
    void drawBackground(SDL_Renderer* SDL_renderer) override;
};