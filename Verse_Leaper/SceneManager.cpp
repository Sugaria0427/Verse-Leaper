#include "SceneManager.h"
#include "PoolNotFoundException.h"
#include "Panel.h"

SceneManager::SceneManager() {}

SceneManager::~SceneManager() {
    currentScene = nullptr;
}

SceneManager* SceneManager::Instance() {
    static SceneManager* instance = new SceneManager();
    return instance;
}

void SceneManager::setAndEnterCurrentScene(SceneType scene) {
    currentScene = getScene(scene);
    currentScene->onEnter();
}

void SceneManager::setCurrentScene(Scene* scene)
{
    currentScene = scene;
}

Scene* SceneManager::getScene(SceneType sceneType)
{
    if (this->scenesPool.find(sceneType) != this->scenesPool.end()) {
        return this->scenesPool[sceneType];
    }
    else 
        throw new PoolNotFoundException("SceneManager::getScene - Scene not found in pool");
}

void SceneManager::addScene(SceneType sceneType, Scene* scene)
{
    this->scenesPool[sceneType] = scene;
}

void SceneManager::switchTo(SceneType sceneType)
{
    switch (sceneType) {
    case SceneType::Menu:
        currentScene->onExit();
        setCurrentScene(getScene(SceneType::Menu));
        currentScene->onEnter();
        break;
    case SceneType::Game:
        currentScene->onExit();
        setCurrentScene(getScene(SceneType::Game));
        currentScene->onEnter();
        break;
    case SceneType::Option:
        currentScene->onExit();
        setCurrentScene(getScene(SceneType::Option));
        break;
    }
}

void SceneManager::handleEvent()
{
    while (SDL_PollEvent(&Panel::Instance().getEvent()))    // 轮询SDL事件
    {
        if (SDL_QUIT == Panel::Instance().getEvent().type)
            Panel::Instance().setRunning(false);                        // 若接收到退出事件，则将运行标志设为false

        this->currentScene->handleEvent(Panel::Instance().getEvent());  // 将事件传递给当前场景进行处理
    }
}

void SceneManager::handleState(MouseInput& msInput)
{
    this->currentScene->handleState(msInput);
}

void SceneManager::update(int delta) {
    this->currentScene->update(delta);
}

