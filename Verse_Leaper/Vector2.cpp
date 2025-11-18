#include "Vector2.h"

Vector2 Vector2::getUnit() const
{
    if (0 == x_ && 0 == y_) {
        return Vector2(0, 0);
    }
    else {
        return Vector2(x_ / getLength(), y_ / getLength());;
    }
}

void Vector2::setUnit()
{
    Vector2 unit = getUnit();
    x_ = unit.x_;
    y_ = unit.y_;
}
