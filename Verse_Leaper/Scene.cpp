#include "Scene.h"

// ctor & dtor
Scene::Scene(Image* backgroundImage, std::vector<Button*>& btnVec)
    : backgroundImage(backgroundImage), buttonVec(btnVec) {
}

Scene::~Scene() {
    delete backgroundImage;
    backgroundImage = nullptr;
    for (Button* btn : buttonVec) {
        delete btn;
        btn = nullptr;
    }
    buttonVec.clear();
}

void Scene::draw(SDL_Renderer* SDL_renderer) {
    drawBackground(SDL_renderer);
    drawButtonVec(SDL_renderer);
}

void Scene::drawBackground(SDL_Renderer* SDL_renderer) {
    SDL_RenderCopy(SDL_renderer, this->getBackgroundImage()->getImgTexture(), NULL, NULL);
}

void Scene::drawButtonVec(SDL_Renderer* SDL_renderer)
{
    for (Button* btn : this->buttonVec) {
        btn->draw(SDL_renderer);
    }
}