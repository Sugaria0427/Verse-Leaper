#pragma once
#include"Scene.h"
#include "Updatable.h"
#include <unordered_map>

enum class SceneType
{
    Menu,
    Game,
    Option
};

class SceneManager : public Updatable
{
private:
    SceneManager();
    ~SceneManager();

public:
    static SceneManager* Instance();

    void update(int delta) override;

    void setAndEnterCurrentScene(SceneType scene);

    void switchTo(SceneType sceneType);

    void handleEvent();

    void handleState(MouseInput &msInput);

public:
    Scene* getCurrentScene() { return currentScene; }
    void setCurrentScene(Scene* scene);

    Scene* getScene(SceneType sceneType);
    void addScene(SceneType sceneType, Scene* scene);

private:
    static SceneManager* instance;
    Scene* currentScene = nullptr;
    std::unordered_map<SceneType, Scene*> scenesPool;
};