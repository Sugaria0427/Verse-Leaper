#pragma once
#include "Player.h"
#include "Npc.h"
#include "Block.h"
#include "Enemy.h"
#include "DropItem.h"
#include "Poster.h"
#include "Bell.h"
#include "Drum.h"

class GameObjFactory
{
public:
	static GameObjFactory* instance();
	Npc* createNpc(Tag tag, int x, int y);
	Enemy* createEnemy(Tag tag, int x, int y);
	Block* createBlock(Tag tag, int x, int y);
	DropItem* createDropItem(Tag tag, int x, int y);
	Bell* createBell(Tag tag, int x, int y);
	Drum* createDrum(Tag tag, int x, int y);
    GameObject* createPosterBG(Tag tag, int width, int height);
	GameObject* createPoster(Tag tag, int x, int y, int width, int height);
	void createBlockRowInMap(Tag tag, int x, int y, int column, std::vector<GameObject*>& dstVec);
	void createBlockAreaInMap(Tag tag, int x, int y, int row, int column, std::vector<GameObject*>& dstVec);
private:
	GameObjFactory() {}
	static GameObjFactory* gameObjFactory;
};