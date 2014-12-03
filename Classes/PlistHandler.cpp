//
//  PlistHandler.cpp
//  Aircraft
//
//  Created by lc on 11/27/14.
//
//

#include "PlistHandler.h"

PlistHandler* PlistHandler::m_instance = NULL;

PlistHandler::Delete PlistHandler::m_delete;

PlistHandler::PlistHandler() {
    init();
}

PlistHandler::~PlistHandler() {
    
}

PlistHandler* PlistHandler::getInstance() {
    if (m_instance == NULL) {
        m_instance = new PlistHandler();
    }
    return m_instance;
}

void PlistHandler::init() {
    //png加入全局cache中
    frameCache = SpriteFrameCache::getInstance();
    frameCache->addSpriteFramesWithFile("shoot_background.plist");
    frameCache->addSpriteFramesWithFile("shoot.plist");
    
    animationCache = AnimationCache::getInstance();
    
    //game loading
    Animation* animationLoading = Animation::create();
    animationLoading->setDelayPerUnit(0.2f);
    animationLoading->addSpriteFrame(frameCache->getSpriteFrameByName("game_loading1.png"));
    animationLoading->addSpriteFrame(frameCache->getSpriteFrameByName("game_loading2.png"));
    animationLoading->addSpriteFrame(frameCache->getSpriteFrameByName("game_loading3.png"));
    animationLoading->addSpriteFrame(frameCache->getSpriteFrameByName("game_loading4.png"));
    animationCache->addAnimation(animationLoading, "loading");
    
    // plane fly
    Animation* animationPlane = Animation::create();
    animationPlane->setDelayPerUnit(0.1f);
    animationPlane->addSpriteFrame(frameCache->getSpriteFrameByName("hero1.png"));
    animationPlane->addSpriteFrame(frameCache->getSpriteFrameByName("hero2.png"));
    animationCache->addAnimation(animationPlane, "plane");
    
    // plane blowup
    Animation* animationPlaneBlowup = Animation::create();
    animationPlaneBlowup->setDelayPerUnit(0.1f);
    animationPlaneBlowup->addSpriteFrame(frameCache->getSpriteFrameByName("hero_blowup_n1.png"));
    animationPlaneBlowup->addSpriteFrame(frameCache->getSpriteFrameByName("hero_blowup_n2.png"));
    animationPlaneBlowup->addSpriteFrame(frameCache->getSpriteFrameByName("hero_blowup_n3.png"));
    animationPlaneBlowup->addSpriteFrame(frameCache->getSpriteFrameByName("hero_blowup_n4.png"));
    animationCache->addAnimation(animationPlaneBlowup, "planeBlowup");
    
    // enemy3 fly
    Animation* animationEnemy3 = Animation::create();
    animationEnemy3->setDelayPerUnit(0.2f);
    animationEnemy3->addSpriteFrame(frameCache->getSpriteFrameByName("enemy3_n1.png"));
    animationEnemy3->addSpriteFrame(frameCache->getSpriteFrameByName("enemy3_n2.png"));
    animationCache->addAnimation(animationEnemy3, "enemy3");
    
    // enemy1 down
    Animation* animationEnemy1Blowup = Animation::create();
    animationEnemy1Blowup->setDelayPerUnit(0.1f);
    animationEnemy1Blowup->addSpriteFrame(frameCache->getSpriteFrameByName("enemy1_down1.png"));
    animationEnemy1Blowup->addSpriteFrame(frameCache->getSpriteFrameByName("enemy1_down2.png"));
    animationEnemy1Blowup->addSpriteFrame(frameCache->getSpriteFrameByName("enemy1_down3.png"));
    animationEnemy1Blowup->addSpriteFrame(frameCache->getSpriteFrameByName("enemy1_down4.png"));
    animationCache->addAnimation(animationEnemy1Blowup, "enemy1Blowup");
    
    Animation* animationEnemy2Blowup = Animation::create();
    animationEnemy2Blowup->setDelayPerUnit(0.1f);
    animationEnemy2Blowup->addSpriteFrame(frameCache->getSpriteFrameByName("enemy2_down1.png"));
    animationEnemy2Blowup->addSpriteFrame(frameCache->getSpriteFrameByName("enemy2_down2.png"));
    animationEnemy2Blowup->addSpriteFrame(frameCache->getSpriteFrameByName("enemy2_down3.png"));
    animationEnemy2Blowup->addSpriteFrame(frameCache->getSpriteFrameByName("enemy2_down4.png"));
    animationCache->addAnimation(animationEnemy2Blowup, "enemy2Blowup");
    
    Animation* animationEnemy3Blowup = Animation::create();
    animationEnemy3Blowup->setDelayPerUnit(0.1f);
    animationEnemy3Blowup->addSpriteFrame(frameCache->getSpriteFrameByName("enemy3_down1.png"));
    animationEnemy3Blowup->addSpriteFrame(frameCache->getSpriteFrameByName("enemy3_down2.png"));
    animationEnemy3Blowup->addSpriteFrame(frameCache->getSpriteFrameByName("enemy3_down3.png"));
    animationEnemy3Blowup->addSpriteFrame(frameCache->getSpriteFrameByName("enemy3_down4.png"));
    animationEnemy3Blowup->addSpriteFrame(frameCache->getSpriteFrameByName("enemy3_down5.png"));
    animationEnemy3Blowup->addSpriteFrame(frameCache->getSpriteFrameByName("enemy3_down6.png"));
    animationCache->addAnimation(animationEnemy3Blowup, "enemy3Blowup");
}

SpriteFrame* PlistHandler::getFrameByName(const string& name) {
    return frameCache->getSpriteFrameByName(name);
}

Animation* PlistHandler::getAnimationByName(const string& name) {
    return animationCache->getAnimation(name);
}