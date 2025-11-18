#pragma once
#include<SDL.h>

class Image
{
public:
    // ctor & dtor
    Image(const char* filePath);
    ~Image() {
        SDL_DestroyTexture(imgTexture);
        SDL_FreeSurface(this->imgSurf);
    }
    SDL_Texture* getImgTexture() { return imgTexture; }
private:
    SDL_Texture* imgTexture;
    SDL_Surface* imgSurf;
};


