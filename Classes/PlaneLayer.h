//
//  PlaneLayer.h
//  Aircraft
//
//  Created by lc on 11/25/14.
//
//

#ifndef __Aircraft__PlaneLayer__
#define __Aircraft__PlaneLayer__

#include <stdio.h>
#include "PlistHandler.h"
#include "ControlLayer.h"

USING_NS_CC;

class PlaneLayer : public Layer {
public:
    virtual bool init();

    Sprite* planeSprite;
    
    EventListenerTouchOneByOne* touchListener;

    bool isAlive;
    
    Sprite* getPlaneSprite();
    
    static PlaneLayer* getInstance();
    
    void blowup();
    
    void removePlane();
    
    static PlaneLayer* create();//实现create函数
    
    static PlaneLayer* _instance;//提供全局指针
};

#endif /* defined(__Aircraft__PlaneLayer__) */
