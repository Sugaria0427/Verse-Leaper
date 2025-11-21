#include"Renderer.h"
#include"SceneManager.h"
#include"Panel.h"
#include "SDLInitException.h"
#include "MouseInput.h"
#undef main

#define WIDTH 1280
#define HEIGHT 720
#define FRAME_RATE 50
#define FRAME_TIME 1000 / FRAME_RATE

int main() {
    Panel::Instance().initSDL();

    Panel::Instance().initAudioAndScenes();

    MouseInput msInput = { NULL, NULL };    // 初始化鼠标坐标
    
    Uint64 start, end;
    int delay;
    int delta = 0;
    while (Panel::Instance().isRunning()) 
    {
        start = SDL_GetTicks64();   // 记录帧开始时间

        SceneManager::Instance()->handleEvent();            // 处理事件

        SceneManager::Instance()->handleState(msInput);     // 处理状态

        SceneManager::Instance()->update(delta);            // 更新场景

        Renderer::Instance().draw(SceneManager::Instance()->getCurrentScene());// 渲染场景

        SDL_RenderPresent(Panel::Instance().getSDLRenderer());// 更新屏幕
        
        // 帧率控制
        end = SDL_GetTicks64();
        delay = FRAME_TIME - (end - start);
        if (delay > 0){
            SDL_Delay(delay);
        }
        delta = (end - start) + (delay > 0 ? delay : 0);
    }

    // 退出
    Mix_Quit();
    SDL_Quit();
    return 0;
}