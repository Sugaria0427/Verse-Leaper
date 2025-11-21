#include "GameScene.h"
#include "Panel.h"
#include "Camera.h"
#include "MapManager.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "GameObjectManager.h"
#include "CollisionManager.h"
#include "Player.h"
#include "Bell.h"
#include "DialogueBox.h"
#include "MouseInput.h"

void GameScene::handleEvent(SDL_Event& event) {
    switch (event.type) {
    case SDL_MOUSEBUTTONUP:
        handleMouseButtonUpEvent(event);
        break;
    case SDL_MOUSEWHEEL:
        handleMouseWheelEvent(event);
        break;
    case SDL_KEYDOWN:
        handleKeyDownEvent(event);
        break;
    default:
        break;
    }
}

void GameScene::handleState(MouseInput& msInput)
{
    // 获取状态信息
    SDL_GetMouseState(&(msInput.mouseX), &(msInput.mouseY));    // 获取鼠标位置
    const Uint8* kbState = SDL_GetKeyboardState(NULL);          // 获取键盘状态
    Button::updateButtonsHover(msInput, buttonVec);              // 更新按钮悬停状态

    // 处理状态信息
    handlePlayerMovementState(kbState);
    handleCameraMovementState(kbState);
}

void GameScene::draw(SDL_Renderer* SDL_renderer) {
    drawButtonVec(SDL_renderer);            // 绘制按钮
    drawGameObj(SDL_renderer);              // 绘制游戏对象
    this->dialogueBox->draw(SDL_renderer);  // 绘制对话框
    //CollisionManager::instance()->onDebugDraw(SDL_renderer);    // debug模式绘制碰撞箱
}

void GameScene::update(int delta) 
{
    MapManager::instance()->update(delta);

    for (GameObject*& obj : GameObjManager::instance()->getVec()) {
        obj->update(delta);
    }

    CollisionManager::instance()->updateCollision();

    updateCameraPosition(delta);

    // 检测玩家是否死亡，若死亡则切换至最后存档点地图
    Player* player = dynamic_cast<Player*>(GameObjManager::instance()->getPlayer());
    if (GameObjManager::instance()->getPlayer()->IsDead()) {
        MapManager::instance()->switchMap(player->getLastSavePointMap());
        player->setBoxX(player->getLastSavePointPosition().getX());
        player->setBoxY(player->getLastSavePointPosition().getY());
        player->setIsDead(false);
    }

    // 玩家有酒则苏轼不存在
    if (player->hasAlcohol()) {
        for (GameObject* obj : GameObjManager::instance()->getVec()) {
            if (obj->getTag() == Tag::Npc_SuShi_Old_giveArrow) {
                obj->setExist(false);
            }
        }
    }

    //使用酒之后让苏轼出现
    if(player->isUsedAlcohol()){
        for (GameObject* obj : GameObjManager::instance()->getVec()) {
            if (obj->getTag() == Tag::Npc_SuShi_Old_alcohol) {
                obj->setExist(true);
            }
        }
        player->setIsUsedAlcohol(false);
	}
    
}

void GameScene::onEnter()
{
    dialogueBox = new DialogueBox(30, 420, 1200, 300);      // 创建对话框

    MapManager::instance()->creatMaps();                    // 创建地图

    MapManager::instance()->setInitialMap("InitialMap");    // 设置初始地图
}

void GameScene::onExit() {
    
    delete dialogueBox;     // 对话框销毁

    // 游戏对象销毁
    GameObjManager::instance()->clearVec();
    CollisionManager::instance()->clearCollisionBoxVec();
	
	Mix_HaltChannel(-1);    //停止所有音效
}

void GameScene::drawGameObj(SDL_Renderer* SDL_renderer)
{
    for (GameObject* GameObj : GameObjManager::instance()->getVec()) {
        GameObj->draw(SDL_renderer);
    }
	GameObjManager::instance()->getPlayer()->draw(SDL_renderer);
}

void GameScene::drawBackground(SDL_Renderer* SDL_renderer) {
    SDL_Rect* winWect = Panel::Instance().getCamera()->getWindowRect();
    SDL_RenderCopy(SDL_renderer, this->backgroundImage->getImgTexture(), winWect, NULL);
    delete winWect;
}

