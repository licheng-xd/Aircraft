//
//  WelcomeLayer.cpp
//  Aircraft
//
//  Created by lc on 12/3/14.
//
//

#include "WelcomeLayer.h"

bool WelcomeLayer::init() {
    if (!Layer::init()) {
        return false;
    }
    
    Size winSize = Director::getInstance()->getWinSize();
    Sprite* background = Sprite::createWithSpriteFrame(PlistHandler::getInstance()->getFrameByName("background.png"));
    background->setPosition(Point(winSize.width/2, winSize.height/2));
    this->addChild(background);
    
    Sprite* copyright = Sprite::createWithSpriteFrame(PlistHandler::getInstance()->getFrameByName("shoot_copyright.png"));
    copyright->setAnchorPoint(Point::ANCHOR_MIDDLE_BOTTOM);
    copyright->setPosition(Point(winSize.width/2, winSize.height/2));
    this->addChild(copyright);
    
    Sprite* loading = Sprite::createWithSpriteFrame(PlistHandler::getInstance()->getFrameByName("game_loading1.png"));
    loading->setPosition(Point(winSize.width/2, winSize.height/2 - 40));
    this->addChild(loading);
    
    Animate* animate = Animate::create(PlistHandler::getInstance()->getAnimationByName("loading"));
    auto repeat = Repeat::create(animate, 2);
    auto repeatdone = CallFuncN::create(CC_CALLBACK_1(WelcomeLayer::loadingDone, this));
    auto sequence = Sequence::create(repeat, repeatdone, nullptr);
    loading->runAction(sequence);
    
    getHighestHistoryScore();
    
    return true;
}

void WelcomeLayer::loadingDone(Node* target) {
    auto gameScene = GameScene::create();
    auto animateScene = TransitionMoveInB::create(0.5f, gameScene);
    Director::getInstance()->replaceScene(animateScene);
}

bool WelcomeLayer::haveSaveFile() {
    if (!UserDefault::getInstance()->getBoolForKey("haveSaveFileXML")) {
        UserDefault::getInstance()->setBoolForKey("haveSaveFileXML", true);
        UserDefault::getInstance()->setIntegerForKey("HighestScore", 0);
        UserDefault::getInstance()->flush();
        return false;
    } else {
        return true;
    }
}

void WelcomeLayer::getHighestHistoryScore() {
    if (haveSaveFile()) {
        GameOverLayer::m_highestScore = UserDefault::getInstance()->getIntegerForKey("HighestScore", 0);
    }
}