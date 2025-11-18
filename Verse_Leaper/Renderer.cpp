#include "Renderer.h"

void Renderer::draw(SDL_Renderer* SDL_renderer, Drawable* object)
{
    object->draw(SDL_renderer); 
}

void Renderer::draw(SDL_Renderer* SDL_renderer, std::vector<Drawable*> objVec)
{
    for (Drawable* obj : objVec) {
        obj->draw(SDL_renderer);
    }
}

void Renderer::drawImage()
{
}