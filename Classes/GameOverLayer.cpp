//
//  GameOverLayer.cpp
//  Aircraft
//
//  Created by lc on 12/1/14.
//
//

#include "GameOverLayer.h"
#include "GameScene.h" // 这个头文件只能在cpp中，在h中会编译不过，奇怪

int GameOverLayer::m_highestScore = 0;

GameOverLayer::GameOverLayer(void) {
    m_score = 0;
    highestScoreLabel = nullptr;
}

GameOverLayer::~GameOverLayer(void) {
    
}

GameOverLayer* GameOverLayer::create(int score)
{
    GameOverLayer *pRet = new GameOverLayer();
    pRet->m_score = score;
    if (pRet && pRet->init()) {
        pRet->autorelease();
    } else {
        delete pRet;
        pRet = nullptr;
    }
    return pRet;
}

bool GameOverLayer::init() {
    if (!Layer::init()) {
        return false;
    }
    
    if (CocosDenshion::SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying()) {
        CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    }
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("game_over.mp3");

    Size winSize = Director::getInstance()->getWinSize();
    Sprite* background = Sprite::createWithSpriteFrameName("gameover.png");
    background->setPosition(Point(winSize.width/2, winSize.height/2));
    this->addChild(background);
    auto normalBackToGame = Sprite::createWithSpriteFrameName("btn_finish.png");
    auto pressedBackToGame = Sprite::createWithSpriteFrameName("btn_finish.png");
    auto pBackItem = MenuItemSprite::create(normalBackToGame,
                                            pressedBackToGame,
                                            nullptr,
                                            CC_CALLBACK_1(GameOverLayer::menuBackCallback, this));
    pBackItem->setPosition(Point(winSize.width-normalBackToGame->getContentSize().width/2-10, normalBackToGame->getContentSize().height/2+10));
    auto menuBack = Menu::create(pBackItem, nullptr);
    menuBack->setPosition(Point::ZERO);
    this->addChild(menuBack);
    
    Value strScore(m_score);
    auto finalScore = Label::createWithBMFont("font.fnt", strScore.asString());
    finalScore->setColor(Color3B(143, 146, 147));
    finalScore->setPosition(Point(winSize.width/2, winSize.height/2));
    this->addChild(finalScore);
    
    auto delay = DelayTime::create(1.0f);
    auto scalebig = ScaleTo::create(1.0f, 3.0f);
    auto scalelittle = ScaleTo::create(0.3f, 2.0f);
    auto showAD = CallFunc::create(CC_CALLBACK_0(GameOverLayer::showAD, this));
    auto sequence = Sequence::create(delay, scalebig, scalelittle, showAD, nullptr);
    finalScore->runAction(sequence);
    
    Value strHighestScore(m_highestScore);
    highestScoreLabel = Label::createWithBMFont("font.fnt", strHighestScore.asString());
    highestScoreLabel->setColor(Color3B(143, 146, 147));
    highestScoreLabel->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    highestScoreLabel->setPosition(Point(140, winSize.height - 55));
    this->addChild(highestScoreLabel);
    
    if (m_score > m_highestScore) {
        UserDefault::getInstance()->setIntegerForKey("HighestScore", m_score);
        m_highestScore = m_score;
        auto delayChange = DelayTime::create(1.3f);
        auto moveOut = MoveBy::create(0.1f, Point(0, 100));
        auto beginChange = CallFuncN::create(CC_CALLBACK_1(GameOverLayer::beginChangeHighestScore, this));
        auto moveIn = MoveBy::create(0.1f, Point(0, -100));
        auto sequence = Sequence::create(delayChange, moveOut, beginChange, moveIn, nullptr);
        highestScoreLabel->runAction(sequence);
    }
    
    return true;
}

void GameOverLayer::menuBackCallback(Ref* target) {
    auto scene = GameScene::create();
    auto animateScene = TransitionSlideInL::create(1.0f, scene);
    Director::getInstance()->replaceScene(animateScene);
}

void GameOverLayer::beginChangeHighestScore(Node* target) {
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("achievement.mp3");
    Value changeScore(m_score);
    highestScoreLabel->setString(changeScore.asString());
}

void GameOverLayer::showAD() {
    
}