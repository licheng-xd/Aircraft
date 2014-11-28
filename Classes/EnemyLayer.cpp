//
//  EnemyLayer.cpp
//  Aircraft
//
//  Created by lc on 11/27/14.
//
//

#include "EnemyLayer.h"

EnemyLayer::EnemyLayer(void) {
    m_allEnemy1 = __Array::create();
    m_allEnemy2 = __Array::create();
    m_allEnemy3 = __Array::create();
    m_allEnemy1->retain();
    m_allEnemy2->retain();
    m_allEnemy3->retain();
}

EnemyLayer::~EnemyLayer(void) {
    m_allEnemy1->release();
    m_allEnemy1 = NULL;
    m_allEnemy2->release();
    m_allEnemy2 = NULL;
    m_allEnemy3->release();
    m_allEnemy3 = NULL;
}

EnemyLayer* EnemyLayer::create() {
    EnemyLayer* pRet = new EnemyLayer();
    if (pRet && pRet->init()) {
        pRet->autorelease();
        return pRet;
    } else {
        CC_SAFE_DELETE(pRet);
        return NULL;
    }
}

bool EnemyLayer::init() {
    if (!Layer::init()) {
        return false;
    }
    
    this->schedule(schedule_selector(EnemyLayer::addEnemy1), 2.0f, kRepeatForever, 2);
    this->schedule(schedule_selector(EnemyLayer::addEnemy2), 4.0f, kRepeatForever, 4);
    this->schedule(schedule_selector(EnemyLayer::addEnemy3), 8.0f, kRepeatForever, 8);
    return true;
}

void EnemyLayer::addEnemy1(float dt) {
    Enemy* enemy = Enemy::create();
    enemy->bindSprite(Sprite::createWithSpriteFrame(PlistHandler::getInstance()->getFrameByName("enemy1.png")), ENEMY1_LIFE);
    
    Size enemySize = enemy->getSprite()->getContentSize();
    Size winSize = Director::getInstance()->getWinSize();
    int minX = enemySize.width/2;
    int maxX = winSize.width-enemySize.width/2;
    int rangeX = maxX - minX;
    int actualX = (rand()%rangeX) + minX;
    
    enemy->setPosition(Point(actualX,winSize.height + enemySize.height/2));
    this->addChild(enemy);
    this->m_allEnemy1->addObject(enemy);
    
    //随机飞行速度
    float minDuration = 4.0f, maxDuration = 10.0f;
    int rangeDuration = maxDuration - minDuration;
    int actualDuration = (rand()%rangeDuration) + minDuration;
    
    FiniteTimeAction* actionMove = MoveTo::create(actualDuration,Point(actualX, 0 - enemy->getSprite()->getContentSize().height/2));
    FiniteTimeAction* actionDone = CallFuncN::create(CC_CALLBACK_1(EnemyLayer::enemy1MoveFinished, this));
    
    Sequence* sequence = Sequence::createWithTwoActions(actionMove, actionDone);
    enemy->runAction(sequence);
}

void EnemyLayer::enemy1MoveFinished(Node* pNode) {
    //log("enemy1 Move finished\n");
    m_allEnemy1->removeObject(pNode);
    this->removeChild(pNode);
}

void EnemyLayer::addEnemy2(float dt) {
    Enemy* enemy = Enemy::create();
    enemy->bindSprite(Sprite::createWithSpriteFrame(PlistHandler::getInstance()->getFrameByName("enemy2.png")), ENEMY2_LIFE);
    
    Size enemySize = enemy->getSprite()->getContentSize();
    Size winSize = Director::getInstance()->getWinSize();
    int minX = enemySize.width / 2;
    int maxX = winSize.width - enemySize.width / 2;
    int rangeX = maxX - minX;
    int actualX = (rand()%rangeX) + minX;
    
    enemy->setPosition(Point(actualX,winSize.height + enemySize.height/2));
    this->addChild(enemy);
    this->m_allEnemy2->addObject(enemy);
    
    //随机飞行速
    float minDuration = 6.0f, maxDuration = 14.0f;
    int rangeDuration = maxDuration - minDuration;
    int actualDuration = (rand()%rangeDuration) + minDuration;
    
    FiniteTimeAction* actionMove = MoveTo::create(actualDuration,Point(actualX, 0 - enemy->getSprite()->getContentSize().height/2));
    FiniteTimeAction* actionDone = CallFuncN::create(CC_CALLBACK_1(EnemyLayer::enemy2MoveFinished, this));
    
    Sequence* sequence = Sequence::createWithTwoActions(actionMove, actionDone);
    enemy->runAction(sequence);
}

