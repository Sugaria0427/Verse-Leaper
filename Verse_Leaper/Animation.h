#pragma once
#include "Atlas.h"
#include<functional>

class Animation {
public:
    Animation(Atlas* atlas, int interval_ms = 1000)
        : atlas(atlas), interval_ms(interval_ms), timer(0), idxFrame(0) {
    }
    Animation() : Animation(nullptr) {}
    Animation(const Animation& animation) 
        : isStopped(animation.isStopped), 
        atlas(animation.atlas),
        timer(animation.timer), 
        idxFrame(animation.idxFrame), 
        interval_ms(animation.interval_ms), 
        callback(animation.callback) {
    }
    ~Animation() = default;
    // getters & setters
    int getSize() const { return atlas->getSize(); }
    SDL_Texture* getFrameTexture();
    Atlas* getAtlas() const { return atlas; }
    void setAtlas(Atlas* atlas) {
        if (atlas != this->atlas) {
            this->atlas = atlas;
            this->reset();
        }
    }
    void setCallback(std::function<void()> callback_) {
        this->callback = callback_;
    }
	int getIndexFrame() const { return idxFrame; }

    bool isLastFrame() const {
        return idxFrame == (atlas->getSize() - 1);
    }
    void updateIdxFrame(int delta);
    void reset() {
        idxFrame = 0;
        timer = 0;
    }
    void stop();
    void nextIdxFrame() { idxFrame = (idxFrame + 1) % atlas->getFrameList().size(); }
private:
    bool isStopped = false;
    Atlas* atlas;
    int timer = 0;
    int idxFrame = 0;
    int interval_ms = 0;
    std::function<void()> callback = nullptr;
};

