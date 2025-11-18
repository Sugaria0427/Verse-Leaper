#include "SceneManager.h"

extern Scene* menuScene;
extern Scene* gameScene;
extern Scene* optionScene;

void SceneManager::setCurrentScene(Scene* scene)
{
    currentScene = scene;
}

void SceneManager::switchTo(SceneType sceneType)
{
    switch (sceneType) {
    case SceneType::Menu:
        currentScene->onExit();
        currentScene = menuScene;
        currentScene->onEnter();
        break;
    case SceneType::Game:
        currentScene->onExit();
        currentScene = gameScene;
        currentScene->onEnter();
        break;
    case SceneType::Option:
        currentScene->onExit();
        currentScene = optionScene;

        break;
    }
}

void SceneManager::handleEvent(SDL_Event& event)
{
    this->currentScene->handleEvent(event);
}

void SceneManager::handleState(MouseInput& msInput)
{
    this->currentScene->handleState(msInput);
}

void SceneManager::update(int delta) {
    this->currentScene->update(delta);
}