void GameScene::updateCameraPosition(int delta) const
{
    // 获取必要参数
    int map_x = 0;
    int map_y = 0;
    int map_width = MapManager::instance()->getMapSize().getX();
    int map_height = MapManager::instance()->getMapSize().getY();
    double player_center_x = GameObjManager::instance()->getPlayer()->getBoxCenterX();
    double player_center_y = GameObjManager::instance()->getPlayer()->getBoxCenterY();
    double camera_x = Panel::Instance().getCamera()->getX();
    double camera_y = Panel::Instance().getCamera()->getY();
    double camera_world_width = Panel::Instance().getCamera()->getWidth() / Panel::Instance().getCamera()->getZoom();
    double camera_world_height = Panel::Instance().getCamera()->getHeight() / Panel::Instance().getCamera()->getZoom();
    // 根据摄像机是否跟随玩家，更新摄像机位置
    if (isCameraFollowing_) {
        if ((player_center_x - (camera_world_width / 2)) < map_x)
            Panel::Instance().getCamera()->setX(map_x);                             // 左边越界
        else if ((player_center_x + (camera_world_width / 2)) > map_width)
            Panel::Instance().getCamera()->setX(map_width - camera_world_width);    // 右边越界
        else
            Panel::Instance().getCamera()->setX(player_center_x - (camera_world_width / 2));// 正常跟随
        
        if ((player_center_y - camera_world_height / 2) < map_y)
            Panel::Instance().getCamera()->setY(map_y);                             // 上边越界
        else if ((player_center_y + camera_world_height / 2) > map_height)
            Panel::Instance().getCamera()->setY(map_height - camera_world_height);  // 下边越界
        else
            Panel::Instance().getCamera()->setY(player_center_y - camera_world_height / 2);// 正常跟随
    }
    else {
        if ((camera_x < map_x))
            Panel::Instance().getCamera()->setX(map_x);
        else if (camera_x + camera_world_width > map_width)
            Panel::Instance().getCamera()->setX(map_width - camera_world_width);
        else
            Panel::Instance().getCamera()->setX(camera_x + Panel::Instance().getCamera()->getSpeed().getX() * 10);

        if (camera_y < map_y)
            Panel::Instance().getCamera()->setY(map_y);
        else if (camera_y + camera_world_height > map_height)
            Panel::Instance().getCamera()->setY(map_height - camera_world_height);
        else
            Panel::Instance().getCamera()->setY(camera_y + Panel::Instance().getCamera()->getSpeed().getY() * 10);
    }
}

void GameScene::handleMouseButtonUpEvent(SDL_Event& event)
{
    switch (event.button.button) {
    case SDL_BUTTON_RIGHT:
        tryUseArrow();
        break;
    case SDL_BUTTON_LEFT:
        if (dialogueBox->isExist()) 
            dialogueBox->next();    // 对话框存在，点击左键翻页
        else {
            tryTriggerMouseInteractiveObjs(event);
            tryUseSword();
        }
        break;
    default:
        break;
    }
}

void GameScene::tryTriggerMouseInteractiveObjs(SDL_Event& event)
{
    // 遍历所有游戏对象，检查是否点击了NPC或其他可交互物体
    for (GameObject* obj : GameObjManager::instance()->getVec()) {
        if (!obj->isExist()) continue;  // 对象不存在，跳过

        // 获得鼠标在世界坐标系中的位置
        double mouseWorld_X = event.motion.x / Panel::Instance().getCamera()->getZoom() + Panel::Instance().getCamera()->getX();
        double mouseWorld_Y = event.motion.y / Panel::Instance().getCamera()->getZoom() + Panel::Instance().getCamera()->getY();

        if (!obj->getBox()->isPointOn(mouseWorld_X, mouseWorld_Y)) continue; // 鼠标未点击在该对象上，跳过

        switch (obj->getTag()) {
        case Tag::Npc_SuShi_Old_giveArrow:
            dialogueBox->start(DialogueBox::Dialogue::Npc_SuShi_Old_giveArrow);
            break;
        case Tag::Npc_SuShi_Old_alcohol:
            dialogueBox->start(DialogueBox::Dialogue::Npc_SuShi_Old_alcohol);
            break;
        case Tag::Npc_SuShi_Young:
            dialogueBox->start(DialogueBox::Dialogue::Npc_SuShi_Young);
            break;
        case Tag::Npc_OldMan:
            dialogueBox->start(DialogueBox::Dialogue::Npc_OldMan);
            break;
        case Tag::Bell: 
            triggerBell(obj);
            break;
        default:
            break;
        }
        GameObjManager::instance()->getPlayer()->setSpeedX(0);  // 点击了某个对象，停止玩家移动
    }
}

void GameScene::triggerBell(GameObject* obj)
{
    Bell* bell = dynamic_cast<Bell*>(obj);
    Mix_PlayChannel(-1, ResourceManager::Instance().getSound(SoundType::bell), 0);
    bell->setGravity(0, 5);
    for (GameObject* obj : GameObjManager::instance()->getVec()) {
        if (!obj->isExist()) continue;
        if (obj->getTag() == Tag::Block_Board) {
            Mix_PlayChannel(-1, ResourceManager::Instance().getSound(SoundType::board), 0);
            obj->setExist(false);
        }
        if (obj->getTag() == Tag::Block_TowerMist) {
            obj->setExist(false);
        }
    }
}

