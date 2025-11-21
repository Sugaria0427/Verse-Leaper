#include "DialogueBox.h"
#include "GameObjFactory.h"
#include "ResourceManager.h"
#include "GameObjectManager.h"

DialogueBox::DialogueBox(int x, int y, int width, int height) : Box(x, y, width, height)
{
    dialogueAnimation = new Animation(ResourceManager::Instance().getAtlas(AtlasType::atlasDialogue_giveArrow));
    dialogueAnimation->stop();   // 不自动播放，不设置callback函数
}

DialogueBox::~DialogueBox()
{
    delete dialogueAnimation;
}

void DialogueBox::draw(SDL_Renderer* SDL_renderer) {
    if (this->isExist_) {
        SDL_Texture* texture = this->dialogueAnimation->getFrameTexture();
        SDL_Rect* rect = this->getWorldRect();
        int renderResult = SDL_RenderCopy(SDL_renderer, texture, NULL, rect);
		delete rect;
        // 创建失败
        if (renderResult != 0) {
            SDL_Log("DialogueBox::draw() SDL_RenderCopy failed: %s", SDL_GetError());
        }
    }
}

bool DialogueBox::isExist() const { return isExist_; }

void DialogueBox::setExist(bool isExist) { isExist_ = isExist; }

void DialogueBox::setAtlas(Atlas* atlas) { dialogueAnimation->setAtlas(atlas); }

void DialogueBox::setDialogueVec(const std::vector<Mix_Chunk*>& dialogueVec_) { dialogueVec = dialogueVec_; }

void DialogueBox::next() {
    if (!this->isExist()) return;   // 对话框不存在时不处理
    
    if (dialogueAnimation->isLastFrame()) {
        // 动画结束后关闭对话框
        this->setExist(false);
        this->dialogueAnimation->reset();
        // 停止当前音频
        Mix_HaltChannel(-1);
        // 控制雾气消失
        for (GameObject* obj : GameObjManager::instance()->getVec()) {
            switch (dialogue) {
            case Dialogue::Npc_SuShi_Old_giveArrow:
                if (obj->getTag() == Tag::Block_Mist_SuShi_Arrow) obj->setExist(false);
                if (!GameObjManager::instance()->getPlayer()->hasArrow() && obj->getTag() == Tag::Npc_SuShi_Old_giveArrow) {
                    DropItem* dropItem = GameObjFactory::instance()->createDropItem(Tag::DropItem_Arrow, obj->getBoxX(), obj->getBoxY());
                    dropItem->drop(obj->getBoxX(), obj->getBoxY());
                    GameObjManager::instance()->addGameObj(dropItem);
                }
                break;
            case Dialogue::Npc_SuShi_Old_alcohol:
                if (obj->getTag() == Tag::Block_Mist02) obj->setExist(false);
                break;
            }
        }
    }
    else {
		// 暂停当前音频
		Mix_HaltChannel(-1);
		// 播放当前帧对应音频            
        this->dialogueAnimation->nextIdxFrame();
        this->playDialogue(this->dialogueAnimation->getIndexFrame());
    }
}

void DialogueBox::playDialogue(int idx)
{
    if (idx >= 0 && idx < dialogueVec.size()) {
        Mix_PlayChannel(-1, dialogueVec[idx], 0);
    }
}

void DialogueBox::start(Dialogue dialogue)
{
    this->setExist(true);
    Mix_HaltChannel(-1);
    switch (dialogue) {
    case Dialogue::Npc_SuShi_Old_giveArrow:
        this->dialogue = Dialogue::Npc_SuShi_Old_giveArrow;
        // 播放音效
        this->setDialogueVec(ResourceManager::Instance().getDialogue(DialogueType::GiveArrow));
        // 展示对话
        this->setAtlas(ResourceManager::Instance().getAtlas(AtlasType::atlasDialogue_giveArrow));
        break;
    case Dialogue::Npc_SuShi_Old_alcohol:
        this->dialogue = Dialogue::Npc_SuShi_Old_alcohol;
        this->setDialogueVec(ResourceManager::Instance().getDialogue(DialogueType::Alcohol));
        this->setAtlas(ResourceManager::Instance().getAtlas(AtlasType::atlasDialogue_alcohol));
        break;
    case Dialogue::Npc_OldMan:
        this->dialogue = Dialogue::Npc_OldMan;
        this->setDialogueVec(ResourceManager::Instance().getDialogue(DialogueType::OldMan));
        this->setAtlas(ResourceManager::Instance().getAtlas(AtlasType::atlasDialogue_OldMan));
        break;
    case Dialogue::Npc_SuShi_Young:
        this->dialogue = Dialogue::Npc_SuShi_Old_alcohol;
        this->setDialogueVec(ResourceManager::Instance().getDialogue(DialogueType::Young));
        this->setAtlas(ResourceManager::Instance().getAtlas(AtlasType::atlasDialogue_Young));
        break;
    }
    this->playDialogue(0);
}
