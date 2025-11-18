#include "GameScene.h"
#include "Maps.h"
#include "Panel.h"
#include "ResourceManager.h"

void GameScene::handleEvent(SDL_Event& event) {
    Player* player = dynamic_cast<Player*>(GameObjManager::instance()->getPlayer());
    switch (event.type) {
    // 鼠标
    case SDL_MOUSEBUTTONDOWN:
        break;
    case SDL_MOUSEBUTTONUP:
        if (event.button.button == SDL_BUTTON_RIGHT
            && player->hasArrow() && player->isExist()&& !player->isInArrowCD()) {
            // 鼠标右键抬起、且获得了箭技能、且player存在、且不在箭冷却时间内，准备发射箭
            player->setWillUseArrow(true);
        }
        else if (event.button.button == SDL_BUTTON_LEFT && !(dialogueBox->isExist())) {
            // 鼠标左键抬起且未弹出对话框，检查是否处于NPC框中（即是否点击npc）
            for (GameObject* obj : GameObjManager::instance()->getVec()) {
                if (obj->getTag() == Tag::Npc_SuShi_Old_giveArrow 
                    && obj->isExist()
                    && obj->getBox()->isPointOn(event.motion.x / Panel::Instance().getCamera()->getZoom() + Panel::Instance().getCamera()->getX(), event.motion.y / Panel::Instance().getCamera()->getZoom() + Panel::Instance().getCamera()->getY())) {
                    dialogueBox->start(DialogueBox::Dialogue::Npc_SuShi_Old_giveArrow);
                    GameObjManager::instance()->getPlayer()->setSpeedX(0);
                }
                else if (obj->getTag() == Tag::Npc_SuShi_Old_alcohol
                    && obj->isExist()
                    && obj->getBox()->isPointOn(event.motion.x / Panel::Instance().getCamera()->getZoom() + Panel::Instance().getCamera()->getX(), event.motion.y / Panel::Instance().getCamera()->getZoom() + Panel::Instance().getCamera()->getY())) {
                    dialogueBox->start(DialogueBox::Dialogue::Npc_SuShi_Old_alcohol);
                    GameObjManager::instance()->getPlayer()->setSpeedX(0);
                }
                else if (obj->getTag() == Tag::Npc_SuShi_Young
                    && obj->isExist()
                    && obj->getBox()->isPointOn(event.motion.x / Panel::Instance().getCamera()->getZoom() + Panel::Instance().getCamera()->getX(), event.motion.y / Panel::Instance().getCamera()->getZoom() + Panel::Instance().getCamera()->getY())) {
                    dialogueBox->start(DialogueBox::Dialogue::Npc_SuShi_Young);
                    GameObjManager::instance()->getPlayer()->setSpeedX(0);
                }
                else if (obj->getTag() == Tag::Npc_OldMan
                    && obj->isExist()
                    && obj->getBox()->isPointOn(event.motion.x / Panel::Instance().getCamera()->getZoom() + Panel::Instance().getCamera()->getX(), event.motion.y / Panel::Instance().getCamera()->getZoom() + Panel::Instance().getCamera()->getY())) {
                    dialogueBox->start(DialogueBox::Dialogue::Npc_OldMan);
                    GameObjManager::instance()->getPlayer()->setSpeedX(0);
				}
                else if(obj->getTag() == Tag::Bell
                    && obj->getBox()->isPointOn(event.motion.x / Panel::Instance().getCamera()->getZoom() + Panel::Instance().getCamera()->getX(), event.motion.y / Panel::Instance().getCamera()->getZoom() + Panel::Instance().getCamera()->getY())) {
                    // 点击了Bell
					Mix_PlayChannel(-1, ResourceManager::Instance().getSound(SoundType::bell), 0);
					Bell* bell = dynamic_cast<Bell*>(obj);
					bell->setGravity(0, 5);
                    for (GameObject* obje : GameObjManager::instance()->getVec()) {
                        if (obje->getTag() == Tag::Block_Board && obje->isExist()) {
							Mix_PlayChannel(-1, ResourceManager::Instance().getSound(SoundType::board), 0);
							obje->setExist(false);
                        }
                        if(obje->getTag() == Tag::Block_TowerMist && obje->isExist()){
                            obje->setExist(false);
						}
                    }

				}
            }
            if (!(dialogueBox->isExist())                                   // 按下左键且未弹出对话框
                && GameObjManager::instance()->getPlayer()->hasSword()      // 且获得了剑技能
                && GameObjManager::instance()->getPlayer()->isExist()) {    // 且player存在) 
                // 则攻击
                Player* player = dynamic_cast<Player*>(GameObjManager::instance()->getPlayer());
                player->useSword();      
            }
        }
        else if (event.button.button == SDL_BUTTON_LEFT && dialogueBox->isExist()) {
            // 鼠标左键抬起且弹出对话框
            dialogueBox->next();
        }
        break;
    case SDL_MOUSEWHEEL:
        if (event.wheel.y > 0) {
            Panel::Instance().getCamera()->setZoom(Panel::Instance().getCamera()->getZoom() + 0.1);
        }
        else if (event.wheel.y < 0) {
            Panel::Instance().getCamera()->setZoom(Panel::Instance().getCamera()->getZoom() - 0.1);
        }
        break;
    // 键盘
    case SDL_KEYDOWN:
        if (this->dialogueBox->isExist()) { // 弹出对话框，仅有空格可被操控
            if (event.key.keysym.scancode == SDL_SCANCODE_SPACE) {
                dialogueBox->next();
            }
        }
        else {  // 未弹出对话框，可以操作人物
            if (event.key.keysym.scancode == SDL_SCANCODE_SPACE && event.key.repeat == 0) {
                Player* player = dynamic_cast<Player*>(GameObjManager::instance()->getPlayer());
                player->setWillJump(true);
            }
            if (event.key.keysym.scancode == SDL_SCANCODE_K 
                && event.key.repeat == 0 
                && GameObjManager::instance()->getPlayer()->hasAlcohol()) {
                Player* player = dynamic_cast<Player*>(GameObjManager::instance()->getPlayer());
                player->useAlcohol();
            }
            if(event.key.keysym.scancode == SDL_SCANCODE_X 
                && event.key.repeat == 0 
                && GameObjManager::instance()->getPlayer()->getPotion()) {
                Player* player = dynamic_cast<Player*>(GameObjManager::instance()->getPlayer());
                player->usePotion();
			}
            if (event.key.keysym.scancode == SDL_SCANCODE_C                 // 按下c键脱离/跟随玩家
                && event.key.repeat == 0                                    // 且不是重复按键
                ) {
                isCameraFollowing_ = !isCameraFollowing_;
            }
            if (event.key.keysym.scancode == SDL_SCANCODE_N                 // 按下n键Prior
                && event.key.repeat == 0                                    // 且不是重复按键
                ) {
                MapManager::instance()->setTeleportFlag(MapManager::TeleportFlag::Prior);
            }
            if (event.key.keysym.scancode == SDL_SCANCODE_M                 // 按下m键Next
                && event.key.repeat == 0                                    // 且不是重复按键
                ) {
                MapManager::instance()->setTeleportFlag(MapManager::TeleportFlag::Next);
            }
            if (event.key.keysym.scancode == SDL_SCANCODE_B                 // 按下b键Extra
                && event.key.repeat == 0                                    // 且不是重复按键
                ) {
                MapManager::instance()->setTeleportFlag(MapManager::TeleportFlag::Extra);
            }
            if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE            // 按下esc键退出到主菜单
                && event.key.repeat == 0                                    // 且不是重复按键
                ) {
                SceneManager::Instance()->switchTo(SceneManager::SceneType::Menu);
            }
        }
    }
}

