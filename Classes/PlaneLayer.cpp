//
//  PlaneLayer.cpp
//  Aircraft
//
//  Created by lc on 11/25/14.
//
//

#include "PlaneLayer.h"

PlaneLayer* PlaneLayer::_instance = nullptr;

PlaneLayer* PlaneLayer::create() {
    PlaneLayer* p = new PlaneLayer();
    if (p && p->init()) {
        p->autorelease();
        _instance = p;
    } else {
        delete p;
        p = nullptr;
    }
    return p;
}

bool PlaneLayer::init() {
    
    if ( !Layer::init()) {
        return false;
    }
    isAlive = true;
    Size winSize = Director::getInstance()->getWinSize();
    
    Sprite* plane = Sprite::createWithSpriteFrame(PlistHandler::getInstance()->getFrameByName("hero1.png"));
    plane->setPosition(Point(winSize.width/2, plane->getContentSize().height/2));//飞机放置在底部中央
    this->addChild(plane, 0, TAG_AIRPLANE);
    this->planeSprite = plane;
    
    Blink *blink = Blink::create(1, 3);//闪烁动画
    Animate* animate = Animate::create(PlistHandler::getInstance()->getAnimationByName("plane"));//帧动画
    
    plane->runAction(blink);//执行闪烁动画
    plane->runAction(CCRepeatForever::create(animate));// 执行帧动画
    
    // 设置触摸监听
    touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    
    touchListener->onTouchBegan = [=](Touch *touch, Event *event) {
        if (!isAlive || Director::getInstance()->isPaused()) {
            return false;
        }
        //auto target = static_cast<Sprite*>(event->getCurrentTarget());
        Point locationInNode = touch->getLocationInView();
        locationInNode = Director::getInstance()->convertToGL(locationInNode);
        //log("sprite began... x = %f, y = %f", locationInNode.x, locationInNode.y);
        
        Rect planeRect = planeSprite->getBoundingBox();
        if (planeRect.containsPoint(locationInNode)) {
            return true;
        } else {
            return false;
        }
    };
    
    touchListener->onTouchMoved = [=](Touch* touch, Event* event){
        //auto target = static_cast<Sprite*>(event->getCurrentTarget());
        //Move the position of current button sprite
        plane->setPosition(planeSprite->getPosition() + touch->getDelta());
    };
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

    return true;
}

Sprite* PlaneLayer::getPlaneSprite() {
    return this->planeSprite;
}

void PlaneLayer::blowup() {
    Animation* animation = PlistHandler::getInstance()->getAnimationByName("planeBlowup");
    Animate* animate = Animate::create(animation);
    CallFuncN* remove = CallFuncN::create(CC_CALLBACK_0(PlaneLayer::removePlane, this));
    Sequence* sequence = Sequence::create(animate, remove, NULL);
    planeSprite->stopAllActions();
    planeSprite->runAction(sequence);
}

void PlaneLayer::removePlane() {
    this->removeChild(planeSprite);
    _eventDispatcher->removeEventListener(touchListener);
    isAlive = false;
}