#pragma once
#include"Vector2.h"
#include<SDL.h>

class Camera
{
public:
    Camera();
    Camera(double x, double y, double width, double height);
    ~Camera() {}
    // getters&setters
    double getZoom() const { return zoom; }
    void setZoom(double zoom_) { zoom = zoom_; }
    SDL_Rect* getWorldRect() { return new SDL_Rect{(int)x_, (int)y_, (int)width_, (int)height_}; }
    SDL_Rect* getWindowRect() { return new SDL_Rect{ (int)(x_), (int)(y_), (int)(width_ / zoom), (int)(height_ / zoom) }; }
    void setSpeed(Vector2 vec) { speed_ = vec; }
    Vector2 getSpeed() const { return speed_; }
    double getX() const { return x_; }
    void setX(double x) { x_ = x; }
    double getY() const { return y_; }
    void setY(double y) { y_ = y; }
    double getWidth() { return width_; }
    double getHeight() { return height_; }

    void addSpeed(Vector2 vec) { speed_ += vec; }
    
private:
    double zoom = 1;
    double x_;
    double y_;
    double width_;
    double height_;
    Vector2 speed_;
};

