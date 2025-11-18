#pragma once
#include <vector>
#include <SDL.h>
#include"Image.h"

class Atlas {
public:
    // ctor & dtor
    Atlas(const char* path, int size, SDL_RendererFlip initFlip = SDL_FLIP_NONE);
    ~Atlas();
    // getters & setters
    int getSize() const { return size; }
    std::vector<Image*> getFrameList() { return frameList; }
    void setFlip(SDL_RendererFlip flip) { flipMode = flip; }
    SDL_RendererFlip getFlip() const { return flipMode; }
private:
    std::vector<Image*> frameList;
    int size = 0;
    SDL_RendererFlip flipMode;
};
