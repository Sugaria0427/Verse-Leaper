#include "GameObjFactory.h"
#include "Enemy_sub.h"
#include "ResourceManager.h"

GameObjFactory* GameObjFactory::gameObjFactory = nullptr;

GameObjFactory* GameObjFactory::instance() {
    if (!gameObjFactory) {
        gameObjFactory = new GameObjFactory();
    }
    return gameObjFactory;
}

Npc* GameObjFactory::createNpc(Tag tag, int x, int y)
{
    Npc* temp;
    switch(tag) {
    case Tag::Npc_SuShi_Old_giveArrow:
        
		temp = new Npc(tag, new Animation(ResourceManager::Instance().getAtlas(AtlasType::atlasNpcSuShi_old), 300), new Box(x, y, 230, 230));
        return temp;
		break;
	case Tag::Npc_SuShi_Old_alcohol:
        temp = new Npc(tag, new Animation(ResourceManager::Instance().getAtlas(AtlasType::atlasNpcSuShi_old), 300), new Box(x, y, 230, 230));
		temp->setExist(false);
        return temp;
        break;
	case Tag::Npc_OldMan:
        temp = new Npc(tag, new Animation(ResourceManager::Instance().getAtlas(AtlasType::atlasNpcOldman), 300), new Box(x, y, 230, 230));
        return temp;
        break;
	case Tag::Npc_SuShi_Young:
        temp = new Npc(tag, new Animation(ResourceManager::Instance().getAtlas(AtlasType::atlasNpcSuShi_young), 300), new Box(x, y, 230, 230));
		temp->setExist(false);
        return temp;
        break;
    default:
        throw std::runtime_error("创建错误");
        break;
    }
	return nullptr;
}

Enemy* GameObjFactory::createEnemy(Tag tag, int x, int y)
{
	Enemy* temp;
    switch(tag) {
    case Tag::Enemy_Dog:
        temp = new EnemyDog(tag, new Animation(ResourceManager::Instance().getAtlas(AtlasType::atlasEnemyDog), 300), new Box(x, y, 250, 200));
        return temp;
        break;
    case Tag::Enemy_Eagle:
        temp = new EnemyEagle(tag, new Animation(ResourceManager::Instance().getAtlas(AtlasType::atlasEnemyEagle), 300), new Box(x, y, 250, 200));
        return temp;
        break;
    case Tag::Enemy_Tiger:
        temp = new EnemyTiger(tag, new Animation(ResourceManager::Instance().getAtlas(AtlasType::atlasEnemyTigerIdleLeft), 300), new Box(x, y, 500, 400));
        return temp;
        break;
    case Tag::Enemy_Boss:
        temp = new EnemyBoss(tag, new Animation(ResourceManager::Instance().getAtlas(AtlasType::atlasEnemyBossIdle), 500), new Box(x, y, 1200, 1000));
        return temp;
        break;
    default:
        throw std::runtime_error("创建错误");
        break;
    }
	return nullptr;
}

