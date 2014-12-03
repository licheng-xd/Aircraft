//
//  GameOverScene.cpp
//  Aircraft
//
//  Created by lc on 12/1/14.
//
//

#include "GameOverScene.h"

GameOverScene::GameOverScene(void) {
    gameOverLayer = nullptr;
    m_score = 0;
}

GameOverScene::~GameOverScene(void) {
    
}

GameOverScene* GameOverScene::create(int score) {
    GameOverScene *pRet = new GameOverScene();
    pRet->m_score = score;
    if (pRet && pRet->init()) {
        pRet->autorelease();
    } else {
        delete pRet;
        pRet = nullptr;
    }
    return pRet;
}

bool GameOverScene::init() {
    if (!Scene::init()) {
        return false;
    }
    
    gameOverLayer = GameOverLayer::create(m_score);
    this->addChild(gameOverLayer);
    
    return true;
}