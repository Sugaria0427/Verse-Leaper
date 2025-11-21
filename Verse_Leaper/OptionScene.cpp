#include "OptionScene.h"
#include "SceneManager.h"
#include "MouseInput.h"

void OptionScene::handleEvent(SDL_Event& event)
{
    switch (event.type) {
        // 鼠标
    case SDL_MOUSEBUTTONDOWN:
        break;
    case SDL_MOUSEBUTTONUP:
        SceneManager::Instance()->switchTo(SceneType::Menu);
        break;
    }
}

void OptionScene::handleState(MouseInput& msInput)
{
    // 获取状态
    SDL_GetMouseState(&(msInput.mouseX), &(msInput.mouseY));
    // 处理状态
}

void OptionScene::onEnter(){
}

void OptionScene::onExit(){
}
