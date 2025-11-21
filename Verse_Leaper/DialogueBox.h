#pragma once
#include <SDL_mixer.h>
#include <vector>
#include "Box.h"
#include "Drawable.h"

class Animation;

class Atlas;

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

public:
    DialogueBox(int x, int y, int width, int height);
    ~DialogueBox();
    
    void draw(SDL_Renderer* SDL_renderer) override;

public:
    bool isExist() const;
    void setExist(bool isExist);
    void setAtlas(Atlas* atlas);
	void setDialogueVec(const std::vector<Mix_Chunk*>& dialogueVec_);

    void next();                    // 跳转下一条对话
	void playDialogue(int idx);     // 播放第idx条对话
    void start(Dialogue dialogue);

private:
    bool isExist_ = false;
    Animation* dialogueAnimation = nullptr;
    std::vector<Mix_Chunk*> dialogueVec;
    Dialogue dialogue = Dialogue::null;
};

