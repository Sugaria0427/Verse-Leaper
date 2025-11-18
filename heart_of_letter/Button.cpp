#include "Button.h"

extern Camera* camera;

void Button::draw(SDL_Renderer* SDL_renderer) {
    if (isHover) {  //绘制hover状态下按钮
        SDL_Texture* buttonTexture = buttonImage->getImgTexture();

        SDL_Rect* destRect = getWorldRect();

        int renderResult = SDL_RenderCopy(SDL_renderer, buttonTexture, NULL, destRect);
        delete destRect;
        // 创建失败
        if (renderResult != 0) {
            SDL_Log("SDL_RenderCopy failed: %s", SDL_GetError());
        }
    }
    else {  //绘制非hover状态下按钮

    }
    
}

bool Button::isMouseOn(MouseInput& msInput)
{
    isHover = this->isPointOn(msInput.mouseX, msInput.mouseY);
    return isHover;
}

void Button::updateButtonHover(MouseInput& msInput, std::vector<Button*>& buttons) {
    for (Button* button : buttons) {
        button->isMouseOn(msInput);
    }
}

Button::Name Button::findHoverInVec(std::vector<Button*>& buttons)
{
    for (Button* btn : buttons) {
        if (btn->isHover) {
            return btn->name;
        }
    }
    return Name::Null;
}