Block* GameObjFactory::createBlock(Tag tag, int x, int y)
{
	Block* temp;
	int width = 150;
	int height = 150;
    switch (tag) {
    case Tag::Block_Grass:
        temp =  new Block(tag, new Animation(ResourceManager::Instance().getAtlas(AtlasType::atlasBlock_Grass), 1000), new Box(x, y, width, height));
        return temp;
        break;
	case Tag::Block_GrassUnder:
        temp = new Block(tag, new Animation(ResourceManager::Instance().getAtlas(AtlasType::atlasBlock_GrassUnder), 1000), new Box(x, y, width, height));
        return temp;
		break;
    case Tag::Block_IceGrass:
        temp =  new Block(tag, new Animation(ResourceManager::Instance().getAtlas(AtlasType::atlasBlock_IceGrass), 1000), new Box(x, y, width, height));
        return temp;
        break;
	case Tag::Block_IceGrassUnder:
        temp = new Block(tag, new Animation(ResourceManager::Instance().getAtlas(AtlasType::atlasBlock_IceGrassUnder), 1000), new Box(x, y, width, height));
        return temp;
		break;
    case Tag::Block_Ice:
        temp = new Block(tag, new Animation(ResourceManager::Instance().getAtlas(AtlasType::atlasBlock_Ice), 1000), new Box(x, y, width, height));
        return temp;
        break;
    case Tag::Block_Cloud1:
        temp = new Block(tag, new Animation(ResourceManager::Instance().getAtlas(AtlasType::atlasBlock_Cloud1), 1000), new Box(x, y, width, height));
        temp->setExist(false);
        return temp;
        break;
    case Tag::Block_Cloud2:
        temp = new Block(tag, new Animation(ResourceManager::Instance().getAtlas(AtlasType::atlasBlock_Cloud2), 1000), new Box(x, y, width, height));
        temp->setExist(false);
        return temp;
        break;
    case Tag::Block_Mist_SuShi_Arrow:
        temp = new Block(tag, new Animation(ResourceManager::Instance().getAtlas(AtlasType::atlasBlock_Mist01), 1000), new Box(x, y, width, height));
        return temp;
        break;
    case Tag::Block_Mist02:
        temp = new Block(tag, new Animation(ResourceManager::Instance().getAtlas(AtlasType::atlasBlock_Mist01), 1000), new Box(x, y, width, height));
        return temp;
        break;
    case Tag::Block_JumpPad:
        temp = new Block(tag, new Animation(ResourceManager::Instance().getAtlas(AtlasType::atlasBlock_JumpPad), 1000), new Box(x, y, width, height));
        return temp;
		break;
	case Tag::Block_SavePoint:
        temp = new Block(tag, new Animation(ResourceManager::Instance().getAtlas(AtlasType::atlasBlock_SavePoint), 1000), new Box(x, y, width, height));
		return temp;
		break;
    case Tag::Block_TeleportNext:
        temp = new Block(tag, new Animation(ResourceManager::Instance().getAtlas(AtlasType::atlasBlock_Teleport), 1000), new Box(x, y, width, height * 3));
        return temp;
		break;
    case Tag::Block_TeleportPrior:
        temp = new Block(tag, new Animation(ResourceManager::Instance().getAtlas(AtlasType::atlasBlock_Teleport), 1000), new Box(x, y, width, height * 3));
		return temp;
        break;
	case Tag::Block_TeleportExtra:
		temp = new Block(tag, new Animation(ResourceManager::Instance().getAtlas(AtlasType::atlasBlock_Teleport), 1000), new Box(x, y, width, height * 3));
		return temp;
		break;
    case Tag::Block_Air:
		temp = new Block(tag, new Animation(ResourceManager::Instance().getAtlas(AtlasType::atlasBlock_Air), 1000), new Box(x, y, width, height));
		return temp;
		break;
    case Tag::Block_Board:
        temp = new Block(tag, new Animation(ResourceManager::Instance().getAtlas(AtlasType::atlasBlock_Board), 1000), new Box(x, y, width, height));
        return temp;
		break;
    case Tag::Block_Dead:
        temp = new Block(tag, new Animation(ResourceManager::Instance().getAtlas(AtlasType::atlasBlock_Dead), 1000), new Box(x, y, width, height));
        return temp;
		break;
    case Tag::Block_TowerMist:
		temp = new Block(tag, new Animation(ResourceManager::Instance().getAtlas(AtlasType::atlasBlock_Mist01), 1000), new Box(x, y, width, height));
		return temp;
		break;
    default:
        throw std::runtime_error("创建错误");
        break;
    }
	return nullptr;
}

void GameObjFactory::createBlockRowInMap(Tag tag, int x, int y, int column, std::vector<GameObject*>& dstVec)
{
    for (int i = 0; i < column; i++) {
        dstVec.push_back(createBlock(tag, x + i * 150, y));
    }
}

void GameObjFactory::createBlockAreaInMap(Tag tag, int x, int y, int row, int column, std::vector<GameObject*>& dstVec)
{
    for (int i = 0; i < row; i++) {
        createBlockRowInMap(tag, x, y + i * 150, column, dstVec);
    }
}

