#include "Renderer.h"
#include "Panel.h"

Renderer& Renderer::Instance()
{
    static Renderer instance;
    return instance;
}

void Renderer::draw(Drawable* object)
{
    object->draw(Panel::Instance().getSDLRenderer()); 
}

void Renderer::draw(std::vector<Drawable*> objVec)
{
    for (Drawable* obj : objVec) {
        obj->draw(Panel::Instance().getSDLRenderer());
    }
}