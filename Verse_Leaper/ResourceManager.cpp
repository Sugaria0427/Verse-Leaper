#include <stdexcept>
#include "ResourceManager.h"

Mix_Music* ResourceManager::getMusic(MusicType type) {
    if (musicPool.find(type) != musicPool.end()) {
        return musicPool[type];
    }
    else {
        return nullptr;
    }
}

Mix_Chunk*& ResourceManager::getSound(SoundType type)
{
    if (soundPool.find(type) != soundPool.end()) {
        return soundPool[type];
    }
    else {
        throw std::runtime_error("Sound not found");
    }
}

Atlas* ResourceManager::getAtlas(AtlasType type) {
    if (atlasPool.find(type) != atlasPool.end()) {
        return atlasPool[type];
    }
    else {
        return nullptr;
    }
}

std::vector<Mix_Chunk*>& ResourceManager::getDialogue(DialogueType type)
{
    if (dialoguePool.find(type) != dialoguePool.end()) {
        return dialoguePool[type];
    }
    else {
        throw std::runtime_error("Dialogue not found");
    }
}

void ResourceManager::loadMusic(MusicType type, const char* path) {
    musicPool[type] = Mix_LoadMUS(path);
}

void ResourceManager::loadSound(SoundType type, const char* path)
{
    soundPool[type] = Mix_LoadWAV(path);
}

void ResourceManager::loadAtlas(AtlasType type, const char* path, int size, SDL_RendererFlip initFlip)
{
    atlasPool[type] = new Atlas(path, size, initFlip);
}

void ResourceManager::loadDialogue(DialogueType type, const std::vector<const char*>& paths)
{
    std::vector<Mix_Chunk*> dialogueSounds;
    for (const char* path : paths) {
        Mix_Chunk* chunk = Mix_LoadWAV(path);
        dialogueSounds.push_back(chunk);
    }
    dialoguePool[type] = dialogueSounds;
}

void ResourceManager::initMusic()
{
    ResourceManager::Instance().loadMusic(MusicType::menuBgm, "music\\BGM\\music_menuBgm.mp3");
    ResourceManager::Instance().loadMusic(MusicType::initialBgm, "music\\BGM\\music_initialBgm.mp3");
    ResourceManager::Instance().loadMusic(MusicType::tigerBgm, "music\\BGM\\music_tigerBgm.mp3");
    ResourceManager::Instance().loadMusic(MusicType::bossBgm, "music\\BGM\\music_bossBgm.mp3");
}

