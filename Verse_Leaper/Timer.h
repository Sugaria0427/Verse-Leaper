#pragma once
#include <functional>
#include "Updatable.h"

class Timer : public Updatable
{
public:
    Timer() = default;
    Timer(const Timer& timer) = default;
    ~Timer() = default;

    void setWaitTime(int val);
    int getPassTime() const;
    void setCallback(std::function<void()> callback);
	int getWaitTime() const;

    void restart();
    void pause();
    void resume();
    void setOneShot(bool isOneShot);
    bool isShotted() const;
    void update(int delta) override;

private:
    int passTime = 0;         // 已过时间
    int waitTime = 0;         // 等待时间
    bool paused = false;      // 是否暂停
    bool isOneShot_ = true;   // 是否单次触发
    bool isShotted_ = false;     // 是否已触发一次
    std::function<void()> callback; // 触发回调
};

