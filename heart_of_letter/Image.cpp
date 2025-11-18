#include "Image.h"
#include <stdexcept>
#include "Panel.h"

Image::Image(const char* filePath) : imgTexture(nullptr), imgSurf(nullptr) {
    imgSurf = SDL_LoadBMP(filePath);
    if (NULL == imgSurf) {
        SDL_Log("SDL_LoadBMP failed: %s", filePath);
    }
    imgTexture = SDL_CreateTextureFromSurface(Panel::Instance().getSDLRenderer(), imgSurf);
}