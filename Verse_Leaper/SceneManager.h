#pragma once
#include"Scene.h"

class SceneManager
{
public:
    enum class SceneType
    {
        Menu,
        Game,
        Option
    };
private:
    SceneManager() {}
    ~SceneManager() {
        currentScene = nullptr;
    }
public:
    static SceneManager* Instance() {
        static SceneManager* instance = new SceneManager();
        return instance;
    }
    void initCurrentScene(Scene* scene) { 
        currentScene = scene; 
        currentScene->onEnter();
    }
public:
    // getters & setters
    Scene* getCurrentScene() { return currentScene; }
    void setCurrentScene(Scene* scene);

    void switchTo(SceneType sceneType);
    void handleEvent(SDL_Event &event);
    void handleState(MouseInput &msInput);
    void update(int delta);
private:
    static SceneManager* instance;
    Scene* currentScene;
};

