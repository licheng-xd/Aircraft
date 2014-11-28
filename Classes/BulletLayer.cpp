//
//  BulletLayer.cpp
//  Aircraft
//
//  Created by lc on 11/26/14.
//
//

#include "BulletLayer.h"

BulletLayer::BulletLayer(void) {
    m_pAllBullet = __Array::create();
    m_pAllBullet->retain();
}

BulletLayer::~BulletLayer(void) {
    m_pAllBullet->release();
    m_pAllBullet = NULL;
}

BulletLayer *BulletLayer::create() {
    BulletLayer *bullet = new BulletLayer();
    if (bullet && bullet->init()) {
        bullet->autorelease();
        return bullet;
    } else {
        CC_SAFE_DELETE(bullet);
        return NULL;
    }
}

bool BulletLayer::init() {
    if (!Layer::init()) {
        return false;
    }
    
    winSize = Director::getInstance()->getWinSize();
    
    Texture2D *texture = TextureCache::getInstance()->getTextureForKey("shoot.png");
    if (texture == NULL) {
        printf("------------------texture is NULL");
    }
    bulletBatchNode = SpriteBatchNode::createWithTexture(texture);
    this->addChild(bulletBatchNode);
    
    return true;
}

void BulletLayer::addBullet(float dt) {
    Sprite* bullet = Sprite::createWithSpriteFrameName("bullet1.png");
    //    PlaneLayer *planeLayer = (PlaneLayer*)this->getParent()->getChildByTag(TAG_AIRPLANE);
    Sprite *planeSprite = PlaneLayer::getInstance()->getPlaneSprite();
    Point planePos = planeSprite->getPosition();
    
    Point bulletPos = Point(planePos.x, planePos.y + planeSprite->getContentSize().height/2);
    bullet->setPosition(bulletPos); // 子弹初始位置在飞机的头上
    
    // 子弹从初始位置到飞出屏幕的距离
    float length = Director::getInstance()->getWinSize().height + bullet->getContentSize().height/2 - bulletPos.y;
    float velocity = 420/1; // 飞行速度 420像素/秒
    float moveDuration = length / velocity; // 飞行时间
    
    FiniteTimeAction *actionMove = MoveTo::create(moveDuration, Point(bulletPos.x, Director::getInstance()->getWinSize().height + bullet->getContentSize().height/2));
    
    FiniteTimeAction *actionDone = CallFuncN::create(CC_CALLBACK_1(BulletLayer::bulletMoveFinished, this)); // 子弹结束处理回调
    Sequence *sequence = Sequence::createWithTwoActions(actionMove, actionDone);
    bullet->runAction(sequence);
    
    bulletBatchNode->addChild(bullet);
    m_pAllBullet->addObject(bullet);
    //printf("========== add bullet =========== \n");
}

void BulletLayer::bulletMoveFinished(Node *pSender) {
    Sprite *bullet = (Sprite*) pSender;
    m_pAllBullet->removeObject(bullet);
    this->bulletBatchNode->removeChild(bullet, true);
}

void BulletLayer::startShoot(float delay) {
    this->schedule(schedule_selector(BulletLayer::addBullet), 0.2f, kRepeatForever, delay);
}

void BulletLayer::stopShoot() {
    this->unschedule(schedule_selector(BulletLayer::addBullet));
}

void BulletLayer::removeBullet(Sprite *bullet) {
    if (bullet != NULL) {
        if (this->bulletBatchNode->getChildren().contains(bullet)) {
            this->bulletBatchNode->removeChild(bullet, true);
        }
        this->m_pAllBullet->removeObject(bullet);
    }
}