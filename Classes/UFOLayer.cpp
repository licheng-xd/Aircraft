//
//  UFOLayer.cpp
//  Aircraft
//
//  Created by lc on 12/1/14.
//
//

#include "UFOLayer.h"

UFOLayer::UFOLayer(void) {
    m_allBomb = __Array::create();
    m_allBomb->retain();
    m_allMutiBullte = __Array::create();
    m_allMutiBullte->retain();
}

UFOLayer::~UFOLayer(void) {
    m_allMutiBullte->release();
    m_allMutiBullte = nullptr;
    m_allBomb->release();
    m_allBomb = nullptr;
}

bool UFOLayer::init() {
    if (!Layer::init()) {
        return false;
    }
    
    this->schedule(schedule_selector(UFOLayer::addBomb), 20.0f);
    this->schedule(schedule_selector(UFOLayer::addMutiBullet), 20.0f, kRepeatForever, 5.0f);
    return true;
}

void UFOLayer::addMutiBullet(float dt) {
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("out_porp.mp3");
    auto ufoSprite = Sprite::createWithSpriteFrame(PlistHandler::getInstance()->getFrameByName("ufo1.png"));
    
    Size unfoSize = ufoSprite->getContentSize();
    Size winSize = Director::getInstance()->getWinSize();
    srand((uint) time(NULL));
    int minX = unfoSize.width / 2;
    int maxX = winSize.width - unfoSize.width / 2;
    int rangeX = maxX - minX;
    int actualX = (rand() % rangeX)+minX;
    
    ufoSprite->setPosition(Point(actualX, winSize.height + unfoSize.height/2));
    this->addChild(ufoSprite);
    this->m_allMutiBullte->addObject(ufoSprite);
    
    auto move1 = MoveBy::create(0.5, Point(0, -150));
    auto move2 = MoveBy::create(0.3, Point(0, 100));
    auto move3 = MoveBy::create(1.0, Point(0, 0 - winSize.height - unfoSize.height/2));
    auto moveDone = CallFuncN::create(CC_CALLBACK_1(UFOLayer::mutiBulletMoveFinished, this));
    
    auto sequence = Sequence::create(move1, move2, move3, moveDone, nullptr);
    ufoSprite->runAction(sequence);

}

void UFOLayer::addBomb(float dt) {
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("out_porp.mp3");
    auto ufoSprite = Sprite::createWithSpriteFrame(PlistHandler::getInstance()->getFrameByName("ufo2.png"));
    
    Size unfoSize = ufoSprite->getContentSize();
    Size winSize = Director::getInstance()->getWinSize();
    srand((uint) time(NULL));
    int minX = unfoSize.width / 2;
    int maxX = winSize.width - unfoSize.width / 2;
    int rangeX = maxX - minX;
    int actualX = (rand() % rangeX)+minX;
    
    ufoSprite->setPosition(Point(actualX, winSize.height + unfoSize.height/2));
    this->addChild(ufoSprite);
    this->m_allBomb->addObject(ufoSprite);
    
    auto move1 = MoveBy::create(0.5, Point(0, -150));
    auto move2 = MoveBy::create(0.3, Point(0, 100));
    auto move3 = MoveBy::create(1.0, Point(0, 0 - winSize.height - unfoSize.height/2));
    auto moveDone = CallFuncN::create(CC_CALLBACK_1(UFOLayer::bombMoveFinished, this));
    
    auto sequence = Sequence::create(move1, move2, move3, moveDone, nullptr);
    ufoSprite->runAction(sequence);

}

void UFOLayer::bombMoveFinished(Node* target) {
    auto boom = (Sprite*) target;
    this->removeChild(boom);
    this->m_allBomb->removeObject(boom);
}

void UFOLayer::removeBomb(Node *bomb) {
    if (bomb != nullptr) {
        this->m_allBomb->removeObject(bomb);
    }
    this->removeChild(bomb, true);
}

void UFOLayer::mutiBulletMoveFinished(Node* target) {
    auto ufo = (Sprite*) target;
    this->removeMutiBullet(ufo);
    this->m_allMutiBullte->removeObject(ufo);
}

void UFOLayer::removeMutiBullet(Node* mutiBulelt) {
    if (mutiBulelt != nullptr) {
        this->m_allMutiBullte->removeObject(mutiBulelt);
    }
    this->removeChild(mutiBulelt, true);
}