void GameScene::handleState(MouseInput& msInput)
{
    // 获取状态
    SDL_GetMouseState(&(msInput.mouseX), &(msInput.mouseY));
    const Uint8* GSkbState = SDL_GetKeyboardState(NULL);
    SDL_GetMouseState(&(msInput.mouseX), &(msInput.mouseY));
    const Uint8* kbState = SDL_GetKeyboardState(NULL);
    // 处理状态
    Button::updateButtonHover(msInput, buttonVec);
    {
        if (!dialogueBox->isExist()) {
            Player* player = dynamic_cast<Player*>(GameObjManager::instance()->getPlayer());
            // 对话框未弹出，主角可移动
            bool prevRunning = isRunning;   // 上一帧运动状态：用于控制走路音效的播放与暂停
            bool prevFalling = isFalling;
            isRunning = false;
            isFalling = GameObjManager::instance()->getPlayer()->getSpeed().getY();
            GameObjManager::instance()->getPlayer()->setSpeedX(0);
            if (kbState[SDL_SCANCODE_A]) {
                GameObjManager::instance()->getPlayer()->addSpeed(-1, 0);   // 向左移动
                isRunning = true;
            }
            if (kbState[SDL_SCANCODE_D]) {
                GameObjManager::instance()->getPlayer()->addSpeed(1, 0);    // 向右移动
                isRunning = true;
            }
        }
        // 摄像机移动
        if(!isCameraFollowing_){
            Panel::Instance().getCamera()->setSpeed(Vector2(0, 0));
            if (kbState[SDL_SCANCODE_RIGHT]) {
                Panel::Instance().getCamera()->addSpeed(Vector2(1, 0));
            }
            if (kbState[SDL_SCANCODE_LEFT]) {
                Panel::Instance().getCamera()->addSpeed(Vector2(-1, 0));
            }
            if (kbState[SDL_SCANCODE_UP]) {
                Panel::Instance().getCamera()->addSpeed(Vector2(0, -1));
            }
            if (kbState[SDL_SCANCODE_DOWN]) {
                Panel::Instance().getCamera()->addSpeed(Vector2(0, 1));
            }
            Panel::Instance().getCamera()->setSpeed(Panel::Instance().getCamera()->getSpeed().getUnit());
        }
    }
}

