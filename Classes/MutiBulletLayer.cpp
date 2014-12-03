//
//  MutiBulletLayer.cpp
//  Aircraft
//
//  Created by lc on 12/1/14.
//
//

#include "MutiBulletLayer.h"

MutiBulletLayer::MutiBulletLayer(void) {
    m_allMutiBullet = __Array::create();
    m_allMutiBullet->retain();
}

MutiBulletLayer::~MutiBulletLayer(void) {
    m_allMutiBullet->release();
    m_allMutiBullet = nullptr;
}

bool MutiBulletLayer::init() {
    if (!Layer::init()) {
        return false;
    }
    
    
    return true;
}

void MutiBulletLayer::addMutiBullet(float dt) {
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("bullet.mp3");
    Sprite* bulletLeft = Sprite::createWithSpriteFrame(PlistHandler::getInstance()->getFrameByName("bullet2.png"));
    Sprite* bulletRight = Sprite::createWithSpriteFrame(PlistHandler::getInstance()->getFrameByName("bullet2.png"));
    
    Size winSzie = Director::getInstance()->getWinSize();
    auto planePosition = PlaneLayer::_instance->getPlaneSprite()->getPosition();
    
    auto bulletLeftPosition = Point(planePosition.x - 33, planePosition.y + 35);
    auto bulletRightPosition = Point(planePosition.x + 33, planePosition.y + 35);
    bulletLeft->setPosition(bulletLeftPosition);
    bulletRight->setPosition(bulletRightPosition);
    
    this->m_allMutiBullet->addObject(bulletLeft);
    this->m_allMutiBullet->addObject(bulletRight);
    this->addChild(bulletLeft);
    this->addChild(bulletRight);
    
    float length = winSzie.height + bulletLeft->getContentSize().height/2 - bulletLeftPosition.y;
    float velocity = 420/1;
    float realMoveDuration = length/velocity;
    
    auto actionLeftMove = MoveTo::create(realMoveDuration, Point(bulletLeftPosition.x, Director::getInstance()->getWinSize().height + bulletLeft->getContentSize().height/2));
    auto actionLeftDone = CallFuncN::create(CC_CALLBACK_1(MutiBulletLayer::mutiBulletMoveFinished, this));
    auto sequenceLeft = Sequence::create(actionLeftMove, actionLeftDone, nullptr);
    
    auto actionRightMove = MoveTo::create(realMoveDuration, Point(bulletRightPosition.x, Director::getInstance()->getWinSize().height+bulletRight->getContentSize().height/2));
    auto actionRightDone = CallFuncN::create(CC_CALLBACK_1(MutiBulletLayer::mutiBulletMoveFinished, this));
    auto sequenceRight = Sequence::create(actionRightMove, actionRightDone, nullptr);
    
    bulletLeft->runAction(sequenceLeft);
    bulletRight->runAction(sequenceRight);
}

void MutiBulletLayer::mutiBulletMoveFinished(Node* target) {
    auto mutiBullet = (Sprite*) target;
    this->m_allMutiBullet->removeObject(mutiBullet);
    this->removeChild(mutiBullet);
}

void MutiBulletLayer::removeMutiBullet(Sprite* mutiBullet) {
    if (mutiBullet != nullptr) {
        this->m_allMutiBullet->removeObject(mutiBullet);
    }
    this->removeChild(mutiBullet, true);
}

void MutiBulletLayer::startShoot() {
    // 连续两次接到道具，以第二次作为开始时间
    this->unschedule(schedule_selector(MutiBulletLayer::addMutiBullet));
    this->schedule(schedule_selector(MutiBulletLayer::addMutiBullet), 0.2f, 40, 0.0f);
}

void MutiBulletLayer::stopShoot() {
    this->unschedule(schedule_selector(MutiBulletLayer::addMutiBullet));
}