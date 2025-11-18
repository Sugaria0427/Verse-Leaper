#pragma once
#include<cmath>

class Vector2
{
public:
    Vector2() : Vector2(0, 0) {}
    Vector2(double x, double y) : x_(x), y_(y) {}
    ~Vector2() = default;
    // 运算符重载
    Vector2 operator+(const Vector2 &vec2) {
        return Vector2(this->x_ + vec2.x_, this->y_ + vec2.y_);
    }
    Vector2 operator-(const Vector2 &vec2) {
        return Vector2(this->x_ - vec2.x_, this->y_ - vec2.y_);
    }
    Vector2 operator*(double num) {
        return Vector2(this->x_ * num, this->y_ * num);
    }
    Vector2 operator/(double num) {
        if (num) {
            return Vector2(this->x_ / num, this->y_ / num);
        }
        else {
            return Vector2(0, 0);   // 不能除以零
        }
    }
    void operator+=(const Vector2 &vec2) {
        *this = (*this) + vec2;
    }
    void operator-=(const Vector2 &vec2) {
        *this = (*this) - vec2;
    }
    // getters&setters
    double getX() const { return x_; }
    double getY() const { return y_; }
    double getLength() const { return sqrt(x_ * x_ + y_ * y_); }
    Vector2 getUnit() const;
    void setX(double x) { x_ = x; }
    void setY(double y) { y_ = y; }
    void setUnit();
private:
    double x_;
    double y_;
};

