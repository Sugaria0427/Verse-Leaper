#include "Panel.h"
#include "Camera.h"

Panel::Panel() {
    camera = new Camera();
}

Panel::~Panel() {
    SDL_DestroyWindow(win);
    SDL_DestroyRenderer(SDL_renderer);
}

void Panel::initSDL() {
    initSDLAudio();
    initSDLWindow();
    initSDLRenderer();
}

void Panel::initSDLAudio() {
    SDL_Init(SDL_INIT_EVERYTHING);
    Mix_Init(MIX_INIT_MP3);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    Mix_AllocateChannels(32);
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        SDL_Log("Init failed: %s", SDL_GetError());
        throw SDLInitException("Audio init failed");
    }
}

void Panel::initSDLWindow()
{
    win = SDL_CreateWindow("heart of letter", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
        camera->getWidth(), camera->getHeight(), 0
    );
    if (!win) {
        SDL_Log("CreateWindow failed: %s", SDL_GetError());
        throw SDLInitException("CreateWindow failed");
    }
}

void Panel::initSDLRenderer()
{
    SDL_renderer = SDL_CreateRenderer(win, -1, 0);
    if (NULL == SDL_renderer) {
        SDL_Log("SDL_CreateRenderer failed: %s", SDL_GetError());
        throw SDLInitException("SDL_CreateRenderer failed");
    }
}
