#pragma once
#include "Box.h"
#include "Animation.h"
#include "Drawable.h"
#include "GameObjectManager.h"
#include<SDL_mixer.h>

class DialogueBox :
    public Box, public Drawable
{
public:
    enum class Dialogue
    {
        Npc_SuShi_Old_giveArrow,
        Npc_SuShi_Old_alcohol,
        Npc_OldMan,
        Npc_SuShi_Young,
        null
    };
    DialogueBox(int x, int y, int width, int height);
    ~DialogueBox();
    // 接口
    void draw(SDL_Renderer* SDL_renderer) override;
    // getters&setters
    bool isExist() const { return isExist_; }
    void setExist(bool isExist) { isExist_ = isExist; }
    void setAtlas(Atlas* atlas) { dialogueAnimation->setAtlas(atlas); }
	void setDialogueVec(const std::vector<Mix_Chunk*>& dialogueVec_) { dialogueVec = dialogueVec_; }

    void next();    // 跳转下一条对话
	void playDialogue(int idx); // 播放第idx条对话
    void start(Dialogue dialogue);

private:
    bool isExist_ = false;
    Animation* dialogueAnimation = nullptr;
    std::vector<Mix_Chunk*> dialogueVec;
    Dialogue dialogue = Dialogue::null;
};

