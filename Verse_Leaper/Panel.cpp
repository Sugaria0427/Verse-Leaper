#include "Panel.h"
#include "Camera.h"
#include "SDLInitException.h"
#include "MenuScene.h"
#include "GameScene.h"
#include "OptionScene.h"
#include "SceneManager.h"

Panel::Panel() : event{}, camera{new Camera()} {}

Panel::~Panel() {
    SDL_DestroyWindow(win);
    SDL_DestroyRenderer(SDL_renderer);
}

Panel& Panel::Instance() {
    static Panel panel;
    return panel;
}

void Panel::initSDL() {
    try {
        initSDLAudio();
        initSDLWindow();
        initSDLRenderer();
    }
    catch (const SDLInitException& e) {
        std::cout << e.what() << std::endl;
        Panel::Instance().setRunning(false);    // 初始化失败，设置运行状态为false
    }
}

void Panel::initAudioAndScenes()
{
    initAudio();
    creatScenes();
    SceneManager::Instance()->setAndEnterCurrentScene(SceneType::Menu);
}

SDL_Renderer* Panel::getSDLRenderer() const { return SDL_renderer; }

SDL_Window* Panel::getSDLWindow() const { return win; }

Camera* Panel::getCamera() const { return camera; }

SDL_Event& Panel::getEvent() { return event; }

bool Panel::isRunning() const { return isRunning_; }

void Panel::setRunning(bool running) { isRunning_ = running; }

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

void Panel::initAudio()
{
    Mix_VolumeMusic(128);

    ResourceManager::Instance().initMusic();

    ResourceManager::Instance().initSound();

    ResourceManager::Instance().initDialogue();
}

void Panel::creatScenes()
{
    creatMenuScene();
    creatGameScene();
    creatOptionScene();
}

void Panel::creatMenuScene()
{
    std::vector<Button*> menuButtonVec = {
           new Button(567, 357, 159, 53, Button::Name::menu_Continue, new Image("image\\menu_continue.bmp")),
           new Button(567, 415, 158, 55, Button::Name::menu_Start, new Image("image\\menu_start.bmp")),
           new Button(567, 474, 158, 53, Button::Name::menu_Option, new Image("image\\menu_option.bmp")),
           new Button(567, 532, 158, 53, Button::Name::menu_Quit, new Image("image\\menu_quit.bmp"))
    };
    Scene* menuScene = new MenuScene(new Image("image\\MenuBackground.bmp"), menuButtonVec);
    SceneManager::Instance()->addScene(SceneType::Menu, menuScene);
}

void Panel::creatGameScene()
{
    ResourceManager::Instance().initAtlas();

    std::vector<Button*> gameButtonVec = {
        new Button(1180, 0, 100, 100, Button::Name::menu_Continue, new Image("image\\menu_continue.bmp"))
    };
    Scene* gameScene = new GameScene(new Image("image\\GameBackground.bmp"), gameButtonVec);
    SceneManager::Instance()->addScene(SceneType::Game, gameScene);
}

void Panel::creatOptionScene()
{
    std::vector<Button*> optionButtonVec = {};
    Scene* optionScene = new OptionScene(new Image("image\\OptionBackground.bmp"), optionButtonVec);
    SceneManager::Instance()->addScene(SceneType::Option, optionScene);
}