#include"mainHead.h"

int main() {
    try {
        Panel::Instance().initSDL();
    }
    catch (const SDLInitException& e) {
        std::cout << e.what() << std::endl;
    }
    initAudioAndScenes();
    renderer = new Renderer();
    MouseInput msInput = { NULL, NULL };    // 初始化鼠标坐标
    
    Uint64 start, end;
    int delay;
    int delta = 0;
    // 游戏主体
    while (running) {
        start = SDL_GetTicks64();
        // 获取并处理事件
        while (SDL_PollEvent(&Panel::Instance().getEvent())) {
            if (SDL_QUIT == Panel::Instance().getEvent().type) {
                running = false;
            }
            SceneManager::Instance()->handleEvent(Panel::Instance().getEvent());
        }
        // 获取并处理状态
        SceneManager::Instance()->handleState(msInput);

        // 更新
        SceneManager::Instance()->update(delta);

        // 渲染
        renderer->draw(Panel::Instance().getSDLRenderer(), SceneManager::Instance()->getCurrentScene());  // 渲染场景
        SDL_RenderPresent(Panel::Instance().getSDLRenderer());    // 更新窗口显示
        
        // 帧率控制
        end = SDL_GetTicks64();
        delay = FRAME_TIME - (end - start);
        if (delay > 0){
            SDL_Delay(delay);
        }
        delta = (end - start) + (delay > 0 ? delay : 0);
    }

    // 销毁
    delete renderer;
    delete menuScene;
    delete gameScene;
    // 退出
    Mix_Quit();
    SDL_Quit();
    return 0;
}


static void initAudioAndScenes() {
    initAudio();
    creatScenes();
    SceneManager::Instance()->initCurrentScene(menuScene);
}

void initAudio()
{
    Mix_VolumeMusic(128);

    ResourceManager::Instance().initMusic();

    ResourceManager::Instance().initSound();

    dialogueVec_giveArrow = {
        Mix_LoadWAV("dialogue\\giveArrow\\FirstSuShi01.wav"),
        Mix_LoadWAV("empty"),
        Mix_LoadWAV("dialogue\\giveArrow\\FirstSuShi02.wav"),
        Mix_LoadWAV("empty"),
        Mix_LoadWAV("dialogue\\giveArrow\\FirstSuShi03.wav")
    };
    dialogueVec_alcohol = {
        Mix_LoadWAV("empty"),
        Mix_LoadWAV("dialogue\\alcohol\\SecondSuShi01.wav"),
        Mix_LoadWAV("empty"),
        Mix_LoadWAV("dialogue\\alcohol\\SecondSuShi02.wav"),
        Mix_LoadWAV("empty")
    };
    dialogueVec_OldMan = {
        Mix_LoadWAV("dialogue\\oldMan\\Oldman01.wav"),
        Mix_LoadWAV("empty"),
        Mix_LoadWAV("empty"),
        Mix_LoadWAV("dialogue\\oldMan\\Oldman02.wav"),
        Mix_LoadWAV("empty"),
        Mix_LoadWAV("dialogue\\oldMan\\Oldman03.wav")
    };
    dialogueVec_Young = {
        Mix_LoadWAV("dialogue\\young\\Taishou01.wav"),
        Mix_LoadWAV("empty"),
        Mix_LoadWAV("dialogue\\young\\Taishou02.wav"),
        Mix_LoadWAV("empty"),
        Mix_LoadWAV("dialogue\\young\\Taishou03.wav"),
        Mix_LoadWAV("empty"),
        Mix_LoadWAV("dialogue\\young\\Taishou04.wav"),
    };
}

void creatScenes()
{
    creatMenuScene();
    creatGameScene();
    creatOptionScene();
}

void creatMenuScene()
{
    std::vector<Button*> menuButtonVec = {
        new Button(567, 357, 159, 53, Button::Name::menu_Continue, new Image("image\\menu_continue.bmp")),
        new Button(567, 415, 158, 55, Button::Name::menu_Start, new Image("image\\menu_start.bmp")),
        new Button(567, 474, 158, 53, Button::Name::menu_Option, new Image("image\\menu_option.bmp")),
        new Button(567, 532, 158, 53, Button::Name::menu_Quit, new Image("image\\menu_quit.bmp"))
    };
    menuScene = new MenuScene(new Image("image\\MenuBackground.bmp"), menuButtonVec);
}

void creatGameScene()
{
    ResourceManager::Instance().initAtlas();

    std::vector<Button*> gameButtonVec = {
        new Button(1180, 0, 100, 100, Button::Name::menu_Continue, new Image("image\\menu_continue.bmp"))
    };
    gameScene = new GameScene(new Image("image\\GameBackground.bmp"), gameButtonVec);
}

void creatOptionScene()
{
    std::vector<Button*> optionButtonVec = {};
    optionScene = new OptionScene(new Image("image\\OptionBackground.bmp"), optionButtonVec);
}
