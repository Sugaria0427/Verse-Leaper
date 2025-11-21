#include "Timer.h"

void Timer::setWaitTime(int val) { waitTime = val; }

int Timer::getPassTime() const { return passTime; }

void Timer::setCallback(std::function<void()> callback) { this->callback = callback; }

int Timer::getWaitTime() const { return waitTime; }

void Timer::restart() {
    passTime = 0;
    isShotted_ = false;
}

void Timer::pause() { paused = true; }

void Timer::resume() { paused = false; }

void Timer::setOneShot(bool isOneShot) { isOneShot_ = isOneShot; }

bool Timer::isShotted() const { return isShotted_; }

void Timer::update(int delta) {
    if (paused)
        return;
    passTime += delta;
    if (passTime >= waitTime && (!isShotted_ || !isOneShot_)) {
        if (callback) callback();
        isShotted_ = true;
        passTime = 0;
    }
}
