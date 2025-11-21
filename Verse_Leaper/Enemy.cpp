#include "Enemy.h"
#include "GameObjFactory.h"
#include "EnemyDogStates.h"
#include "EnemyEagleStates.h"

Enemy::Enemy(Tag _tag, Animation* _animation,  Box* _EnemyBox)
    : Entity(_tag, _animation, _EnemyBox) {
    initEnemy();
}

Enemy::Enemy(const Enemy& enemy)
    : isInvincible(enemy.isInvincible),
    Entity(enemy)
{
    initEnemy();
}

void Enemy::update(int delta) {
    if (isExist_) {
        Entity::update(delta);
        this->hurtBox->setBox(this->getBoxX(), this->getBoxY(), this->getBoxWidth(), this->getBoxHeight());
        if (isInvincible) {
            this->invincibleDur->update(delta);
        }
    }
}

void Enemy::decreaseHP(int _damage) {
    if (!isInvincible) {
        HP -= _damage;
        if (HP <= 0 && !isDead_) {
            setIsDead(true);
        }
        isInvincible = true;
    }
}
void Enemy::draw(SDL_Renderer* SDL_renderer) {
    GameObject::draw(SDL_renderer);
    //if (HP > 0) {
    //    const int hpWidth = 100;
    //    const int hpHeight = 10;
    //    int hpX = (this->getBoxX() + (this->getBoxWidth() - hpWidth) / 2 - camera->getX()) * camera->getZoom();
    //    int hpY = (this->getBoxY() - hpHeight - 5 - camera->getY()) * camera->getZoom();
    //    SDL_Rect bgRect = { hpX, hpY, hpWidth * camera->getZoom(), hpHeight * camera->getZoom() };
    //    SDL_Rect hpRect = { bgRect.x, bgRect.y, (int)(bgRect.w * ((float)getHP() / 10)), bgRect.h };
    //    SDL_SetRenderDrawColor(SDL_renderer, 255, 0, 0, 255);
    //    SDL_RenderFillRect(SDL_renderer, &bgRect);
    //    SDL_SetRenderDrawColor(SDL_renderer, 0, 255, 0, 255);
    //    SDL_RenderFillRect(SDL_renderer, &hpRect);
    //}
}

void Enemy::initEnemy()
{
    invincibleDur = new Timer();
    this->invincibleDur->setWaitTime(300);
    this->invincibleDur->setOneShot(false);
    this->invincibleDur->setCallback(
        [this]() {
            isInvincible = false;
        }
    );
    hurtBox = CollisionManager::instance()->creatCollisionBox(this, this->box->getX(), this->box->getY(), this->box->getWidth(), this->box->getHeight());
    this->hurtBox->setLayerSrc(CollisionBox::Layer::Enemy);
    this->hurtBox->setLayerDst(CollisionBox::Layer::Null);
    hurtBox->setCollidable(true);
    animation->setCallback(
        [this]() {
            if (isDead_) {
                // Í£Ö¹²¥·Å¶¯»­
                this->getAnimation()->stop();
                this->setWillDrop(true);
            }
        }
    );
    if (!this->isExist())
        hurtBox->setCollidable(false);
}