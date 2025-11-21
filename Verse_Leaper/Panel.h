#pragma once
#include<SDL.h>
#include<SDL_mixer.h>
#include<iostream>

class Camera;

class Panel
{
private:
    Panel();
    ~Panel();

public:
    static Panel& Instance();

    void initSDL();

    void initAudioAndScenes();

public:
    SDL_Renderer* getSDLRenderer() const;
    SDL_Window* getSDLWindow() const;
    Camera* getCamera() const;
    SDL_Event& getEvent();
    bool isRunning() const;
    void setRunning(bool running);

private:
    SDL_Window* win = nullptr;
    SDL_Renderer* SDL_renderer = nullptr;
    Camera* camera = nullptr;
    SDL_Event event;
    bool isRunning_ = true;

private:
    // 初始化SDL子函数
    void initSDLAudio();
    void initSDLWindow();
    void initSDLRenderer();

private:
    // 初始化音频和场景子函数
    void initAudio();
    void creatScenes();
    void creatMenuScene();
    void creatGameScene();
    void creatOptionScene();
};

