//
//  WelcomScene.cpp
//  Aircraft
//
//  Created by lc on 12/3/14.
//
//

#include "WelcomScene.h"

bool WelcomeScene::init() {
    if (!Scene::init()) {
        return false;
    }
    
    welcomeLayer = WelcomeLayer::create();
    this->addChild(welcomeLayer);
    preLoadMusic();
    return true;
}

void WelcomeScene::preLoadMusic() {
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("game_music.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("bullet.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("enemy1_down.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("enemy2_down.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("enemy3_down.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("game_over.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("get_bomb.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("get_double_laser.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("use_bomb.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("big_spaceship_flying.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("achievement.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("out_porp.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("button.mp3");
    
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("game_music.mp3", true);
}