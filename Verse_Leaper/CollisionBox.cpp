#include "CollisionBox.h"

void CollisionBox::getOverlapLength(int& xLength, int& yLength, CollisionBox* box)
{
    int minX = this->x < box->x ? this->x : box->x;
    int maxX = (this->x + this->width) > (box->x + box->width) ? (this->x + this->width) : (box->x + box->width);
    xLength = (this->width + box->width) - (maxX - minX);
    int minY = this->y < box->y ? this->y : box->y;
    int maxY = (this->y + this->height) > (box->y + box->height) ? (this->y + this->height) : (box->y + box->height);
    yLength = (this->height + box->height) - (maxY - minY);
}

bool CollisionBox::isAnotherCollide(CollisionBox* box)
{
    int overlapX;
    int overlapY;
    this->getOverlapLength(overlapX, overlapY, box);
    if (overlapX > 0 && overlapY > 0)
    {
        return true;
    }
    return false;
}
