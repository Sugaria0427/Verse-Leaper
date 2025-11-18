#pragma once
#include<SDL.h>
#include<SDL_mixer.h>
#include<iostream>
#include<vector>
#include"Renderer.h"
#include"SceneManager.h"
#include"ResourceManager.h"
#include"MenuScene.h"
#include"GameScene.h"
#include"OptionScene.h"
#include"Button.h"
#include"MouseInput.h"
#include"Atlas.h"
#include"Player.h"
#include"Npc.h"
#include"Camera.h"
#include"Panel.h"
#undef main

#define WIDTH 1280
#define HEIGHT 720
#define FRAME_RATE 50
#define FRAME_TIME 1000 / FRAME_RATE

Renderer* renderer;
Scene* menuScene;
Scene* gameScene;
Scene* optionScene;
bool running = true;

std::vector<Mix_Chunk*> dialogueVec_giveArrow;
std::vector<Mix_Chunk*> dialogueVec_alcohol;
std::vector<Mix_Chunk*> dialogueVec_OldMan;
std::vector<Mix_Chunk*> dialogueVec_Young;

static void initAudioAndScenes();
static void initAudio();
static void creatScenes();
static void creatMenuScene();
static void creatGameScene();
static void creatOptionScene();