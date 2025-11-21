#pragma once
#include <SDL_mixer.h>
#include <SDL.h>
#include <unordered_map>
#include "Atlas.h"

enum class MusicType
{
    menuBgm,
    initialBgm,
    tigerBgm,
    bossBgm,
};

enum class SoundType
{
    jump, 
    jump_normal,
    jumpPad,
    run_grass,
    run_ice,
    run_cloud,
    run,
    hit,
    button,
    grunt,
    arrow,
    bell,
    board,
    die,
    dogRun,
    dogChase,
    dogGoback,
    eagleFly,
    eagleHawk,
    tigerRun,
    tigerAttack,
    tigerJump,
    bossLasser,
    bossMove,
    bossFire,
    bossWeak,
    bossBarrage,
};

enum class AtlasType
{
    atlasInitialBG,
    atlasTowerBG,
    atlasTransitionBG,
    atlasTigerBG,
    atlasCloudBG,
    atlasBossBG,
    atlasMainTower,
    atlasSmallTower,
    atlasTree,
    atlasWall,
    atlasPlayerIdleRight,
    atlasPlayerIdleLeft, 
    atlasPlayerRunRight, 
    atlasPlayerRunLeft,
    atlasPlayerUseArrowRight,
    atlasPlayerUseArrowLeft,
    atlasNpcSuShi_old,
    atlasNpcSuShi_young,
    atlasNpcOldman,
    atlasBlock_Grass,
    atlasBlock_GrassUnder,
    atlasBlock_IceGrass,
    atlasBlock_IceGrassUnder,
    atlasBlock_Ice,
    atlasBlock_Cloud_Red,
    atlasBlock_Cloud_Blue,
    atlasBlock_JumpPad,
    atlasBlock_SavePoint,
    atlasBlock_Teleport,
    atlasBlock_Mist01,
    atlasBlock_Air,
    atlasBlock_Board,
    atlasBlock_Dead,
    atlasHitBoxRight,
    atlasHitBoxLeft,
    atlasArrowRight,
    atlasArrowLeft,
    atlasBell,
    atlasDrum,
    atlasEnemyDogRunRight,
    atlasEnemyDogRunLeft,
    atlasEnemyDogDead,
    atlasEnemyEagleFlyRight,
    atlasEnemyEagleFlyLeft,
    atlasEnemyEagleDead,
    atlasEnemyTigerIdleRight,
    atlasEnemyTigerIdleLeft,
    atlasEnemyTigerMoveRight,
    atlasEnemyTigerMoveLeft,
    atlasEnemyTigerRetreatRight,
    atlasEnemyTigerRetreatLeft,
    atlasEnemyTigerAttackRight,
    atlasEnemyTigerAttackLeft,
    atlasEnemyTigerBiteBoxRight,
    atlasEnemyTigerBiteBoxLeft,
    atlasEnemyTigerJumpRight,
    atlasEnemyTigerJumpLeft,
    atlasEnemyTigerDead,
    atlasEnemyBossIdle,
    atlasEnemyBossLaser,
    atlasEnemyBossBarrage,
    atlasEnemyBossWeak,
    atlasLaser,
    atlasBarrage,
    atlasDropItem_Alcohol,
    atlasDropItem_Arrow,
    atlasDropItem_Sword,
    atlasDropItem_DoubleJump,
    atlasDropItem_Potion,
    atlasDialogue_giveArrow,
    atlasDialogue_alcohol,
    atlasDialogue_OldMan,
    atlasDialogue_Young,
};

enum class DialogueType
{
    GiveArrow,
    Alcohol,
    OldMan,
    Young,
};

class ResourceManager
{
private:
    ResourceManager() {}
    ~ResourceManager() {}
public:
    static ResourceManager& Instance() {
        static ResourceManager instance{};
        return instance;
    }

public:
    Mix_Music* getMusic(MusicType type);
    Mix_Chunk*& getSound(SoundType type);
    Atlas* getAtlas(AtlasType type);
    std::vector<Mix_Chunk*>& getDialogue(DialogueType type);

    void loadMusic(MusicType type, const char* path);
    void loadSound(SoundType type, const char* path);
    void loadAtlas(AtlasType type, const char* path, int size, SDL_RendererFlip initFlip = SDL_FLIP_NONE);
    void loadDialogue(DialogueType type, const std::vector<const char*>& paths);
    
    void initMusic();
    void initSound();
    void initAtlas();
    void initDialogue();

private:
    std::unordered_map<MusicType, Mix_Music*> musicPool;
    std::unordered_map<SoundType, Mix_Chunk*> soundPool;
    std::unordered_map<AtlasType, Atlas*> atlasPool;
    std::unordered_map<DialogueType, std::vector<Mix_Chunk*>> dialoguePool;
};