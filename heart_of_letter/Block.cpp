#include "Block.h"
#include "Player.h"
#include "MapManager.h"
#include "ResourceManager.h"

Block::Block(Tag _tag, Animation* _animation, Box* _Box)
    : GameObject(_tag, _animation, _Box) {
    initCollisionBox();
}

Block::Block(const Block& block)
    : GameObject(block) {
    initCollisionBox();
}

Block::~Block()
{
    switch (this->getTag()) {
    case Tag::Block_Mist_SuShi_Arrow:
        this->initCollisionBox();
        break;
    case Tag::Block_Mist02:
        this->initCollisionBox();
        break;
    default:
        break;
    }
}

GameObject* Block::clone() {
    Block* block = nullptr;
    switch (this->getTag()) {
    case Tag::Block_Mist_SuShi_Arrow:
        this->initCollisionBox();
        return this;
        break;
    case Tag::Block_Mist02:
        this->initCollisionBox();
        return this;
        break;
    case Tag::Block_Cloud1:
        block = new Block(*this);
        block->setExist(false);
        return block;
        break;
    case Tag::Block_Cloud2:
        block = new Block(*this);
        block->setExist(false);
        return block;
        break;
    default:
        return new Block(*this);
        break;
    }
}

void Block::beDeleted() {
    switch (this->getTag()) {
    case Tag::Block_Mist_SuShi_Arrow:
        return;
        break;
    case Tag::Block_Mist02:
        return;
        break;
    default:
        delete this;
        break;
    }
}

void Block::update(int delta) {
    if (isExist_) {
        updatePosition();
        this->animation->updateIdxFrame(delta);
        // Åö×²ÏäÒÆ¶¯
        this->collisionBox->setBox(this->getBoxX(), this->getBoxY(), this->getBoxWidth(), this->getBoxHeight());
    }
    else {
    }
}

void Block::initCollisionBox()
{
    // ´´½¨Åö×²Ïä
    collisionBox = CollisionManager::instance()->creatCollisionBox(this, box->getX(), box->getY(), box->getWidth(), box->getHeight());
    this->collisionBox->setLayerSrc(CollisionBox::Layer::Block);
    this->collisionBox->setLayerDst(CollisionBox::Layer::Player);
    collisionBox->setOnCollide(
        [this](CollisionBox* boxDst) {
            ResourceManager::Instance().getSound(SoundType::jump) = ResourceManager::Instance().getSound(SoundType::jump_normal);
			Player* player = dynamic_cast<Player*>(boxDst->getOwner());
			Vector2 position = Vector2(0, 0);
            boxDst->getOwner()->setJumpSpeed(-25);
            switch (this->getTag()) {
            case Tag::Block_Grass:
                ResourceManager::Instance().getSound(SoundType::run) = ResourceManager::Instance().getSound(SoundType::run_grass);
                break;
            case Tag::Block_GrassUnder:
                ResourceManager::Instance().getSound(SoundType::run) = ResourceManager::Instance().getSound(SoundType::run_grass);
				break;
            case Tag::Block_IceGrass:
                ResourceManager::Instance().getSound(SoundType::run) = ResourceManager::Instance().getSound(SoundType::run_ice);
				break;
            case Tag::Block_IceGrassUnder:
                ResourceManager::Instance().getSound(SoundType::run) = ResourceManager::Instance().getSound(SoundType::run_ice);
				break;
            case Tag::Block_Ice:
                ResourceManager::Instance().getSound(SoundType::run) = ResourceManager::Instance().getSound(SoundType::run_ice);
                break;
            case Tag::Block_Cloud1:
                ResourceManager::Instance().getSound(SoundType::run) = ResourceManager::Instance().getSound(SoundType::run_cloud);
                break;
            case Tag::Block_Cloud2:
                ResourceManager::Instance().getSound(SoundType::run) = ResourceManager::Instance().getSound(SoundType::run_cloud);
                break;
            case Tag::Block_JumpPad:
                ResourceManager::Instance().getSound(SoundType::jump) = ResourceManager::Instance().getSound(SoundType::jumpPad);
                player->setJumpSpeed(-40);
				break;
            case Tag::Block_SavePoint:
                position = Vector2(this->getBoxX(), this->getBoxY() - player->getBoxHeight());
                player->setLastSavePointPosition(position);
                player->setLastSavePointMap(MapManager::instance()->getCurrentMap());
                break;
			case Tag::Block_TeleportNext:
                MapManager::instance()->setTeleportFlag(MapManager::TeleportFlag::Next);
				break;
			case Tag::Block_TeleportPrior:
                MapManager::instance()->setTeleportFlag(MapManager::TeleportFlag::Prior);
				break;
			case Tag::Block_TeleportExtra:
                MapManager::instance()->setTeleportFlag(MapManager::TeleportFlag::Extra);
				break;
            case Tag::Block_Air:
                ResourceManager::Instance().getSound(SoundType::run) = ResourceManager::Instance().getSound(SoundType::run_ice);
				break;
            case Tag::Block_Board:
				break;
            case Tag::Block_Dead:
				player->decreaseHP(100);
            case Tag::Block_TowerMist:
                break;
			default:
				break;
            };
        }
    );
    if (!this->isExist()) collisionBox->setCollidable(false);
    else collisionBox->setCollidable(true);
}