void ResourceManager::initSound()
{
    ResourceManager::Instance().loadSound(SoundType::jump, "music\\sound_jump.wav");
    ResourceManager::Instance().loadSound(SoundType::jump_normal, "music\\sound_jump.wav");
    ResourceManager::Instance().loadSound(SoundType::jumpPad, "music\\sound_jumpPad.wav");
    ResourceManager::Instance().loadSound(SoundType::run, "music\\sound_run_grass.wav");
    ResourceManager::Instance().loadSound(SoundType::run_grass, "music\\sound_run_grass.wav");
    ResourceManager::Instance().loadSound(SoundType::run_ice, "music\\sound_run_ice.wav");
    ResourceManager::Instance().loadSound(SoundType::run_cloud, "music\\sound_run_cloud.wav");
    ResourceManager::Instance().loadSound(SoundType::hit, "music\\sound_hit.wav");
    ResourceManager::Instance().loadSound(SoundType::button, "music\\sound_button.wav");
    ResourceManager::Instance().loadSound(SoundType::grunt, "music\\sound_grunt.wav");
    ResourceManager::Instance().loadSound(SoundType::arrow, "music\\sound_arrow.wav");
    ResourceManager::Instance().loadSound(SoundType::bell, "music\\sound_bell.wav");
    ResourceManager::Instance().loadSound(SoundType::board, "music\\sound_board.wav");
    ResourceManager::Instance().loadSound(SoundType::die, "music\\sound_die.wav");
    ResourceManager::Instance().loadSound(SoundType::dogRun, "music\\dog\\sound_dogRun.wav");
    ResourceManager::Instance().loadSound(SoundType::dogChase, "music\\dog\\sound_dogChase.wav");
    ResourceManager::Instance().loadSound(SoundType::dogGoback, "music\\dog\\sound_dogGoback.wav");
    ResourceManager::Instance().loadSound(SoundType::eagleFly, "music\\eagle\\sound_eagleFly.wav");
    ResourceManager::Instance().loadSound(SoundType::eagleHawk, "music\\eagle\\sound_eagleHawk.wav");
    ResourceManager::Instance().loadSound(SoundType::tigerAttack, "music\\tiger\\sound_tigerAttack.wav");
    ResourceManager::Instance().loadSound(SoundType::tigerRun, "music\\tiger\\sound_tigerRun.wav");
    ResourceManager::Instance().loadSound(SoundType::tigerJump, "music\\tiger\\sound_tigerJump.wav");
    ResourceManager::Instance().loadSound(SoundType::bossLasser, "music\\boss\\sound_bossLasser.wav");
    ResourceManager::Instance().loadSound(SoundType::bossMove, "music\\boss\\sound_bossMove.wav");
    ResourceManager::Instance().loadSound(SoundType::bossFire, "music\\boss\\sound_bossFire.wav");
    ResourceManager::Instance().loadSound(SoundType::bossWeak, "music\\boss\\sound_bossWeak.wav");
    ResourceManager::Instance().loadSound(SoundType::bossBarrage, "music\\boss\\sound_bossBarrage.wav");
}