void GameScene::tryUseArrow()
{
    Player* player = dynamic_cast<Player*>(GameObjManager::instance()->getPlayer());
    if (player->hasArrow() && player->isExist() && !player->isInArrowCD()) {
        // 鼠标右键抬起、且获得了箭技能、且player存在、且不在箭冷却时间内，准备发射箭
        player->setWillUseArrow(true);
    }
}

void GameScene::tryUseSword()
{
    Player* player = dynamic_cast<Player*>(GameObjManager::instance()->getPlayer());
    if (player->hasSword() && player->isExist()) player->useSword();
}

void GameScene::handleMouseWheelEvent(SDL_Event& event)
{
    if (event.wheel.y > 0) {
        Panel::Instance().getCamera()->setZoom(Panel::Instance().getCamera()->getZoom() + 0.1);
    }
    else if (event.wheel.y < 0) {
        Panel::Instance().getCamera()->setZoom(Panel::Instance().getCamera()->getZoom() - 0.1);
    }
}

void GameScene::handleKeyDownEvent(SDL_Event& event)
{
    if (this->dialogueBox->isExist()) { // 弹出对话框，仅有空格可被操控
        if (event.key.keysym.scancode == SDL_SCANCODE_SPACE) {
            dialogueBox->next();
        }
    }
    else {
        if (event.key.repeat != 0) return;  // 忽略重复按键事件

        Player* player;
        switch (event.key.keysym.scancode) {
        case SDL_SCANCODE_SPACE:
            player = dynamic_cast<Player*>(GameObjManager::instance()->getPlayer());
            player->setWillJump(true);
            break;
        case SDL_SCANCODE_K:
            player = dynamic_cast<Player*>(GameObjManager::instance()->getPlayer());
            if (player->hasAlcohol()) player->useAlcohol();
            break;
        case SDL_SCANCODE_X:
            player = dynamic_cast<Player*>(GameObjManager::instance()->getPlayer());
            if (player->getPotion()) player->usePotion();
            break;
        case SDL_SCANCODE_C:
            isCameraFollowing_ = !isCameraFollowing_;       // 按下c键脱离/跟随玩家
            break;
        case SDL_SCANCODE_N:
            MapManager::instance()->setTeleportFlag(MapManager::TeleportFlag::Prior);
            break;
        case SDL_SCANCODE_M:
            MapManager::instance()->setTeleportFlag(MapManager::TeleportFlag::Next);
            break;
        case SDL_SCANCODE_B:
            MapManager::instance()->setTeleportFlag(MapManager::TeleportFlag::Extra);
            break;
        case SDL_SCANCODE_ESCAPE:
            SceneManager::Instance()->switchTo(SceneType::Menu);
            break;
        default:
            break;
        }
    }
}

void GameScene::handlePlayerMovementState(const Uint8* kbState)
{
    if (dialogueBox->isExist()) return; // 对话框存在，主角不能受键盘驱动而移动

    Player* player = dynamic_cast<Player*>(GameObjManager::instance()->getPlayer());
    // 水平移动
    GameObjManager::instance()->getPlayer()->setSpeedX(0);  // 先将水平速度置0
    if (kbState[SDL_SCANCODE_A])
        GameObjManager::instance()->getPlayer()->addSpeed(-1, 0);   // 向左移动
    if (kbState[SDL_SCANCODE_D])
        GameObjManager::instance()->getPlayer()->addSpeed(1, 0);    // 向右移动
}

void GameScene::handleCameraMovementState(const Uint8* kbState)
{
    if (isCameraFollowing_) return; // 摄像机跟随主角，不能受键盘驱动而移动

    // 假设速度为0
    Panel::Instance().getCamera()->setSpeed(Vector2(0, 0));
    // 根据键盘状态累加速度
    if (kbState[SDL_SCANCODE_RIGHT]) 
        Panel::Instance().getCamera()->addSpeed(Vector2(1, 0));
    if (kbState[SDL_SCANCODE_LEFT]) 
        Panel::Instance().getCamera()->addSpeed(Vector2(-1, 0));
    if (kbState[SDL_SCANCODE_UP])
        Panel::Instance().getCamera()->addSpeed(Vector2(0, -1));
    if (kbState[SDL_SCANCODE_DOWN]) 
        Panel::Instance().getCamera()->addSpeed(Vector2(0, 1));
    // 保持速度单位不变（使其斜向跳跃速度不突变）
    Panel::Instance().getCamera()->setSpeed(Panel::Instance().getCamera()->getSpeed().getUnit());
    
}