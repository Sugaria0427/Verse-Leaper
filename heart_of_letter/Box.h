#pragma once
#include<SDL.h>
#include"Camera.h"

class Box
{
public:
    // ctor:
    Box(int x, int y, int width, int height) : x(x), y(y), width(width), height(height) {}
    Box() : Box(0, 0, 0, 0) {}
    Box(const Box& box) = default;
    ~Box() = default;
    // getters&setters
    int getWidth() const { return width; }
    int getHeight() const { return height; }
    int getX() const { return x; }
    int getY() const { return y; }
    void setBox(int x, int y, int width, int height) {
        this->x = x;
        this->y = y;
        this->width = width;
        this->height = height;
    }
    void setBoxPosition(int x, int y) {
        this->x = x;
        this->y = y;
    }
    void setX(int x) { this->x = x; }
    void setY(int y) { this->y = y; }
    void setWidth(int width) { this->width = width; }
    void setHeight(int height) { this->height = height; }

    SDL_Rect* getWorldRect() {
        return new SDL_Rect{ x, y, width, height };
    }
    SDL_Rect* getWindowRect(Camera* camera) {
        return new SDL_Rect{ 
            (int)((x - camera->getX()) * camera->getZoom()), 
            (int)((y - camera->getY()) * camera->getZoom()), 
            (int)(width * camera->getZoom()), 
            (int)(height * camera->getZoom()) 
        };
    }

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