void ResourceManager::initAtlas()
{
    ResourceManager::Instance().loadAtlas(AtlasType::atlasInitialBG,    "atlas\\BG\\initialBG_%d.bmp", 1);
    ResourceManager::Instance().loadAtlas(AtlasType::atlasTowerBG,      "atlas\\BG\\towerBG_%d.bmp", 1);
    ResourceManager::Instance().loadAtlas(AtlasType::atlasTransitionBG, "atlas\\BG\\transitionBG_%d.bmp", 1);
    ResourceManager::Instance().loadAtlas(AtlasType::atlasTigerBG,      "atlas\\BG\\tigerBG_%d.bmp", 1);
    ResourceManager::Instance().loadAtlas(AtlasType::atlasCloudBG,      "atlas\\BG\\cloudBG_%d.bmp", 1);
    ResourceManager::Instance().loadAtlas(AtlasType::atlasBossBG,       "atlas\\BG\\bossBG_%d.bmp", 1);

    ResourceManager::Instance().loadAtlas(AtlasType::atlasMainTower,    "atlas\\MainTower_%d.bmp", 1);
    ResourceManager::Instance().loadAtlas(AtlasType::atlasSmallTower,   "atlas\\SmallTower_%d.bmp", 1, SDL_FLIP_HORIZONTAL);
    ResourceManager::Instance().loadAtlas(AtlasType::atlasTree,         "atlas\\Tree_%d.bmp", 1);
    ResourceManager::Instance().loadAtlas(AtlasType::atlasWall,         "atlas\\Wall_%d.bmp", 1);

    ResourceManager::Instance().loadAtlas(AtlasType::atlasPlayerIdleRight,"atlas\\Player\\player_idle_%d.bmp", 4);
    ResourceManager::Instance().loadAtlas(AtlasType::atlasPlayerIdleLeft, "atlas\\Player\\player_idle_%d.bmp", 4, SDL_FLIP_HORIZONTAL);
    ResourceManager::Instance().loadAtlas(AtlasType::atlasPlayerRunRight, "atlas\\Player\\run_%d.bmp", 6);
    ResourceManager::Instance().loadAtlas(AtlasType::atlasPlayerRunLeft, "atlas\\Player\\run_%d.bmp", 6, SDL_FLIP_HORIZONTAL);
    ResourceManager::Instance().loadAtlas(AtlasType::atlasPlayerUseArrowRight, "atlas\\Player\\useArrow_%d.bmp", 3);
    ResourceManager::Instance().loadAtlas(AtlasType::atlasPlayerUseArrowLeft, "atlas\\Player\\useArrow_%d.bmp", 3, SDL_FLIP_HORIZONTAL);

    ResourceManager::Instance().loadAtlas(AtlasType::atlasNpcSuShi_old, "atlas\\SuShi01_%d.bmp", 2);
    ResourceManager::Instance().loadAtlas(AtlasType::atlasNpcSuShi_young, "atlas\\SuShi02_%d.bmp", 1);
    ResourceManager::Instance().loadAtlas(AtlasType::atlasNpcOldman, "atlas\\Oldman_%d.bmp", 2);

    ResourceManager::Instance().loadAtlas(AtlasType::atlasBlock_Grass, "atlas\\block_Grass_%d.bmp", 1);
    ResourceManager::Instance().loadAtlas(AtlasType::atlasBlock_GrassUnder, "atlas\\block_GrassUnder_%d.bmp", 1);
    ResourceManager::Instance().loadAtlas(AtlasType::atlasBlock_IceGrass, "atlas\\block_Ice_%d.bmp", 1);
    ResourceManager::Instance().loadAtlas(AtlasType::atlasBlock_IceGrassUnder, "atlas\\Block_IceUnder_%d.bmp", 1);
    ResourceManager::Instance().loadAtlas(AtlasType::atlasBlock_Ice, "atlas\\block_Ice_%d.bmp", 1);
    ResourceManager::Instance().loadAtlas(AtlasType::atlasBlock_Cloud_Red, "atlas\\block_Cloud_Red_%d.bmp", 1);
    ResourceManager::Instance().loadAtlas(AtlasType::atlasBlock_Cloud_Blue, "atlas\\block_Cloud_Blue_%d.bmp", 1);
    ResourceManager::Instance().loadAtlas(AtlasType::atlasBlock_JumpPad, "atlas\\block_JumpPad_%d.bmp", 1);
    ResourceManager::Instance().loadAtlas(AtlasType::atlasBlock_SavePoint, "atlas\\block_SavePoint_%d.bmp", 1);
    ResourceManager::Instance().loadAtlas(AtlasType::atlasBlock_Teleport, "atlas\\block_Teleport_%d.bmp", 1);
    ResourceManager::Instance().loadAtlas(AtlasType::atlasBlock_Mist01, "atlas\\Block_Mist01_%d.bmp", 1);
    ResourceManager::Instance().loadAtlas(AtlasType::atlasBlock_Air, "atlas\\block_Air_%d.bmp", 1);
    ResourceManager::Instance().loadAtlas(AtlasType::atlasBlock_Board, "atlas\\block_Board_%d.bmp", 1);
    ResourceManager::Instance().loadAtlas(AtlasType::atlasBlock_Dead, "atlas\\block_Dead_%d.bmp", 1);

    ResourceManager::Instance().loadAtlas(AtlasType::atlasHitBoxRight, "atlas\\hit_%d.bmp", 3);
    ResourceManager::Instance().loadAtlas(AtlasType::atlasHitBoxLeft, "atlas\\hit_%d.bmp", 3, SDL_FLIP_HORIZONTAL);
    ResourceManager::Instance().loadAtlas(AtlasType::atlasArrowRight, "atlas\\arrow_%d.bmp", 2);
    ResourceManager::Instance().loadAtlas(AtlasType::atlasArrowLeft, "atlas\\arrow_%d.bmp", 2, SDL_FLIP_HORIZONTAL);
    ResourceManager::Instance().loadAtlas(AtlasType::atlasBell, "atlas\\bell_%d.bmp", 1);
    ResourceManager::Instance().loadAtlas(AtlasType::atlasDrum, "atlas\\drum_%d.bmp", 1);

    ResourceManager::Instance().loadAtlas(AtlasType::atlasEnemyDogRunRight, "atlas\\dog\\dogPatrol_%d.bmp", 7, SDL_FLIP_HORIZONTAL);
    ResourceManager::Instance().loadAtlas(AtlasType::atlasEnemyDogRunLeft, "atlas\\dog\\dogPatrol_%d.bmp", 7);
    ResourceManager::Instance().loadAtlas(AtlasType::atlasEnemyDogDead, "atlas\\dog\\dogDead_%d.bmp", 5);

    ResourceManager::Instance().loadAtlas(AtlasType::atlasEnemyEagleFlyRight, "atlas\\eagle\\eaglePatrol_%d.bmp", 6, SDL_FLIP_HORIZONTAL);
    ResourceManager::Instance().loadAtlas(AtlasType::atlasEnemyEagleFlyLeft, "atlas\\eagle\\eaglePatrol_%d.bmp", 6);
    ResourceManager::Instance().loadAtlas(AtlasType::atlasEnemyEagleDead, "atlas\\eagle\\eagleDead_%d.bmp", 5);

    ResourceManager::Instance().loadAtlas(AtlasType::atlasEnemyTigerIdleRight, "atlas\\Tiger\\tiger_Idle_%d.bmp", 1, SDL_FLIP_HORIZONTAL);
    ResourceManager::Instance().loadAtlas(AtlasType::atlasEnemyTigerIdleLeft, "atlas\\Tiger\\tiger_Idle_%d.bmp", 1);
    ResourceManager::Instance().loadAtlas(AtlasType::atlasEnemyTigerMoveRight, "atlas\\Tiger\\run\\Tiger_run_%d.bmp", 6, SDL_FLIP_HORIZONTAL);
    ResourceManager::Instance().loadAtlas(AtlasType::atlasEnemyTigerMoveLeft, "atlas\\Tiger\\run\\Tiger_run_%d.bmp", 6);
    ResourceManager::Instance().loadAtlas(AtlasType::atlasEnemyTigerRetreatRight, "atlas\\Tiger\\run\\Tiger_retreat_%d.bmp", 6, SDL_FLIP_HORIZONTAL);
    ResourceManager::Instance().loadAtlas(AtlasType::atlasEnemyTigerRetreatLeft, "atlas\\Tiger\\run\\Tiger_retreat_%d.bmp", 6);
    ResourceManager::Instance().loadAtlas(AtlasType::atlasEnemyTigerAttackRight, "atlas\\Tiger\\tiger_Attack_%d.bmp", 6, SDL_FLIP_HORIZONTAL);
    ResourceManager::Instance().loadAtlas(AtlasType::atlasEnemyTigerAttackLeft, "atlas\\Tiger\\tiger_Attack_%d.bmp", 6);
    ResourceManager::Instance().loadAtlas(AtlasType::atlasEnemyTigerBiteBoxRight, "atlas\\Tiger\\bite_%d.bmp", 5);
    ResourceManager::Instance().loadAtlas(AtlasType::atlasEnemyTigerBiteBoxLeft, "atlas\\Tiger\\bite_%d.bmp", 5, SDL_FLIP_HORIZONTAL);
    ResourceManager::Instance().loadAtlas(AtlasType::atlasEnemyTigerJumpRight, "atlas\\Tiger\\tiger_Jump_%d.bmp", 4, SDL_FLIP_HORIZONTAL);
    ResourceManager::Instance().loadAtlas(AtlasType::atlasEnemyTigerJumpLeft, "atlas\\Tiger\\tiger_Jump_%d.bmp", 4);
    ResourceManager::Instance().loadAtlas(AtlasType::atlasEnemyTigerDead, "atlas\\Tiger\\tigerDead_%d.bmp", 5, SDL_FLIP_HORIZONTAL);

    ResourceManager::Instance().loadAtlas(AtlasType::atlasEnemyBossIdle, "atlas\\Boss\\boss_idle_%d.bmp", 3);
    ResourceManager::Instance().loadAtlas(AtlasType::atlasEnemyBossLaser, "atlas\\Boss\\boss_laser_%d.bmp", 4);
    ResourceManager::Instance().loadAtlas(AtlasType::atlasEnemyBossBarrage, "atlas\\Boss\\boss_laser_%d.bmp", 4);
    ResourceManager::Instance().loadAtlas(AtlasType::atlasEnemyBossWeak, "atlas\\Boss\\boss_weak_%d.bmp", 3);
    ResourceManager::Instance().loadAtlas(AtlasType::atlasEnemyBossDead, "atlas\\Boss\\boss_weak_%d.bmp", 3);
    ResourceManager::Instance().loadAtlas(AtlasType::atlasLaser, "atlas\\Boss\\laser_%d.bmp", 1);
    ResourceManager::Instance().loadAtlas(AtlasType::atlasBarrage, "atlas\\Boss\\barrage_%d.bmp", 1);

    ResourceManager::Instance().loadAtlas(AtlasType::atlasDropItem_Alcohol, "atlas\\dropItem_Alcohol_%d.bmp", 1);
    ResourceManager::Instance().loadAtlas(AtlasType::atlasDropItem_Arrow, "atlas\\dropItem_Arrow_%d.bmp", 1);
    ResourceManager::Instance().loadAtlas(AtlasType::atlasDropItem_Sword, "atlas\\dropItem_Sword_%d.bmp", 1);
    ResourceManager::Instance().loadAtlas(AtlasType::atlasDropItem_DoubleJump, "atlas\\dropItem_DoubleJump_%d.bmp", 1);
    ResourceManager::Instance().loadAtlas(AtlasType::atlasDropItem_Potion, "atlas\\dropItem_Potion_%d.bmp", 1);

    ResourceManager::Instance().loadAtlas(AtlasType::atlasDialogue_giveArrow, "atlas\\dialogue\\SuShi_Arrow\\Dialogue02_%d.bmp", 5);
    ResourceManager::Instance().loadAtlas(AtlasType::atlasDialogue_alcohol, "atlas\\dialogue\\SuShi_Alcohol\\Dialogue03_%d.bmp", 5);
    ResourceManager::Instance().loadAtlas(AtlasType::atlasDialogue_OldMan, "atlas\\dialogue\\OldMan\\Dialogue01_%d.bmp", 6);
    ResourceManager::Instance().loadAtlas(AtlasType::atlasDialogue_Young, "atlas\\dialogue\\SuShi_Young\\Dialogue04_%d.bmp", 7);

}

