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
private:
    PlaneLayer();
    static PlaneLayer *m_pInstance;
    class Delete {
    public:
        ~Delete() {
            if (PlaneLayer::m_pInstance != NULL) {
                delete PlaneLayer::m_pInstance;
            }
        }
    };
    
    static Delete m_delete;
    virtual bool init();
    Sprite* planeSprite;
    
    EventListenerTouchOneByOne* touchListener;
    
public:
    
    bool isAlive;
    
    Sprite* getPlaneSprite();
    
    static PlaneLayer* getInstance();
    
    void blowup();
    
    void removePlane();
    //static Sprite* m_planeSprite;
    //PlaneLayer();
    //~PlaneLayer();
    
    //static PlaneLayer* create();//实现create函数
    //static PlaneLayer* sharedPlane;//提供sharedPlane全局指针
};

#endif /* defined(__Aircraft__PlaneLayer__) */
