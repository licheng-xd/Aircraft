//
//  ControlLayer.cpp
//  Aircraft
//
//  Created by lc on 11/27/14.
//
//

#include "ControlLayer.h"

ControlLayer* ControlLayer::create() {
    ControlLayer* p = new ControlLayer();
    if (p && p->init()) {
        p->autorelease();
        return p;
    }
    else {
        return NULL;
    }
}

bool ControlLayer::init() {
    if (!Layer::init()) {
        return false;
    }

    Size winSize = Director::getInstance()->getWinSize();
    Sprite* pause_nor = Sprite::createWithSpriteFrame(PlistHandler::getInstance()->getFrameByName("game_pause_nor.png"));
    Sprite* pause_pressed = Sprite::createWithSpriteFrame(PlistHandler::getInstance()->getFrameByName("game_pause_pressed.png"));
    pauseItem = MenuItemSprite::create(pause_nor, pause_pressed);
    pauseItem->setCallback(CC_CALLBACK_1(ControlLayer::menuPausedCallback, this));

    Menu* menuPause = Menu::create(pauseItem, NULL);
    menuPause->setPosition(Point(winSize.width - pause_nor->getContentSize().width/2 - 10, winSize.height - pause_nor->getContentSize().height/2 - 15));
    this->addChild(menuPause, 101);
    

    //scoreLable = Label::createWithCharMap("fps_images.png", 12, 32, 46);
    //scoreLable->setString("0");
    scoreLable = Label::createWithBMFont("font.fnt", "0");
    scoreLable->setColor(Color3B(143, 146, 147));
    scoreLable->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    scoreLable->setPosition(Point(pause_nor->getContentSize().width/2 + 10, menuPause->getPositionY()));
    this->addChild(scoreLable);
    scoreLable->setScale(2.0f);
    
    return true;
}

void ControlLayer::menuPausedCallback(Ref* pSender) {
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("button.mp3");
    if (!Director::getInstance()->isPaused()) {
        pauseItem->setNormalImage(Sprite::createWithSpriteFrame(PlistHandler::getInstance()->getFrameByName("game_resume_nor.png")));
        pauseItem->setSelectedImage(Sprite::createWithSpriteFrame(PlistHandler::getInstance()->getFrameByName("game_resume_pressed.png")));
        Director::getInstance()->pause();
    } else {
        pauseItem->setNormalImage(Sprite::createWithSpriteFrame(PlistHandler::getInstance()->getFrameByName("game_pause_nor.png")));
        pauseItem->setSelectedImage(Sprite::createWithSpriteFrame(PlistHandler::getInstance()->getFrameByName("game_pause_pressed.png")));
        Director::getInstance()->resume();
    }
}

void ControlLayer::updateScore(int score) {
    if (score >= 0) {
        __String* strScore = __String::createWithFormat("%d", score);
        scoreLable->setString(strScore->getCString());
    }
}
