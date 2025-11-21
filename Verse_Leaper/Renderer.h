#pragma once
#include <SDL.h>
#include <vector>
#include "Drawable.h"

class Renderer
{
private:
    Renderer() {}
    ~Renderer() = default;
public:
    static Renderer& Instance();

    void draw(Drawable* Object);
    void draw(std::vector<Drawable*> ObjVec);
};