void ResourceManager::initDialogue()
{
    ResourceManager::Instance().loadDialogue(DialogueType::GiveArrow, { 
        "dialogue\\giveArrow\\FirstSuShi01.wav",
        "empty",
        "dialogue\\giveArrow\\FirstSuShi02.wav",
        "empty",
        "dialogue\\giveArrow\\FirstSuShi03.wav" }
    );
    ResourceManager::Instance().loadDialogue(DialogueType::Alcohol, {
        "empty",
        "dialogue\\alcohol\\SecondSuShi01.wav",
        "empty",
        "dialogue\\alcohol\\SecondSuShi02.wav",
        "empty" }
    );
    ResourceManager::Instance().loadDialogue(DialogueType::OldMan, {
        "dialogue\\oldMan\\Oldman01.wav",
        "empty",
        "empty",
        "dialogue\\oldMan\\Oldman02.wav",
        "empty",
        "dialogue\\oldMan\\Oldman03.wav" }
    );
    ResourceManager::Instance().loadDialogue(DialogueType::Young, {
        "dialogue\\young\\Taishou01.wav",
        "empty",
        "dialogue\\young\\Taishou02.wav",
        "empty",
        "dialogue\\young\\Taishou03.wav",
        "empty",
        "dialogue\\young\\Taishou04.wav", }
    );
}