#pragma once
#include<SDL.h>
#include<SDL_mixer.h>
#include "SDLInitException.h"

class Camera;

class Panel
{
private:
    Panel();
    ~Panel();

public:
    static Panel& Instance() {
        static Panel panel;
        return panel;
    }

public:
    void initSDL();
private:
    void initSDLAudio();
    void initSDLWindow();
    void initSDLRenderer();

public:
    SDL_Renderer* getSDLRenderer() const { return SDL_renderer; }
    SDL_Window* getSDLWindow() const { return win; }
    Camera* getCamera() const { return camera; }
    SDL_Event& getEvent() { return event; }
private:
    SDL_Window* win = nullptr;
    SDL_Renderer* SDL_renderer = nullptr;
    Camera* camera = nullptr;
    SDL_Event event;
};