void GameScene::draw(SDL_Renderer* SDL_renderer) {
    //drawBackground(SDL_renderer);           // 绘制背景
    drawButtonVec(SDL_renderer);            // 绘制按钮
    drawGameObj(SDL_renderer);              // 绘制游戏对象
    this->dialogueBox->draw(SDL_renderer);  // 绘制对话框
    //CollisionManager::instance()->onDebugDraw(SDL_renderer);    // debug模式绘制碰撞箱
}

void GameScene::update(int delta) {
    MapManager::instance()->update(delta);
    // 更新游戏对象
    for (GameObject*& obj : GameObjManager::instance()->getVec()) {
        // 更新位置坐标与动画
        obj->update(delta);
    }
    // 更新碰撞箱位置
    CollisionManager::instance()->updateCollision();
    // 更新摄像机位置坐标
    int x = 0;
    int y = 0;
    int width = MapManager::instance()->getMapSize().getX();
    int height = MapManager::instance()->getMapSize().getY();
    if (isCameraFollowing_) {
        if ((GameObjManager::instance()->getPlayer()->getBoxCenterX() - ((Panel::Instance().getCamera()->getWidth() / 2) / Panel::Instance().getCamera()->getZoom())) < x)
            Panel::Instance().getCamera()->setX(x);
        else if ((GameObjManager::instance()->getPlayer()->getBoxCenterX() + ((Panel::Instance().getCamera()->getWidth() / 2) / Panel::Instance().getCamera()->getZoom())) > width)
            Panel::Instance().getCamera()->setX(width - Panel::Instance().getCamera()->getWidth() / Panel::Instance().getCamera()->getZoom());
        else
            Panel::Instance().getCamera()->setX(GameObjManager::instance()->getPlayer()->getBoxCenterX() - ((Panel::Instance().getCamera()->getWidth() / 2) / Panel::Instance().getCamera()->getZoom()));
        if ((GameObjManager::instance()->getPlayer()->getBoxCenterY() - ((Panel::Instance().getCamera()->getHeight() / 2) / Panel::Instance().getCamera()->getZoom())) < y)
            Panel::Instance().getCamera()->setY(y);
        else if ((GameObjManager::instance()->getPlayer()->getBoxCenterY() + ((Panel::Instance().getCamera()->getHeight() / 2) / Panel::Instance().getCamera()->getZoom())) > height)
            Panel::Instance().getCamera()->setY(height - Panel::Instance().getCamera()->getHeight() / Panel::Instance().getCamera()->getZoom());
        else
            Panel::Instance().getCamera()->setY(GameObjManager::instance()->getPlayer()->getBoxCenterY() - ((Panel::Instance().getCamera()->getHeight() / 2) / Panel::Instance().getCamera()->getZoom()));
    }
    else {
        if ((Panel::Instance().getCamera()->getX() / Panel::Instance().getCamera()->getZoom() < x))
            Panel::Instance().getCamera()->setX(x);
        else if (Panel::Instance().getCamera()->getX() + Panel::Instance().getCamera()->getWidth() / Panel::Instance().getCamera()->getZoom() > width)
            Panel::Instance().getCamera()->setX(width - Panel::Instance().getCamera()->getWidth() / Panel::Instance().getCamera()->getZoom());
        else
            Panel::Instance().getCamera()->setX(Panel::Instance().getCamera()->getX() + Panel::Instance().getCamera()->getSpeed().getX() * 10);
        if (Panel::Instance().getCamera()->getY() / Panel::Instance().getCamera()->getZoom() < y)
            Panel::Instance().getCamera()->setY(y);
        else if (Panel::Instance().getCamera()->getY() + Panel::Instance().getCamera()->getHeight() / Panel::Instance().getCamera()->getZoom() > height)
            Panel::Instance().getCamera()->setY(height - Panel::Instance().getCamera()->getHeight() / Panel::Instance().getCamera()->getZoom());
        else
            Panel::Instance().getCamera()->setY(Panel::Instance().getCamera()->getY() + Panel::Instance().getCamera()->getSpeed().getY() * 10);
    }
    // 检测玩家是否死亡，若死亡则切换至最后存档点地图
    Player* player = dynamic_cast<Player*>(GameObjManager::instance()->getPlayer());
    if (GameObjManager::instance()->getPlayer()->IsDead()) {
        MapManager::instance()->switchMap(player->getLastSavePointMap());
        player->setBoxX(player->getLastSavePointPosition().getX());
        player->setBoxY(player->getLastSavePointPosition().getY());
        player->setIsDead(false);
    }
    // 过渡NPC不存在
    if (player->hasAlcohol()) {
        for (GameObject* obj : GameObjManager::instance()->getVec()) {
            if (obj->getTag() == Tag::Npc_SuShi_Old_giveArrow) {
                obj->setExist(false);
            }
        }
    }
    //使用酒之后让npc出现
    if(player->isUsedAlcohol()){
        for (GameObject* obj : GameObjManager::instance()->getVec()) {
            if (obj->getTag() == Tag::Npc_SuShi_Old_alcohol) {
                obj->setExist(true);
            }
        }
        player->setIsUsedAlcohol(false);
	}
    
}

void GameScene::onEnter(){
    // 对话框创建
    dialogueBox = new DialogueBox(30, 420, 1200, 300);
    // 不同地图创建
    MapManager::instance()->addMap("InitialMap", new InitialMap(42 * 150, 13 * 150));
    MapManager::instance()->addMap("TowerMap", new TowerMap(22 * 150, 11 * 150));
    MapManager::instance()->addMap("TransitionMap", new TransitionMap(46 * 150, 20 * 150));
    MapManager::instance()->addMap("TigerMap", new TigerMap(28 * 150, 10 * 150));
    MapManager::instance()->addMap("CloudMap", new CloudMap(37 * 150, 23 * 150));
    MapManager::instance()->addMap("BossMap", new BossMap(36 * 150, 21 * 150));
    // 初始地图切换
    MapManager::instance()->setInitialMap("InitialMap");
}

void GameScene::onExit() {
    // 对话框销毁
    delete dialogueBox;
    // 游戏对象销毁
    GameObjManager::instance()->clearVec();
    CollisionManager::instance()->clearCollisionBoxVec();
	//停止所有音效
	Mix_HaltChannel(-1);
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