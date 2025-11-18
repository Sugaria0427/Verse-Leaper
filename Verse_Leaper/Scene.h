#pragma once
#include<SDL.h>
#include<SDL_mixer.h>
#include"Drawable.h"
#include"Image.h"
#include"Button.h"
#include"Updatable.h"
#include"Camera.h"
#include"ResourceManager.h"

class Scene : public Drawable, public Updatable
{
public:
    // ctor & dtor
    Scene(Image* backgroundImage, std::vector<Button*> &btnVec) 
        : backgroundImage(backgroundImage), buttonVec(btnVec){}
    ~Scene() {
        delete backgroundImage;
        backgroundImage = nullptr;
        for (Button* btn : buttonVec) {
            delete btn;
            btn = nullptr;
        }
        buttonVec.clear();
    }
    // setters & getters
    Image* getBackgroundImage() { return backgroundImage; }

    virtual void onEnter() {}
    virtual void onExit() {}
    void draw(SDL_Renderer* SDL_renderer) override;
    void update(int delta) override {}
    virtual void handleEvent(SDL_Event &event) = 0;
    virtual void handleState(MouseInput &msInput) = 0;
protected:
    Image* backgroundImage;
    std::vector<Button*> buttonVec;
    virtual void drawBackground(SDL_Renderer* SDL_renderer);
    virtual void drawButtonVec(SDL_Renderer* SDL_renderer);
};

