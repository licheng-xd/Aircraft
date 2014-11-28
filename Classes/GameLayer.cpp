//
//  GameLayer.cpp
//  Aircraft
//
//  Created by lc on 11/23/14.
//
//

#include "GameLayer.h"

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
    
    //Size visibleSize = Director::getInstance()->getVisibleSize();
    this->controlLayer = ControlLayer::create();
    this->addChild(controlLayer);
    
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
    this->planeLayer = PlaneLayer::getInstance();
    this->addChild(planeLayer, 0, TAG_AIRPLANE);
    
    //加入bulletLayer
    this->bulletLayer = BulletLayer::create();
    this->addChild(bulletLayer);
    this->bulletLayer->startShoot(1);
    
    // add enemyLayer
    this->enemyLayer = EnemyLayer::create();
    this->addChild(enemyLayer);
    
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
    
    __Array* bulletsToDel = __Array::create();
    bulletsToDel->retain();
    Ref *bt, *et;
    
    CCARRAY_FOREACH(this->bulletLayer->m_pAllBullet, bt) { // 遍历子弹
        Sprite* bullet = (Sprite*) bt;
        
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
                    score += ENEMY1_LIFE;
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
                    score += ENEMY2_LIFE;
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
                    score += ENEMY3_LIFE;
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
    
    bulletsToDel->release();
    
    updatePlane();
}

bool GameLayer::updatePlane() {
    Ref* et;
    
    CCARRAY_FOREACH(this->enemyLayer->m_allEnemy1, et) {
        if (checkPlaneBox((Enemy*) et)) {
            return true;
        }
    }
    
    CCARRAY_FOREACH(this->enemyLayer->m_allEnemy2, et) {
        if (checkPlaneBox((Enemy*) et)) {
            return true;
        }
    }
    
    CCARRAY_FOREACH(this->enemyLayer->m_allEnemy2, et) {
        if (checkPlaneBox((Enemy*) et)) {
            return true;
        }
    }
    return false;
}

bool GameLayer::checkPlaneBox(Enemy* enemy) {
    Sprite* plane = this->planeLayer->getPlaneSprite();

    // 缩小碰撞范围
    Rect planeRect = plane->getBoundingBox();
    //log("plane rect %f, %f, %f, %f\n", planeRect.origin.x, planeRect.origin.y, planeRect.size.width, planeRect.size.height);
    planeRect.origin.x -= 5;
    planeRect.origin.y -= 5;
    //planeRect.size.width -= 10;
    //planeRect.size.height -= 10;
    
    if (planeRect.intersectsRect(enemy->getBoundingBox())) {
        this->bulletLayer->stopShoot();
        this->planeLayer->blowup();
        //this->planeLayer->removePlane();
        log("finally score: %d\n", score);
        //Director::getInstance()->pause();
        this->bulletLayer->stopShoot();
        this->unscheduleUpdate();
        return true;
    }
    return false;
}