DropItem* GameObjFactory::createDropItem(Tag tag, int x, int y)
{
	DropItem* temp;
    switch (tag) {
    case Tag::DropItem_Alcohol:
		temp = new DropItem(tag, new Animation(ResourceManager::Instance().getAtlas(AtlasType::atlasDropItem_Alcohol), 500), new Box(x, y, 100, 100));
        return temp;
        break;
	case Tag::DropItem_Arrow:
		temp =  new DropItem(tag, new Animation(ResourceManager::Instance().getAtlas(AtlasType::atlasDropItem_Arrow), 500), new Box(x, y, 100, 100));
        return temp;
        break;
    case Tag::DropItem_Sword:
        temp =  new DropItem(tag, new Animation(ResourceManager::Instance().getAtlas(AtlasType::atlasDropItem_Sword), 500), new Box(x, y, 100, 100));
        return temp;
        break;
	case Tag::DropItem_DoubleJump:
        temp = new DropItem(tag, new Animation(ResourceManager::Instance().getAtlas(AtlasType::atlasDropItem_DoubleJump), 500), new Box(x, y, 100, 100));
        return temp;
		break;
    case Tag::DropItem_Potion:
		temp = new DropItem(tag, new Animation(ResourceManager::Instance().getAtlas(AtlasType::atlasDropItem_Potion), 500), new Box(x, y, 100, 100));
		return temp;
		break;
    default:
        throw std::runtime_error("创建错误");
		break;
    }
	return nullptr;
}

GameObject* GameObjFactory::createPosterBG(Tag tag, int width, int height)
{
    switch (tag) {
    case Tag::Poster_BG_Initial:
        return new Poster(tag, new Animation(ResourceManager::Instance().getAtlas(AtlasType::atlasInitialBG), 1000), new Box(0, 0, width, height));
        break;
    case Tag::Poster_BG_Tower:
        return new Poster(tag, new Animation(ResourceManager::Instance().getAtlas(AtlasType::atlasTowerBG), 1000), new Box(0, 0, width, height));
        break;
    case Tag::Poster_BG_Tiger:
        return new Poster(tag, new Animation(ResourceManager::Instance().getAtlas(AtlasType::atlasTigerBG), 1000), new Box(0, 0, width, height));
        break;
    case Tag::Poster_BG_Boss:
        return new Poster(tag, new Animation(ResourceManager::Instance().getAtlas(AtlasType::atlasBossBG), 1000), new Box(0, 0, width, height));
        break;
	case Tag::Poster_BG_Transition:
		return new Poster(tag, new Animation(ResourceManager::Instance().getAtlas(AtlasType::atlasTransitionBG), 1000), new Box(0, 0, width, height));
		break;
	case Tag::Poster_BG_Cloud:
		return new Poster(tag, new Animation(ResourceManager::Instance().getAtlas(AtlasType::atlasCloudBG), 1000), new Box(0, 0, width, height));
		break;
    default:
        throw std::runtime_error("创建错误");
        break;
    };
}

GameObject* GameObjFactory::createPoster(Tag tag, int x, int y, int width, int height)
{
    switch (tag){
    case Tag::Poster_mainTower:
        return new Poster(tag, new Animation(ResourceManager::Instance().getAtlas(AtlasType::atlasMainTower), 1000), new Box(x, y, width, height));
		break;
    case Tag::Poster_smallTower:
		return new Poster(tag, new Animation(ResourceManager::Instance().getAtlas(AtlasType::atlasSmallTower), 1000), new Box(x, y, width, height));
		break;
	case Tag::Poster_tree:
		return new Poster(tag, new Animation(ResourceManager::Instance().getAtlas(AtlasType::atlasTree), 1000), new Box(x, y, width, height));
		break;
	case Tag::Poster_wall:
		return new Poster(tag, new Animation(ResourceManager::Instance().getAtlas(AtlasType::atlasWall), 1000), new Box(x, y, width, height));
		break;
    default:
        throw std::runtime_error("创建错误");
		break;
    }
}

Bell* GameObjFactory::createBell(Tag tag, int x, int y)
{
    Bell* temp;
    temp = new Bell(tag, new Animation(ResourceManager::Instance().getAtlas(AtlasType::atlasBell), 500), new Box(x, y, 150, 150));
    return temp;
}

Drum* GameObjFactory::createDrum(Tag tag, int x, int y)
{
    Drum* temp;
    temp = new Drum(tag, new Animation(ResourceManager::Instance().getAtlas(AtlasType::atlasDrum), 500), new Box(x, y, 150, 150));
    return temp;
}
