#include "Scene.h"

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