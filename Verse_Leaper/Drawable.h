#pragma once
#include<SDL.h>
class Drawable
{
public:
    virtual ~Drawable() = default;
    virtual void draw(SDL_Renderer* SDL_renderer) = 0;
};

