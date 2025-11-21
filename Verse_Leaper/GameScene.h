#pragma once
#include <vector>
#include "Scene.h"

class DialogueBox;

class GameObject;

class GameScene :
    public Scene
{
private:
    DialogueBox* dialogueBox = nullptr;
    bool isCameraFollowing_ = true;

public:
    GameScene(Image* backgroundImage, std::vector<Button*>& btnVec)
        : Scene(backgroundImage, btnVec) {}
    ~GameScene() = default;
    
public:
    void draw(SDL_Renderer* SDL_renderer) override;
    void update(int delta) override;
    void handleEvent(SDL_Event& event) override;
    void handleState(MouseInput& msInput) override;
    void onEnter() override;
    void onExit() override;

private:
    // 绘制子函数
    void drawGameObj(SDL_Renderer* SDL_renderer);
    void drawBackground(SDL_Renderer* SDL_renderer) override;

private:
    // 更新子函数
    void updateCameraPosition(int delta) const;

private:
    // 事件处理子函数
    void handleMouseButtonUpEvent(SDL_Event& event);
    void tryTriggerMouseInteractiveObjs(SDL_Event& event);
    void triggerBell(GameObject* obj);
    void tryUseArrow();
    void tryUseSword();
    void handleMouseWheelEvent(SDL_Event& event);
    void handleKeyDownEvent(SDL_Event& event);

private:
    // 状态处理子函数
    void handlePlayerMovementState(const Uint8* kbState);
    void handleCameraMovementState(const Uint8* kbState);
};