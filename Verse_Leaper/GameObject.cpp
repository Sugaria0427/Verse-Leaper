#include "GameObject.h"
#include "Panel.h"
#include "ResourceManager.h"

GameObject::GameObject(Tag tag_, Animation* _animation, Box* _box, int _HP, int _AD, int _MaxHP)
    : tag(tag_), animation(_animation), box(_box), HP(_HP), AD(_AD), MaxHP(_MaxHP) {}

GameObject::GameObject(const GameObject& obj)
    : tag(obj.tag),
    isExist_(obj.isExist_),
    isDead_(obj.isDead_),
    hasArrow_(obj.hasArrow_),
    hasSword_(obj.hasSword_),
    hasAlcohol_(obj.hasAlcohol_),
    speed(obj.speed),
    gravity(obj.gravity),
    HP(obj.HP),
    AD(obj.AD),
    MaxHP(obj.MaxHP)
{
    this->animation = new Animation(*(obj.animation));
    this->box = new Box(*(obj.box));
}

GameObject::~GameObject() {
    delete animation;
    delete box;
}

void GameObject::draw(SDL_Renderer* SDL_renderer) {
    if (this->isExist_) {
        SDL_Texture* texture = animation->getFrameTexture();
        SDL_Rect* winRect = box->getWindowRect(Panel::Instance().getCamera());
        SDL_RendererFlip flip = animation->getAtlas()->getFlip();
        SDL_RenderCopyEx(SDL_renderer, texture, NULL, winRect, 0, NULL, flip);
		delete winRect;
    }
}


void GameObject::setSpeedUnit()
{
    this->speed.setUnit();
}

void GameObject::jump() {
    speed.setY(JumpSpeed);
    // ²¥·ÅÌøÔ¾ÒôĞ§
    Mix_PlayChannel(-1, ResourceManager::Instance().getSound(SoundType::jump), 0);
}

void GameObject::updatePosition()
{
    box->setX(box->getX() + this->speed.getX() * 8);
    box->setY(box->getY() + this->speed.getY());
}
