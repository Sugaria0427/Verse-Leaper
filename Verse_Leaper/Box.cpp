#include "Box.h"
#include "Camera.h"

Box::Box(int x, int y, int width, int height) : x(x), y(y), width(width), height(height) {}

Box::Box() : Box(0, 0, 0, 0) {}

void Box::setBox(int x, int y, int width, int height) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
}

void Box::setBoxPosition(int x, int y) {
    this->x = x;
    this->y = y;
}

void Box::setWidth(int width) { this->width = width; }

void Box::setHeight(int height) { this->height = height; }

SDL_Rect* Box::getWorldRect() {
    return new SDL_Rect{ x, y, width, height };
}

SDL_Rect* Box::getWindowRect(Camera* camera) {
    return new SDL_Rect{
        (int)((x - camera->getX()) * camera->getZoom()),
        (int)((y - camera->getY()) * camera->getZoom()),
        (int)(width * camera->getZoom()),
        (int)(height * camera->getZoom())
    };
}