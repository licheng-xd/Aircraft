//
//  PlistHandler.h
//  Aircraft
//
//  Created by lc on 11/27/14.
//
//

#ifndef __Aircraft__PlistHandler__
#define __Aircraft__PlistHandler__

#include <stdio.h>
#include <cstdio>
#include <iostream>
#include "cocos2d.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace std;

class PlistHandler {
private:
    
    SpriteFrameCache* frameCache;
    
    AnimationCache* animationCache;
    
    void init();
    
    PlistHandler();
    
    ~PlistHandler();
    
    static PlistHandler* m_instance;
    
    class Delete {
    public:
        ~Delete() {
            if (PlistHandler::m_instance != NULL) {
                delete PlistHandler::m_instance;
            }
        }
    };
    
    static Delete m_delete;
    
public:
    static PlistHandler* getInstance();
    
    SpriteFrame* getFrameByName(const string& name);
    
    Animation* getAnimationByName(const string& name);
};


#endif /* defined(__Aircraft__PlistHandler__) */
