#pragma once
#include<SDL.h>

class Camera;

class Box
{
public:
    Box(int x, int y, int width, int height);
    Box();
    Box(const Box& box) = default;
    ~Box() = default;

public:
    int getWidth() const { return width; }
    int getHeight() const { return height; }
    int getX() const { return x; }
    int getY() const { return y; }
    void setBox(int x, int y, int width, int height);
    void setBoxPosition(int x, int y);
    void setX(int x) { this->x = x; }
    void setY(int y) { this->y = y; }
    void setWidth(int width);
    void setHeight(int height);

    SDL_Rect* getWorldRect();
    SDL_Rect* getWindowRect(Camera* camera);

    bool isPointOn(double x_, double y_) const {
        if ((x < x_ && x_ < x + width) && (y < y_ && y_ < y + height)) return true;
        else return false;
    }
protected:
    int x;
    int y;
    int width;
    int height;
};