#include "Camera.h"

Camera::Camera() :Camera(0, 0, 1280, 720) {}

Camera::Camera(double x, double y, double width, double height)
    :x_(x), y_(y), width_(width), height_(height)
{
}
