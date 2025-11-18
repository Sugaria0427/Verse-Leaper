#pragma once
#include<SDL.h>
#include <vector>
#include"Drawable.h"

class Renderer
{
public:
    Renderer() {}
    ~Renderer() = default;
    void draw(SDL_Renderer* SDL_renderer, Drawable* Object);
    void draw(SDL_Renderer* SDL_renderer, std::vector<Drawable*> ObjVec);
    
private:
    void drawImage();
};

