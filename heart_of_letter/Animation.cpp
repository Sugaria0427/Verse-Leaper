#include "Animation.h"

SDL_Texture* Animation::getFrameTexture() {
    return this->atlas->getFrameList()[idxFrame]->getImgTexture();
}
void Animation::updateIdxFrame(int delta) {
    if (!isStopped) {
        timer += delta;
        if (timer >= interval_ms) {
            if (isLastFrame() && callback) {
                callback();
            }
            this->nextIdxFrame();
            timer = 0;
        }
    }
}

void Animation::stop(){
    if (!isStopped) {
        isStopped = true;
    }
}