void EnemyLayer::enemy2MoveFinished(Node* pNode) {
    //log("enemy2 Move finished\n");
    m_allEnemy2->removeObject(pNode);
    this->removeChild(pNode);
}

void EnemyLayer::addEnemy3(float dt) {
    Enemy* enemy = Enemy::create();
    
    Animate* animate = Animate::create(PlistHandler::getInstance()->getAnimationByName("enemy3"));
    enemy->bindSprite(Sprite::create(), ENEMY3_LIFE);
    enemy->getSprite()->runAction(RepeatForever::create(animate));
    
    Size enemySize = PlistHandler::getInstance()->getFrameByName("enemy3_n1.png")->getOriginalSize();
    Size winSize = Director::getInstance()->getWinSize();
    int minX = enemySize.width / 2;
    int maxX = winSize.width - enemySize.width / 2;
    int rangeX = maxX-minX;
    int actualX = (rand()%rangeX) + minX;
    
    enemy->setPosition(Point(actualX, winSize.height + enemySize.height/2));
    this->addChild(enemy);
    this->m_allEnemy3->addObject(enemy);
    
    //随机飞行速
    float minDuration = 6.0f, maxDuration = 14.0f;
    int rangeDuration = maxDuration - minDuration;
    int actualDuration = (rand()%rangeDuration) + minDuration;
    
    FiniteTimeAction* actionMove = MoveTo::create(actualDuration, Point(actualX, 0 - enemySize.height/2));
    FiniteTimeAction* actionDone = CallFuncN::create(CC_CALLBACK_1(EnemyLayer::enemy3MoveFinished, this));
    
    Sequence* sequence = Sequence::createWithTwoActions(actionMove, actionDone);
    enemy->runAction(sequence);
}

void EnemyLayer::enemy3MoveFinished(Node* pNode) {
    //log("enemy3 Move finished\n");
    m_allEnemy3->removeObject(pNode);
    this->removeChild(pNode);
}

void EnemyLayer::blowupEnemy1(Enemy *enemy1) {
    Animation* animation = PlistHandler::getInstance()->getAnimationByName("enemy1Blowup");
    Animate* animate = Animate::create(animation);
    CallFuncN* remove = CallFuncN::create(CC_CALLBACK_1(EnemyLayer::removeEnemy1, this, enemy1));
    Sequence* sequence = Sequence::create(animate, remove, NULL);
    enemy1->getSprite()->runAction(sequence);
}

void EnemyLayer::blowupEnemy2(Enemy *enemy2) {
    Animation* animation = PlistHandler::getInstance()->getAnimationByName("enemy2Blowup");
    Animate* animate = Animate::create(animation);
    CallFuncN* remove = CallFuncN::create(CC_CALLBACK_1(EnemyLayer::removeEnemy2, this, enemy2));
    Sequence* sequence = Sequence::create(animate, remove, NULL);
    enemy2->getSprite()->runAction(sequence);
}

void EnemyLayer::blowupEnemy3(Enemy *enemy3) {
    Animation* animation = PlistHandler::getInstance()->getAnimationByName("enemy3Blowup");
    Animate* animate = Animate::create(animation);
    CallFuncN* remove = CallFuncN::create(CC_CALLBACK_1(EnemyLayer::removeEnemy3, this, enemy3));
    Sequence* sequence = Sequence::create(animate, remove, NULL);
    enemy3->getSprite()->runAction(sequence);
}

void EnemyLayer::removeEnemy1(Node* pTarget, void* data) {
    Enemy* enemy1 = (Enemy*) data;
    if (enemy1 != NULL)
    {
        m_allEnemy1->removeObject(enemy1);
        this->removeChild(enemy1, true);
    }
}

void EnemyLayer::removeEnemy2(Node* pTarget, void* data) {
    Enemy* enemy2 = (Enemy*) data;
    if (enemy2 != NULL)
    {
        m_allEnemy2->removeObject(enemy2);
        this->removeChild(enemy2, true);
    }
}

void EnemyLayer::removeEnemy3(Node* pTarget, void* data) {
    Enemy* enemy3 = (Enemy*) data;
    if (enemy3 != NULL)
    {
        m_allEnemy3->removeObject(enemy3);
        this->removeChild(enemy3, true);
    }
}