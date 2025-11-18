#pragma once
#include"Scene.h"
#include"SceneManager.h"

class MenuScene :
    public Scene
{
public:
    MenuScene(Image* backgroundImage, std::vector<Button*>& btnVec) 
        : Scene(backgroundImage, btnVec) {}
    void handleEvent(SDL_Event &event) override;
    void handleState(MouseInput &msInput) override;
    void update(int delta) override;
    void onEnter() override;
    void onExit() override;
};