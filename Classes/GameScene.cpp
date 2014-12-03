//
//  GameScene.cpp
//  Aircraft
//
//  Created by lc on 12/3/14.
//
//

#include "GameScene.h"

bool GameScene::init() {
    if (!Scene::init()) {
        return false;
    }
    
    gameLayer = GameLayer::create();
    this->addChild(gameLayer);
    return true;
}