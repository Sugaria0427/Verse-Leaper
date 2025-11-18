#pragma once
#include <functional>
#include"Updatable.h"

class Timer : public Updatable
{
public:
    Timer() = default;
    Timer(const Timer& timer) = default;
    ~Timer() = default;

    void setWaitTime(int val){waitTime = val;}
    int getPassTime() const { return passTime; }
    void setCallback(std::function<void()> callback){this->callback = callback;}
	int getWaitTime() const { return waitTime; }

    void restart() {
        passTime = 0;
        isShotted_ = false;
    }
    void pause(){paused = true;}
    void resume(){ paused = false; }
    void setOneShot(bool isOneShot) { isOneShot_ = isOneShot; }
    bool isShotted() const { return isShotted_; }
    void update(int delta) override{
        if (paused)
            return;
        passTime += delta;
        if (passTime >= waitTime && (!isShotted_ || !isOneShot_)) {
            if (callback) callback();
            isShotted_ = true;
            passTime = 0;
        }
    }

private:
    int passTime = 0;         // 已过时间
    int waitTime = 0;         // 等待时间
    bool paused = false;      // 是否暂停
    bool isOneShot_ = true;   // 是否单次触发
    bool isShotted_ = false;     // 是否已触发一次
    std::function<void()> callback; // 触发回调
};

