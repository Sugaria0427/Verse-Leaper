#include "MenuScene.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "Panel.h"
#include "MouseInput.h"

void MenuScene::handleEvent(SDL_Event& event)
{
    MouseInput mouseInput;
    switch (event.type) {
    case SDL_MOUSEBUTTONDOWN:
        if (event.button.button == SDL_BUTTON_LEFT && Button::findHoverButton(this->buttonVec) != Button::Name::Null) {
			Mix_PlayChannel(-1, ResourceManager::Instance().getSound(SoundType::button), 0);
        }
		break;
    case SDL_MOUSEBUTTONUP:
        if (event.button.button == SDL_BUTTON_LEFT) {
            switch (Button::findHoverButton(this->buttonVec)) {
            case Button::Name::menu_Start:
            case Button::Name::menu_Continue:
                SceneManager::Instance()->switchTo(SceneType::Game);
                break;
            case Button::Name::menu_Option:
                SceneManager::Instance()->switchTo(SceneType::Option);
                break;
            case Button::Name::menu_Quit:
                Panel::Instance().setRunning(false);
                break;
            case Button::Name::Null:
                break;
            }
        }
        break;
    }
}

void MenuScene::handleState(MouseInput& msInput)
{
    // 获取状态
    SDL_GetMouseState(&(msInput.mouseX), &(msInput.mouseY));
    const Uint8* kbState = SDL_GetKeyboardState(NULL);
    // 处理状态
    Button::updateButtonsHover(msInput, buttonVec);
}

void MenuScene::update(int delta) {
}

void MenuScene::onEnter(){
    Mix_ResumeMusic();
    Mix_PlayMusic(ResourceManager::Instance().getMusic(MusicType::menuBgm), -1);
}

void MenuScene::onExit() {
    Mix_HaltMusic();
}