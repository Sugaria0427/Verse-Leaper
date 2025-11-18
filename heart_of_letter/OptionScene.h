#pragma once
#include"Scene.h"
#include"SceneManager.h"
class OptionScene : 
    public Scene
{
public:
    OptionScene(Image* backgroundImage, std::vector<Button*>& btnVec) 
        : Scene(backgroundImage, btnVec) {}
    void handleEvent(SDL_Event& event) override;
    void handleState(MouseInput& msInput) override;
    void onEnter() override;
    void onExit() override;
};

