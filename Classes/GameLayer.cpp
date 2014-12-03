//
//  GameLayer.cpp
//  Aircraft
//
//  Created by lc on 11/23/14.
//
//

#include "GameLayer.h"

GameLayer::GameLayer(void) {
    
}

GameLayer::~GameLayer(void) {
    
}

Scene* GameLayer::createScene() {
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameLayer::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameLayer::init()
{
    if ( !Layer::init()) {
        return false;
    }
    if (!CocosDenshion::SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying()) {
        CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("game_music.mp3",true);
    }

    
    //Size visibleSize = Director::getInstance()->getVisibleSize();
    
    //加载background1
    bg1 = Sprite::createWithSpriteFrame(PlistHandler::getInstance()->getFrameByName("background.png"));
    bg1->setAnchorPoint(Point(0, 0));
    bg1->setPosition(Point(0, 0));
    this->addChild(bg1);
    
    //加载background2
    bg2 = Sprite::createWithSpriteFrame(PlistHandler::getInstance()->getFrameByName("background.png"));
    bg2->setAnchorPoint(Point(0, 0));
    bg2->setPosition(Point(0, bg1->getContentSize().height));
    this->addChild(bg2);
    
    //执行任务计划，实现背景滚动
    this->schedule(schedule_selector(GameLayer::backgroundMove), 0.005f);
    
    //加入planeLayer
    this->planeLayer = PlaneLayer::create();
    this->addChild(planeLayer, 0, TAG_AIRPLANE);
    
    //加入bulletLayer
    this->bulletLayer = BulletLayer::create();
    this->addChild(bulletLayer);
    this->bulletLayer->startShoot(1);
    
    // add enemyLayer
    this->enemyLayer = EnemyLayer::create();
    this->addChild(enemyLayer);
    
    // add controlLayer
    this->controlLayer = ControlLayer::create();
    this->addChild(controlLayer);
    
    // add UFOLayer
    this->ufoLayer = UFOLayer::create();
    this->addChild(ufoLayer);
    
    // add mutiBulletLayer
    this->mutiBulletLayer = MutiBulletLayer::create();
    this->addChild(mutiBulletLayer);
    
    this->scheduleUpdate();
        
    return true;
}

//背景滚动
void GameLayer::backgroundMove(float dt) {
    bg1->setPositionY(bg1->getPositionY() - 2);
    bg2->setPositionY(bg1->getContentSize().height + bg1->getPositionY() - 2);
    
    if (bg2->getPositionY() == 0) {
        bg1->setPositionY(0);
    }
}

void GameLayer::update(float dt) {
    //log("update frame\n");
    updateBullet();
    updateMutiBulelt();
    updateUFO();
    if (updateEnemy()) {
        auto pScene = GameOverScene::create(m_score);
        auto animateScene=TransitionMoveInT::create(0.8f, pScene);
        Director::getInstance()->replaceScene(animateScene);
    }
}

void GameLayer::updateBullet() {
    __Array* bulletsToDel = __Array::create();
    bulletsToDel->retain();
    Ref *bt, *et;
    
    CCARRAY_FOREACH(this->bulletLayer->m_pAllBullet, bt) { // 遍历子弹
        auto bullet = (Sprite*) bt;
        // 遍历enemy1
        __Array* enemy1ToDel = __Array::create();
        enemy1ToDel->retain();
        CCARRAY_FOREACH(this->enemyLayer->m_allEnemy1, et) {
            Enemy* enemy1 = (Enemy*) et;
            if (bullet->getBoundingBox().intersectsRect(enemy1->getBoundingBox())) {
                if (enemy1->getLife() > 1) {
                    enemy1->loseLife();
                    bulletsToDel->addObject(bullet);
                }
                else if (enemy1->getLife() == 1) {
                    enemy1->loseLife();
                    bulletsToDel->addObject(bullet);
                    enemy1ToDel->addObject(enemy1);
                    // 加分
                    m_score += ENEMY1_LIFE;
                    this->controlLayer->updateScore(m_score);
                    enemy1->cleanup();
                }
                else {
                    
                }
            }
            
        }
        
        CCARRAY_FOREACH(enemy1ToDel, et) {
            Enemy* enemy1 = (Enemy*) et;
            this->enemyLayer->blowupEnemy1(enemy1);
        }
        enemy1ToDel->release();
    }
    CCARRAY_FOREACH(bulletsToDel, bt) {
        Sprite* bullet = (Sprite*) bt;
        this->bulletLayer->removeBullet(bullet);
    }
    bulletsToDel->removeAllObjects();
    
    CCARRAY_FOREACH(this->bulletLayer->m_pAllBullet, bt) {
        auto bullet = (Sprite*) bt;
        // 遍历enemy2
        __Array* enemy2ToDel = __Array::create();
        enemy2ToDel->retain();
        CCARRAY_FOREACH(this->enemyLayer->m_allEnemy2, et) {
            Enemy* enemy2 = (Enemy*) et;
            if (bullet->getBoundingBox().intersectsRect(enemy2->getBoundingBox())) {
                if (enemy2->getLife() > 1) {
                    enemy2->loseLife();
                    bulletsToDel->addObject(bullet);
                }
                else if (enemy2->getLife() == 1) {
                    enemy2->loseLife();
                    bulletsToDel->addObject(bullet);
                    enemy2ToDel->addObject(enemy2);
                    // 加分
                    m_score += ENEMY2_LIFE;
                    this->controlLayer->updateScore(m_score);
                    enemy2->cleanup();
                }
                else {
                    
                }
            }
        }
        
        CCARRAY_FOREACH(enemy2ToDel, et) {
            Enemy* enemy2 = (Enemy*) et;
            this->enemyLayer->blowupEnemy2(enemy2);
        }
        enemy2ToDel->release();
    }
    CCARRAY_FOREACH(bulletsToDel, bt) {
        Sprite* bullet = (Sprite*) bt;
        this->bulletLayer->removeBullet(bullet);
    }
    bulletsToDel->removeAllObjects();
    
    CCARRAY_FOREACH(this->bulletLayer->m_pAllBullet, bt) {
        auto bullet = (Sprite*) bt;
        // 遍历enemy3
        __Array* enemy3ToDel = __Array::create();
        enemy3ToDel->retain();
        CCARRAY_FOREACH(this->enemyLayer->m_allEnemy3, et) {
            Enemy* enemy3 = (Enemy*) et;
            if (bullet->getBoundingBox().intersectsRect(enemy3->getBoundingBox())) {
                if (enemy3->getLife() > 1) {
                    enemy3->loseLife();
                    bulletsToDel->addObject(bullet);
                }
                else if (enemy3->getLife() == 1) {
                    enemy3->loseLife();
                    bulletsToDel->addObject(bullet);
                    enemy3ToDel->addObject(enemy3);
                    // 加分
                    m_score += ENEMY3_LIFE;
                    this->controlLayer->updateScore(m_score);
                    enemy3->cleanup();
                }
                else {
                    
                }
            }
        }
        
        CCARRAY_FOREACH(enemy3ToDel, et) {
            Enemy* enemy3 = (Enemy*) et;
            this->enemyLayer->blowupEnemy3(enemy3);
        }
        enemy3ToDel->release();
    }
    
    CCARRAY_FOREACH(bulletsToDel, bt) {
        Sprite* bullet = (Sprite*) bt;
        this->bulletLayer->removeBullet(bullet);
    }
    bulletsToDel->removeAllObjects();
    bulletsToDel->release();
}

void GameLayer::updateMutiBulelt() {
    __Array* bulletsToDel = __Array::create();
    bulletsToDel->retain();
    Ref *bt, *et;

    CCARRAY_FOREACH(this->mutiBulletLayer->m_allMutiBullet, bt) { // 遍历子弹
        auto bullet = (Sprite*) bt;
        // 遍历enemy1
        __Array* enemy1ToDel = __Array::create();
        enemy1ToDel->retain();
        CCARRAY_FOREACH(this->enemyLayer->m_allEnemy1, et) {
            Enemy* enemy1 = (Enemy*) et;
            if (bullet->getBoundingBox().intersectsRect(enemy1->getBoundingBox())) {
                if (enemy1->getLife() > 1) {
                    enemy1->loseLife();
                    bulletsToDel->addObject(bullet);
                }
                else if (enemy1->getLife() == 1) {
                    enemy1->loseLife();
                    bulletsToDel->addObject(bullet);
                    enemy1ToDel->addObject(enemy1);
                    // 加分
                    m_score += ENEMY1_LIFE;
                    this->controlLayer->updateScore(m_score);
                    enemy1->cleanup();
                }
                else {
                    
                }
            }
        }
        
        CCARRAY_FOREACH(enemy1ToDel, et) {
            Enemy* enemy1 = (Enemy*) et;
            this->enemyLayer->blowupEnemy1(enemy1);
        }
        enemy1ToDel->release();
    }
    
    CCARRAY_FOREACH(bulletsToDel, bt) {
        Sprite* bullet = (Sprite*) bt;
        this->mutiBulletLayer->removeMutiBullet(bullet);
    }
    
    bulletsToDel->removeAllObjects();
    
    CCARRAY_FOREACH(this->mutiBulletLayer->m_allMutiBullet, bt) {
        auto bullet = (Sprite*)bt;
        // 遍历enemy2
        __Array* enemy2ToDel = __Array::create();
        enemy2ToDel->retain();
        CCARRAY_FOREACH(this->enemyLayer->m_allEnemy2, et) {
            Enemy* enemy2 = (Enemy*) et;
            if (bullet->getBoundingBox().intersectsRect(enemy2->getBoundingBox())) {
                if (enemy2->getLife() > 1) {
                    enemy2->loseLife();
                    bulletsToDel->addObject(bullet);
                }
                else if (enemy2->getLife() == 1) {
                    enemy2->loseLife();
                    bulletsToDel->addObject(bullet);
                    enemy2ToDel->addObject(enemy2);
                    // 加分
                    m_score += ENEMY2_LIFE;
                    this->controlLayer->updateScore(m_score);
                    enemy2->cleanup();
                }
                else {
                    
                }
            }
        }
        
        CCARRAY_FOREACH(enemy2ToDel, et) {
            Enemy* enemy2 = (Enemy*) et;
            this->enemyLayer->blowupEnemy2(enemy2);
        }
        enemy2ToDel->release();
    }
    
    CCARRAY_FOREACH(bulletsToDel, bt) {
        Sprite* bullet = (Sprite*) bt;
        this->mutiBulletLayer->removeMutiBullet(bullet);
    }
    
    bulletsToDel->removeAllObjects();
    
    CCARRAY_FOREACH(this->mutiBulletLayer->m_allMutiBullet, bt) {
        auto bullet = (Sprite*)bt;
        // 遍历enemy3
        __Array* enemy3ToDel = __Array::create();
        enemy3ToDel->retain();
        CCARRAY_FOREACH(this->enemyLayer->m_allEnemy3, et) {
            Enemy* enemy3 = (Enemy*) et;
            if (bullet->getBoundingBox().intersectsRect(enemy3->getBoundingBox())) {
                if (enemy3->getLife() > 1) {
                    enemy3->loseLife();
                    bulletsToDel->addObject(bullet);
                }
                else if (enemy3->getLife() == 1) {
                    enemy3->loseLife();
                    bulletsToDel->addObject(bullet);
                    enemy3ToDel->addObject(enemy3);
                    // 加分
                    m_score += ENEMY3_LIFE;
                    this->controlLayer->updateScore(m_score);
                    enemy3->cleanup();
                }
                else {
                    
                }
            }
        }
        
        CCARRAY_FOREACH(enemy3ToDel, et) {
            Enemy* enemy3 = (Enemy*) et;
            this->enemyLayer->blowupEnemy3(enemy3);
        }
        enemy3ToDel->release();
    }
    
    CCARRAY_FOREACH(bulletsToDel, bt) {
        Sprite* bullet = (Sprite*) bt;
        this->mutiBulletLayer->removeMutiBullet(bullet);
    }
    bulletsToDel->removeAllObjects();
    bulletsToDel->release();
}

void GameLayer::updateUFO() {
    Ref* et;
    CCARRAY_FOREACH(this->ufoLayer->m_allBomb, et) {
        Sprite* bomb = (Sprite*) et;
        Sprite* plane = this->planeLayer->getPlaneSprite();
        
        // 缩小碰撞范围
        Rect planeRect = plane->getBoundingBox();
        planeRect.origin.x += 20;
        planeRect.size.width -= 40;
        if (planeRect.intersectsRect(bomb->getBoundingBox())) {
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("get_bomb.mp3");
            this->ufoLayer->removeBomb(bomb);
            m_bombCount++;
            updateBombMenu(m_bombCount);
        }
    }
    
    CCARRAY_FOREACH(this->ufoLayer->m_allMutiBullte, et) {
        Sprite* mutiUFO = (Sprite*) et;
        Sprite* plane = this->planeLayer->getPlaneSprite();
        
        // 缩小碰撞范围
        Rect planeRect = plane->getBoundingBox();
        planeRect.origin.x += 20;
        planeRect.size.width -= 40;
        if (planeRect.intersectsRect(mutiUFO->getBoundingBox())) {
            //log("start muti bullet");
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("get_double_laser.mp3");
            this->mutiBulletLayer->startShoot();
            this->bulletLayer->stopShoot();
            this->bulletLayer->startShoot(9.0f);
            this->ufoLayer->removeMutiBullet(mutiUFO);
        }
    }
}

void GameLayer::updateBombMenu(int bombCount) {
    //log("updateBombMenu bombCount: %d\n", bombCount);
    Sprite* bomb = CCSprite::createWithSpriteFrame(PlistHandler::getInstance()->getFrameByName("bomb.png"));
    if (bombCount < 0) {
        return;
    } else if (bombCount == 0) {
        if(this->getChildByTag(TAG_BOMB_MENUITEM)) {
            this->removeChildByTag(TAG_BOMB_MENUITEM, true);//移除炸弹图标
        }
        if (this->getChildByTag(TAG_BOMBCOUNT_LABEL)) {
            this->removeChildByTag(TAG_BOMBCOUNT_LABEL, true);//移除炸弹数量
        }
    } else {
        //加入bigBoomItemMenu
        __String* strScore = __String::createWithFormat("X%d", bombCount);
        if (!this->getChildByTag(TAG_BOMB_MENUITEM)) {
            MenuItemSprite* bombItem = MenuItemSprite::create(bomb, bomb);
            bombItem->setCallback(CC_CALLBACK_1(GameLayer::menuBombCallback, this));
            bombItem->setPosition(Point(bomb->getContentSize().width/2 + 10, bomb->getContentSize().height/2 + 10));
            bombMenu = Menu::create(bombItem, NULL);
            bombMenu->setPosition(Point(0, 0));
            this->addChild(bombMenu, 0, TAG_BOMB_MENUITEM);
        }
        if (!this->getChildByTag(TAG_BOMBCOUNT_LABEL)) {
            bombCountLabel = Label::createWithBMFont("font.fnt", strScore->getCString());
            bombCountLabel->setColor(Color3B(143, 146, 147));
            bombCountLabel->setAnchorPoint(Point(0, 0.5));
            bombCountLabel->setPosition(Point(bomb->getContentSize().width + 15, bomb->getContentSize().height/2 + 5));
            this->addChild(bombCountLabel, 0, TAG_BOMBCOUNT_LABEL);
        } else {
            bombCountLabel->setString(strScore->getCString());
        }
    }
}

void GameLayer::menuBombCallback(Ref* target) {
    if (m_bombCount > 0 && !Director::getInstance()->isPaused()) {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("use_bomb.mp3");
        m_bombCount--;
        m_score += this->enemyLayer->m_allEnemy1->count() * ENEMY1_LIFE;
        m_score += this->enemyLayer->m_allEnemy2->count() * ENEMY2_LIFE;
        m_score += this->enemyLayer->m_allEnemy3->count() * ENEMY3_LIFE;
        this->enemyLayer->removeAllEnemy();
        updateBombMenu(m_bombCount);
        this->controlLayer->updateScore(m_score);
    }
}

bool GameLayer::updateEnemy() {
    Ref* obj;
    CCARRAY_FOREACH(this->enemyLayer->m_allEnemy1, obj) {
        if (checkPlaneBox((Enemy*) obj)) {
            return true;
        }
    }
    
    CCARRAY_FOREACH(this->enemyLayer->m_allEnemy2, obj) {
        if (checkPlaneBox((Enemy*) obj)) {
            return true;
        }
    }
    
    CCARRAY_FOREACH(this->enemyLayer->m_allEnemy2, obj) {
        if (checkPlaneBox((Enemy*) obj)) {
            return true;
        }
    }
    return false;
}

bool GameLayer::checkPlaneBox(Enemy* enemy) {
    Sprite* plane = this->planeLayer->getPlaneSprite();

    // 缩小碰撞范围
    Rect planeRect = plane->getBoundingBox();
    planeRect.origin.x += 30;
    planeRect.size.width -= 60;
    if (planeRect.intersectsRect(enemy->getBoundingBox())) {
        this->bulletLayer->stopShoot();
        this->planeLayer->blowup();
        //this->planeLayer->removePlane();
        log("finally score: %d\n", m_score);
        //Director::getInstance()->pause();
        this->bulletLayer->stopShoot();
        this->mutiBulletLayer->stopShoot();
        this->unscheduleUpdate();
        this->unscheduleAllCallbacks();
        return true;
    }
    return false;
}


